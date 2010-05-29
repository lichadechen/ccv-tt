// ContourMatchingTest Project

#include "stdafx.h"

#include "cv.h"
#include "highgui.h"
#include "cxcore.h"

int main();

int _tmain(int argc, _TCHAR* argv[])
{
	return main();
}

//Method to draw a Box in an image with CvBox2D object
static void draw_box(IplImage *image, CvBox2D box, CvScalar color) {
  CvPoint2D32f boxPoints[4];

  cvBoxPoints(box, boxPoints);
  cvLine(image,
	   cvPoint((int)boxPoints[0].x, (int)boxPoints[0].y),
	   cvPoint((int)boxPoints[1].x, (int)boxPoints[1].y),
	   color);
  cvLine(image,
	   cvPoint((int)boxPoints[1].x, (int)boxPoints[1].y),
	   cvPoint((int)boxPoints[2].x, (int)boxPoints[2].y),
	   color);
  cvLine(image,
	   cvPoint((int)boxPoints[2].x, (int)boxPoints[2].y),
	   cvPoint((int)boxPoints[3].x, (int)boxPoints[3].y),
	   color);
  cvLine(image,
	   cvPoint((int)boxPoints[3].x, (int)boxPoints[3].y),
	   cvPoint((int)boxPoints[0].x, (int)boxPoints[0].y),
	   color);
}

CvSeq* getTemplateContours(IplImage *img,double minArea)
{
CvSeq* contours;
CvSeq* tempContours=0;
CvMemStorage *storage = cvCreateMemStorage(0);

int number=cvFindContours(img, storage, &contours, sizeof(CvContour),
						  CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

printf("%d",number);

for( ; contours != 0 || tempContours==0 ; contours = contours->h_next )
{
	CvBox2D box=cvMinAreaRect2(contours);

	if(box.size.width*box.size.height > minArea)
	{
		CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&0 );
		tempContours=contours;
	}
}

//cvReleaseMemStorage(0);

return tempContours;
}

int main()
{
IplImage *main,*temp;    /// For Showing
main = cvLoadImage("Images/main.jpg",0);
temp = cvLoadImage("Images/template.jpg",0);

IplImage *img,*temp_tmp; /// For calcluation purpose
img = cvCloneImage(main);
temp_tmp=cvCloneImage(temp);

//*************************************************************//
//All the operations go here
//*************************************************************//

cvThreshold(img,img,120,255,CV_THRESH_BINARY);
cvSmooth(img,img,CV_MEDIAN);

cvThreshold(temp_tmp,temp_tmp,80,255,CV_THRESH_BINARY);
//cvSmooth(temp_tmp,temp_tmp,CV_MEDIAN);

/******Remove This *******/
IplImage *local=cvCloneImage(temp_tmp);
/*************************/

CvSeq *tempContours=getTemplateContours(temp_tmp,2*temp_tmp->height*temp_tmp->width/3);
CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&0 );
/* replace CV_FILLED with 1 to see the outlines */
cvDrawContours( temp, tempContours, color, color, -1, 1, 8 );

CvSeq* contours;
CvMemStorage *storage = cvCreateMemStorage(0);

int number=cvFindContours(img, storage, &contours, sizeof(CvContour),
						  CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

printf("\nNumber of main Contours in the main image: %d",number);


for( ; contours != 0; contours = contours->h_next )
{
	//CvBox2D box=cvMinAreaRect2(contours);
	double result=cvMatchShapes(contours,tempContours,CV_CONTOURS_MATCH_I2);

	printf("\n %f",result);
	if(result<0.01)
	{
		CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&0 );
		cvDrawContours( main, contours, color, color, -1, 1, 8 );
	}
}


//*************************************************************//
//Operations End
//*************************************************************//

cvNamedWindow("Main Image");
cvShowImage("Main Image",main);

cvNamedWindow("Template Image");
cvShowImage("Template Image",temp);

cvWaitKey(0);

cvReleaseImage(&main);
cvReleaseImage(&temp);
cvReleaseImage(&img);
cvReleaseImage(&temp_tmp);

cvDestroyWindow("Main Image");
cvDestroyWindow("Template Image");
return 0;
}