// ContourMatchingTest Project

#include "stdafx.h"

#include "cv.h"
#include "highgui.h"

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

cvThreshold(temp_tmp,temp_tmp,120,255,CV_THRESH_BINARY);
cvSmooth(temp_tmp,temp_tmp,CV_MEDIAN);

/******Remove This *******/
IplImage *local=cvCloneImage(temp_tmp);

CvSeq* contours;
CvMemStorage *storage = cvCreateMemStorage(0);

int number=cvFindContours(temp_tmp, storage, &contours, sizeof(CvContour),
						  CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

printf("%d",number);

int n2=0;

for( ; contours != 0; contours = contours->h_next )
{
	CvBox2D box=cvMinAreaRect2(contours);
	double minArea=temp_tmp->width*temp_tmp->height/3;

	if(box.size.width*box.size.height > minArea)
	{
		n2++;
		CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&0 );
		cvDrawContours( temp, contours, color, color, -1, 1, 8 );
		//draw_box(temp,box,color);
	}
}

printf("\n%d",n2);


//*************************************************************//
//Operations End
//*************************************************************//

cvNamedWindow("Main Image");
cvShowImage("Main Image",local);

cvNamedWindow("Template Image");
cvShowImage("Template Image",temp);

cvWaitKey(0);

cvReleaseImage(&main);
cvReleaseImage(&temp);
cvReleaseImage(&img);
cvReleaseImage(&temp_tmp);
return 0;
}