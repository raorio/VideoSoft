// FormSyuuyaku.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <opencv2/highgui/highgui.hpp>

#include "HandleStream.h"
#include "ImageUtile.h"


// test video file
//#define TEST_STREAM_FILE "C:\\OpenCV2.2\\samples\\cpp\\Qt_sample\\cube4.avi"
//#define TEST_STREAM_FILE "C:\\Users\\Public\\Videos\\Corel Sample Videos\\NTSC_02.mpg"
#define TEST_STREAM_FILE "C:\\Users\\waon\\Desktop\\hide\\video\\tennis\\Converted\\DVD001C.mp4"

#define TEST_VIDEO_INDENT_FRAME 30.0
//#define TEST_VIDEO_INDENT_FRAME 500000.0

// test image file
#define TEST_IMAGE_FILE_MODE 2
#if TEST_IMAGE_FILE_MODE == 1
#define TEST_IMAGE_FILE_1 "C:\\Users\\Public\\Pictures\\Sample Pictures\\1.jpg"
#define TEST_IMAGE_FILE_2 "C:\\Users\\Public\\Pictures\\Sample Pictures\\2.jpg"
#define TEST_IMAGE_FILE_3 "C:\\Users\\Public\\Pictures\\Sample Pictures\\3.jpg"
#define TEST_IMAGE_FILE_4 "C:\\Users\\Public\\Pictures\\Sample Pictures\\4.jpg"
#define TEST_IMAGE_FILE_5 "C:\\Users\\Public\\Pictures\\Sample Pictures\\5.jpg"
#define TEST_IMAGE_FILE_6 "C:\\Users\\Public\\Pictures\\Sample Pictures\\6.jpg"
#define TEST_IMAGE_FILE_7 "C:\\Users\\Public\\Pictures\\Sample Pictures\\7.jpg"
#define TEST_IMAGE_FILE_8 "C:\\Users\\Public\\Pictures\\Sample Pictures\\8.jpg"
#elif TEST_IMAGE_FILE_MODE == 2
#define TEST_IMAGE_FILE_1 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-104.jpg"
#define TEST_IMAGE_FILE_2 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-108.jpg"
#define TEST_IMAGE_FILE_3 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-112.jpg"
#define TEST_IMAGE_FILE_4 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-116.jpg"
#define TEST_IMAGE_FILE_5 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-120.jpg"
#define TEST_IMAGE_FILE_6 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-124.jpg"
#define TEST_IMAGE_FILE_7 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-128.jpg"
#define TEST_IMAGE_FILE_8 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-132.jpg"
#elif TEST_IMAGE_FILE_MODE == 3
#define TEST_IMAGE_FILE_1 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-105.jpg"
#define TEST_IMAGE_FILE_2 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-110.jpg"
#define TEST_IMAGE_FILE_3 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-115.jpg"
#define TEST_IMAGE_FILE_4 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-120.jpg"
#define TEST_IMAGE_FILE_5 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-125.jpg"
#define TEST_IMAGE_FILE_6 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-130.jpg"
#define TEST_IMAGE_FILE_7 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-135.jpg"
#define TEST_IMAGE_FILE_8 "C:\\Users\\waon\\Desktop\\soft\\myVideoSoft\\FormSyuuyaku\\img\\handleStream-140.jpg"
#endif

void dumpHandleStreamCamera() {
	std::string streamName;
	streamName = HANDLE_STREAM_DEFAULT_STREAM;

	HandleStream handleStream;

	// camera
	handleStream.setStream(streamName, true);

	handleStream.setDumpImageFrameIndent(TEST_VIDEO_INDENT_FRAME);

	handleStream.init();

	handleStream.dumpCaptureProperty();
	
	double frame = -1.0;
	//handleStream.dumpCaptureImageOne(frame);
	handleStream.dumpCaptureImageAll();

	handleStream.end();
}

void dumpHandleStreamVideo() {
	std::string streamName;
	streamName = TEST_STREAM_FILE;

	HandleStream handleStream;

	// video file
	handleStream.setStream(streamName, false);

	handleStream.setDumpImageFrameIndent(TEST_VIDEO_INDENT_FRAME);

	handleStream.init();

	handleStream.dumpCaptureProperty();
	
	double frame = 4000000.0;
	//handleStream.dumpCaptureImageOne(frame);
	handleStream.dumpCaptureImageAll();

	handleStream.end();
}

void dumpHandleStreamVideoOnTrackBar() {
	std::string streamName;
	streamName = TEST_STREAM_FILE;

	HandleStream handleStream;

	// video file
	handleStream.setStream(streamName, false);

	handleStream.setDumpImageFrameIndent(TEST_VIDEO_INDENT_FRAME);

	handleStream.init();

	handleStream.dumpCaptureProperty();
	
	handleStream.dumpCaptureImageAllOnTrackBar();

	handleStream.end();
}

void playHandleStreamCamera() {
	std::string streamName;
	streamName = HANDLE_STREAM_DEFAULT_STREAM;

	HandleStream handleStream;

	// camera
	handleStream.setStream(streamName, true);

	handleStream.setDumpImageFrameIndent(TEST_VIDEO_INDENT_FRAME);

	handleStream.init();

	handleStream.dumpCaptureProperty();
	
	handleStream.playCapture();

	handleStream.end();
}

void playHandleStreamVideo() {
	std::string streamName;
	streamName = TEST_STREAM_FILE;

	HandleStream handleStream;

	// video file
	handleStream.setStream(streamName, false);

	handleStream.setDumpImageFrameIndent(TEST_VIDEO_INDENT_FRAME);

	handleStream.init();

	handleStream.dumpCaptureProperty();
	
	handleStream.playCapture();

	handleStream.end();
}

void saveHandleStreamCamera() {
	std::string streamName;
	streamName = HANDLE_STREAM_DEFAULT_STREAM;

	HandleStream handleStream;

	// camera
	handleStream.setStream(streamName, true);

	handleStream.setSaveFileImageFrameIndent(TEST_VIDEO_INDENT_FRAME);

	std::string fileName = "img\\handleStream-";
	handleStream.setSaveFileName(fileName);

	handleStream.init();

	handleStream.dumpCaptureProperty();
	
	double frame = -1.0;
	//handleStream.saveFileCaptureImageOne(frame);
	handleStream.saveFileCaptureImageAll();

	handleStream.end();
}

void saveHandleStreamVideo() {
	std::string streamName;
	streamName = TEST_STREAM_FILE;

	HandleStream handleStream;

	// video file
	handleStream.setStream(streamName, false);

	handleStream.setSaveFileImageFrameIndent(TEST_VIDEO_INDENT_FRAME);

	std::string fileName = "img\\handleStream-";
	handleStream.setSaveFileName(fileName);

	handleStream.init();

	handleStream.dumpCaptureProperty();
	
	double frame = 4000000.0;
	//handleStream.saveFileCaptureImageOne(frame);
	handleStream.saveFileCaptureImageAll();

	handleStream.end();
}

void sampleImageUtileCombineImage() {
	int dumpTime = 5000;
	std::string windowName = "sampleImageUtileCombineImage";

	std::string imagePath1;
	std::string imagePath2;
	std::string imagePath3;
	std::string imagePath4;
	std::string imagePath5;
	std::string imagePath6;
	std::string imagePath7;
	std::string imagePath8;

	imagePath1 = TEST_IMAGE_FILE_1;
	imagePath2 = TEST_IMAGE_FILE_2;
	imagePath3 = TEST_IMAGE_FILE_3;
	imagePath4 = TEST_IMAGE_FILE_4;
	imagePath5 = TEST_IMAGE_FILE_5;
	imagePath6 = TEST_IMAGE_FILE_6;
	imagePath7 = TEST_IMAGE_FILE_7;
	imagePath8 = TEST_IMAGE_FILE_8;

	IplImage* image1 = NULL;
	IplImage* image2 = NULL;
	IplImage* image3 = NULL;
	IplImage* image4 = NULL;
	IplImage* image5 = NULL;
	IplImage* image6 = NULL;
	IplImage* image7 = NULL;
	IplImage* image8 = NULL;

	image1 = cvLoadImage(imagePath1.c_str());
	if (image1 == NULL) {
		return;
	}
	image2 = cvLoadImage(imagePath2.c_str());
	if (image2 == NULL) {
		return;
	}
	image3 = cvLoadImage(imagePath3.c_str());
	if (image3 == NULL) {
		return;
	}
	image4 = cvLoadImage(imagePath4.c_str());
	if (image4 == NULL) {
		return;
	}
	image5 = cvLoadImage(imagePath5.c_str());
	if (image5 == NULL) {
		return;
	}
	image6 = cvLoadImage(imagePath6.c_str());
	if (image6 == NULL) {
		return;
	}
	image7 = cvLoadImage(imagePath7.c_str());
	if (image7 == NULL) {
		return;
	}
	image8 = cvLoadImage(imagePath8.c_str());
	if (image8 == NULL) {
		return;
	}

	IplImage* retImage1 = NULL;
	IplImage* retImage2 = NULL;
	IplImage* retImage3 = NULL;
	IplImage* retImage4 = NULL;
	IplImage* retImage5 = NULL;
	IplImage* retImage6 = NULL;
	IplImage* retImage7 = NULL;
	
	retImage1 = ImageUtile::combineImage(image1, image2);
	if (retImage1 == NULL) {
		return;
	}

	cvShowImage(windowName.c_str(), retImage1);

	cvWaitKey(dumpTime);

	retImage2 = ImageUtile::combineImage(retImage1, image3);
	if (retImage2 == NULL) {
		return;
	}

	cvShowImage(windowName.c_str(), retImage2);

	cvWaitKey(dumpTime);

	retImage3 = ImageUtile::combineImage(retImage2, image4);
	if (retImage3 == NULL) {
		return;
	}

	cvShowImage(windowName.c_str(), retImage3);

	cvWaitKey(dumpTime);

	retImage4 = ImageUtile::combineImage(retImage3, image5);
	if (retImage4 == NULL) {
		return;
	}

	cvShowImage(windowName.c_str(), retImage4);

	cvWaitKey(dumpTime);

	retImage5 = ImageUtile::combineImage(retImage4, image6);
	if (retImage5 == NULL) {
		return;
	}

	cvShowImage(windowName.c_str(), retImage5);

	cvWaitKey(dumpTime);

	retImage6 = ImageUtile::combineImage(retImage5, image7);
	if (retImage6 == NULL) {
		return;
	}

	cvShowImage(windowName.c_str(), retImage6);

	cvWaitKey(dumpTime);

	retImage7 = ImageUtile::combineImage(retImage6, image8);
	if (retImage7 == NULL) {
		return;
	}

	cvShowImage(windowName.c_str(), retImage7);

	cvWaitKey(dumpTime);


	cvDestroyWindow(windowName.c_str());

	cvReleaseImage(&image1);
	cvReleaseImage(&image2);
	cvReleaseImage(&image3);
	cvReleaseImage(&image4);
	cvReleaseImage(&image5);
	cvReleaseImage(&image6);
	cvReleaseImage(&image7);
	cvReleaseImage(&image8);
	
	cvReleaseImage(&retImage1);
	cvReleaseImage(&retImage2);
	cvReleaseImage(&retImage3);
	cvReleaseImage(&retImage4);
	cvReleaseImage(&retImage5);
	cvReleaseImage(&retImage6);
	cvReleaseImage(&retImage7);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int mode = 0;
	int modeChild = 0;
	int camera = 0;

	//mode = 0; // dump
	//mode = 1; // save
	mode = 2; // combine
	//mode = 3; // play

	//modeChild = 0;
	modeChild = 1;

	camera = 0; // video
	//camera = 1; // camera

	if (mode == 0) {
		if (camera == 0) {
			if (modeChild == 0) {
				dumpHandleStreamVideo();
			} else {
				dumpHandleStreamVideoOnTrackBar();
			}
		} else {
			dumpHandleStreamCamera();
		}
	} else if (mode == 1) {
		if (camera != 0) {
			saveHandleStreamCamera();
		} else {
			saveHandleStreamVideo();
		}
	} else if (mode == 2) {
		sampleImageUtileCombineImage();
	} else if (mode == 3) {
		if (camera != 0) {
			playHandleStreamCamera();
		} else {
			playHandleStreamVideo();
		}
	}

	cvDestroyAllWindows();

	return 0;
}

