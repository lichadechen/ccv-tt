// ContourMatchingTest Project

#include "stdafx.h"

#include "cv.h"
#include "highgui.h"
#include "cxcore.h"


#define PROCEDURE 1


int main();
int check();

int _tmain(int argc, _TCHAR* argv[])
{
	if(PROCEDURE==1){return main();}
	if(PROCEDURE==2){return check();}
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
CvScalar getRandomColor()
{
return CV_RGB( rand()&255, rand()&255, rand()&255 );
}

CvSeq* getContours(IplImage* img)
{
	CvSeq* contours;
	CvMemStorage *storage = cvCreateMemStorage(0);
	int number=cvFindContours(img, storage, &contours, sizeof(CvContour),
						  CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

	printf("Number of Main contours = %d\n",number);
	return contours;
}

CvSeq* getTemplateContours(IplImage *img,double minArea,bool retutnAll=false)
{
CvSeq* contours;
CvMemStorage *storage = cvCreateMemStorage(0);

int number=cvFindContours(img, storage, &contours, sizeof(CvContour),
						  CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

printf("Number of Template contours = %d\n",number);

if(retutnAll)
{
return contours;
}
else
{
CvSeq* tempContours=0;
for( ; contours != 0 || tempContours==0 ; contours = contours->h_next )
{
	CvBox2D box=cvMinAreaRect2(contours);

	if(box.size.width*box.size.height > minArea)
	{
		tempContours=contours;
	}
}

return tempContours;
}

//cvReleaseMemStorage(0);


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
cvSmooth(temp_tmp,temp_tmp,CV_MEDIAN);

double minArea=2*temp_tmp->height*temp_tmp->width/3;
CvSeq *tempContours=getTemplateContours(temp_tmp,minArea);

CvBox2D tempbox=cvMinAreaRect2(tempContours);
double minArea2=9*tempbox.size.height*tempbox.size.width/13;
double maxArea2=15*tempbox.size.height*tempbox.size.width/13;


if(tempContours!=0)
{
cvDrawContours(temp, tempContours, getRandomColor(),getRandomColor(), -1,1, 8 );
}
else
{
	printf("Bad Template Contour");
}
CvSeq* contours;
CvMemStorage *storage = cvCreateMemStorage(0);

int number=cvFindContours(img, storage, &contours, sizeof(CvContour),
						  CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

printf("Number of main Contours in the main image = %d\n",number);

int n=0;
for( ; contours != 0; contours = contours->h_next )
{
	CvBox2D box=cvMinAreaRect2(contours);
	cvDrawContours( main,contours, getRandomColor(),getRandomColor(), -1, 1, 8 );
	if(box.size.height*box.size.width> minArea2 && box.size.height*box.size.width<maxArea2)
	{
		draw_box(main,box,getRandomColor());
		n++;
	}
}
printf("No of BIG Contours = %d\n",n);

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


int check()
{
	IplImage *main,*temp;
	main = cvLoadImage("Images/main.jpg",0);
	temp = cvLoadImage("Images/template.jpg",0);
	


	cvThreshold(main,main,120,255,CV_THRESH_BINARY);
	cvSmooth(main,main,CV_MEDIAN);

	cvThreshold(temp,temp,80,255,CV_THRESH_BINARY);
	cvSmooth(temp,temp,CV_MEDIAN);

	CvSeq* contours=getContours(cvCloneImage(main));
	CvSeq* tempContours=getTemplateContours(cvCloneImage(temp),1);

	cvDrawContours( main,contours, getRandomColor(),getRandomColor(), -1, 1, 8 );
	cvDrawContours(temp, tempContours, getRandomColor(),getRandomColor(), -1,1, 8 );

	cvNamedWindow("Main Image");
	cvShowImage("Main Image",main);

	cvNamedWindow("Template Image");
	cvShowImage("Template Image",temp);

	cvWaitKey(0);

	cvReleaseImage(&main);
	cvReleaseImage(&temp);
	
	cvDestroyWindow("Main Image");
	cvDestroyWindow("Template Image");
	return 0;

}