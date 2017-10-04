#include <sstream>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv\cv.hpp"

#include "functionale.h"


	int main()
	{
		int counterofcams = 0, counteroftakenpictures = 0, counterofvideos = 0;
		DetectHowMuchCamsHere(counterofcams);
		std::cout << "Welcome to my Camera program!" << std::endl;
		std::cout << "Number of available cameras: " << counterofcams << std::endl << std::endl;
		std::cout << "Push 'p' to take a picture" << std::endl;
		std::cout << "Push 'space' to record a video" << std::endl;
		std::cout << "Push 'z' to detect a face" << std::endl;
		std::cout << "Press 'esc' to quit" << std::endl << std::endl;
		std::cout << "Now pick a cam and have fun!" << std::endl;
		ShowCam(PickACam(counterofcams), counteroftakenpictures, counterofvideos);
		return 0;
	}