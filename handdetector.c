#include <stdio.h>
#include <cv.h>
#include <highgui.h>

void skinFilter(IplImage* img) {
	IplImage* ycbcr = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
	IplImage* filtered_img = cvCreateImage(cvGetSize(img), img->depth, 1);
	cvCvtColor(img, ycbcr, CV_BGR2YCrCb);
	cvInRangeS(ycbcr, cvScalar(120, 133, 77), cvScalar(235, 173, 127), filtered_img);
	cvShowImage("filter", filtered_img);
	cvReleaseImage(&ycbcr);
	cvReleaseImage(&filtered_img);
}
