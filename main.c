#include<highgui.h>
#include<cv.h>
#include<stdio.h>
#include<stdlib.h>
#include"face.h"
#include"contrast.h"
#include"handdetector.h"
#include"webcam.h"

int main(int argc, char* argv[]) {
	int c = 0;
	CvCapture *capture = cvCaptureFromCAM(CV_CAP_ANY);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);
	
	IplImage *img = 0;
	if(!cvQueryFrame(capture))
		printf("Video capture failed, please check the camera.");
	else
		printf("Video camera capture status: OK");
		
	cvNamedWindow("Video In", CV_WINDOW_AUTOSIZE);
	
	while( c != 27 || c!= 1048603) {
	  img = cvQueryFrame( capture );
          //glg(img);
	  detectFace(img);
	  cvShowImage("Video In", img);
	  skinFilter(img);
	  c = cvWaitKey(30);
	}
	cvReleaseImage(&img);
	cvReleaseCapture( &capture);
	cvDestroyAllWindows();
    return 0;
}
