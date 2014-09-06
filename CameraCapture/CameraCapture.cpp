
#include <iostream>

#include <opencv2/highgui/highgui.hpp>

#define NAME_OF_WINDOW	"CameraCapture"

int main(int argc, char** argv)
{
	int ret = 0;

    cv::VideoCapture cap;

	cap.open(0);

	if(cap.isOpened() == false)
    {
        std::cout << "Could not initialize capturing...\n";
        return -1;
    }

	cv::namedWindow(NAME_OF_WINDOW, 0);

	std::cout << "start camera capture\n";

	while (true) {
		cv::Mat frame;
		std::cout << "start capture\n";
        cap >> frame;
		std::cout << "end capture\n";
        if(frame.empty() == true) {
			std::cout << "Could not get frame...\n";
            break;
		}
		
		std::cout << "start image show\n";
		cv::imshow(NAME_OF_WINDOW, frame);
		std::cout << "end image show\n";

		if (false) {
			try {
				cv::imwrite("sample.jpg", frame);
			} catch (std::runtime_error& ex) {
				fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
				break;
			}
		}

		int c = cv::waitKey(30);
		if( c == 'q' || c == 'Q' || (c & 255) == 27 ) {
			std::cout << "quit capture\n";
            break;
		}

	}

	std::cout << "end camera capture\n";

	return ret;
}
