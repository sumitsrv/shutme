#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"

CvHaarClassifierCascade *cascade,*cascade_el,*cascade_er,*cascade_nose,*cascade_mouth;
CvMemStorage            *storage;
char *file = (char*)calloc(50,1);
int countfile=0;
int channel = 1;
int lefteyewidth ;
char *face_cascade="haarcascade_frontalface_alt2.xml";
char *lefteye_cascade="haarcascade_mcs_lefteye.xml";
char *righteye_cascade="haarcascade_mcs_righteye.xml";
char *nose_cascade="haarcascade_mcs_nose.xml";
char *mouth_cascade="haarcascade_mcs_mouth.xml";

void detectFacialFeatures( IplImage *, IplImage *);

void detectFacialFeatures( IplImage *img, IplImage *temp_img)
{
    float m[6];
    double factor = 1;
    CvMat M = cvMat( 2, 3, CV_32F, m );
    int w = (img)->width;
    int h = (img)->height;
    CvSeq* faces;
    CvRect *r;

    m[0] = (float)(factor*cos(0.0));
    m[1] = (float)(factor*sin(0.0));
    m[2] = w*0.5f;
    m[3] = -m[1];
    m[4] = m[0];
    m[5] = h*0.5f;

    cvGetQuadrangleSubPix(img, temp_img, &M);
    CvMemStorage* storage=cvCreateMemStorage(0);
    cvClearMemStorage( storage );

    if( cascade )
        faces = cvHaarDetectObjects(img,cascade, storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(20, 20));
    else
        printf("\nFrontal face cascade not loaded\n");

    /* for each face found, draw a red box */
    for(int i = 0 ; i < ( faces ? faces->total : 0 ) ; i++ )
    {
        r = ( CvRect* )cvGetSeqElem( faces, i );
        cvRectangle( img,cvPoint( r->x, r->y ),cvPoint( r->x + r->width, r->y + r->height ),
                     CV_RGB( 255, 0, 0 ), 1, 8, 0 );
	    cvSetImageROI(img, cvRect(r->x, r->y, r->width, r->height));
        cvResetImageROI(img);
    }
    /* reset region of interest */
      cvResetImageROI(img);
}

void detectFace(IplImage *img)
{
    IplImage *temp_img;
    IplImage *gray;
    IplImage *temp_gray;
   
    char image[100];

    /* load the classifier
       note that I put the file in the same directory with
       this code */
    storage = cvCreateMemStorage( 0 );
    
    cascade = ( CvHaarClassifierCascade* )cvLoad( face_cascade, 0, 0, 0 );
    
    if( !cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    }

    temp_img = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);
    cvCopy(img, temp_img, 0);

    if(!img)
    {
      printf("Could not load image file and trying once again: %s\n",image);
    }
    
    channel = 1; /*for color*/
    detectFacialFeatures(img,temp_img); /*for color*/

    cvReleaseHaarClassifierCascade( &cascade );
    cvReleaseHaarClassifierCascade( &cascade_el );
    cvReleaseHaarClassifierCascade( &cascade_er );
    cvReleaseHaarClassifierCascade( &cascade_nose );
    cvReleaseHaarClassifierCascade( &cascade_mouth );
    cvReleaseMemStorage( &storage );

    cvReleaseImage(&temp_img);
}
