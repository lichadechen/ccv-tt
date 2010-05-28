// ContourMatchingTest Project

#include "stdafx.h"

#include "cv.h"
#include "highgui.h"

int main();

int _tmain(int argc, _TCHAR* argv[])
{
	return main();
}

int main()
{
IplImage* img = cvLoadImage("main.jpg",0);
IplImage* temp = cvLoadImage("template.jpg",0);
IplImage* contourDrawn = cvCloneImage(img);

cvNamedWindow("Main Image");


cvNamedWindow("Template Image");


return 0;

}