#include <iostream>
#include <vector>
#include "Functionale.h"

int DetectHowMuchCamsHere(int& counter)
{
	cv::Mat testframe;
	cv::VideoCapture testcap(counter);
	if (testcap.read(testframe)) {
		counter++;
		DetectHowMuchCamsHere(counter);
	}
	else return counter;
}
int PickACam(int counter)
{
	int choice = 0;
	std::cin >> choice;
	choice--;
	if (choice > (counter - 1) || (choice < 0)) {
		std::cout << "Sorry, you picked a wrong cam, try again" << std::endl;
		PickACam(counter);
	}
	else return choice;
}
void ShowCam(int CameraToBeOpened, int counteroftakenpictures, int counterofvideos)
{
	int i = 0, j = 0;
	cv::Mat frame;
	cv::VideoCapture cap(CameraToBeOpened);
	cvNamedWindow("Camera", CV_WINDOW_NORMAL);
	while (true) {
		if (cap.read(frame))
			imshow("Camera", frame);
		char c = cvWaitKey(50);
		if (c == 27)	//push 'esc'
			break;
		if (c == 112)	//push 'p'
			TakeAPicture(frame, counteroftakenpictures);
		if (c == 32)	//push 'space'
		{
			TakeAVideo(CameraToBeOpened, counterofvideos);
			ShowCam(CameraToBeOpened, counteroftakenpictures, counterofvideos);
		}
		if (c == 122)	//push 'z'
		{
			DetectFace(CameraToBeOpened);
			ShowCam(CameraToBeOpened, counteroftakenpictures, counterofvideos);
		}
	}
	cvDestroyAllWindows();
}
int TakeAPicture(cv::Mat picture, int& counter) {
	char filename[100];
	sprintf_s(filename, "Test pictures/test_%d.jpg", counter);
	counter++;
	cv::imwrite(filename, picture);
	std::cout << "Image has been captured" << std::endl;
	return counter;
}
int TakeAVideo(int CameraToBeOpened, int& counter) {
	cv::Mat frame_in_video;
	cv::VideoCapture cap_for_video(CameraToBeOpened);
	bool writevideo = true;
	std::cout << "You are on air!" << std::endl;
	char videoname[100];
	sprintf_s(videoname, "Test videos/test_video_%d.avi", counter);
	counter++;
	int Width = cap_for_video.get(CV_CAP_PROP_FRAME_WIDTH);
	int Height = cap_for_video.get(CV_CAP_PROP_FRAME_HEIGHT);
	cv::VideoWriter video(videoname, CV_FOURCC('M', 'J', 'P', 'G'), 10, cvSize(Width, Height), true);
	while (writevideo) {
		if (cap_for_video.read(frame_in_video)) {
			imshow("Camera", frame_in_video);
		cap_for_video.read(frame_in_video);
		}
		video.write(frame_in_video);
		char stopper = cvWaitKey(50);
		if (stopper == 32) {
			writevideo = false;
			stopper = 0;
			std::cout << "Video has been captured" << std::endl;
			break;
		}
	}
	return counter;
}
int DetectFace(int CameraToBeOpened) {
	cv::CascadeClassifier face_cascade;
	cv::Mat frame, grayscaleframe;
	cv::VideoCapture cap(CameraToBeOpened);
	face_cascade.load("haarcascade_frontalface_alt.xml");
	bool detectface = true;
	while (detectface) {
		cap >> frame;
		cvtColor(frame, grayscaleframe, CV_BGR2GRAY);
		cv::equalizeHist(grayscaleframe, grayscaleframe);
		std::vector<cv::Rect> faces;
		face_cascade.detectMultiScale(grayscaleframe, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE);
		for (int i = 0; i < faces.size(); i++)
		{
			cv::Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			cv::Point pt2(faces[i].x, faces[i].y);
			cv::rectangle(frame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
		}
		imshow("Camera", frame);
		char stopper = cvWaitKey(50);
		{
			if (stopper == 122) {
				detectface = false;
				stopper = 0;
				std::cout << "Stop it!" << std::endl;
				break;
			}
			if (stopper == 27)
				break;
		}
	}
	return 0;
}