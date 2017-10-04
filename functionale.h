#pragma once

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv\cv.hpp"

void ShowCam(int, int, int);
int DetectHowMuchCamsHere(int&);
int PickACam(int);
int TakeAPicture(cv::Mat, int&);
int TakeAVideo(int, int&);
int DetectFace(int);