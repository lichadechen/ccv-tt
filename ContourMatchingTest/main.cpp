// ContourMatchingTest Project

#include "stdafx.h"

#include "cv.h"
#include "highgui.h"

int main();

int _tmain(int argc, _TCHAR* argv[])
{
	return main();
}
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

//All the operations go here

cvThreshold(img,img,120,255,CV_THRESH_BINARY);
cvSmooth(img,img,CV_MEDIAN);

cvThreshold(temp_tmp,temp_tmp,100,255,CV_THRESH_BINARY);
//cvSmooth(temp_tmp,temp_tmp,CV_MEDIAN);

cvNamedWindow("Main Image");
cvShowImage("Main Image",img);

cvNamedWindow("Template Image");
cvShowImage("Template Image",temp_tmp);

cvWaitKey(0);

cvReleaseImage(&main);
cvReleaseImage(&temp);
cvReleaseImage(&img);
cvReleaseImage(&temp_tmp);
return 0;
}