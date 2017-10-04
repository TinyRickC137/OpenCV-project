#include "opencv\highgui.h"
#include "opencv\cv.h"

int notmain()
{
	CvCapture* camera = cvCreateCameraCapture(-1);
	IplImage* frame = NULL;
	cvNamedWindow("Camera", CV_WINDOW_NORMAL);
	cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH, 640);
	cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT, 480);
	while (true)
	{
		frame = cvQueryFrame(camera);
		if (!frame)
		   break;
		cvShowImage("Camera", frame);
		char c = cvWaitKey(50);
		if (c == 27)
			break;
	}

	cvDestroyWindow("Camera");
	cvReleaseImage(&frame);
	return 0;
}