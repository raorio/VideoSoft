
#include "stdafx.h"

#include <sstream>
#include <string>

#include "HandleStream.h"


//#define HANDLE_STREAM_DEBUG

// query or grab and retrieve
//#define IS_USE_QUERY_FRAME


HandleStream* HandleStream::sHandleStream = NULL;


HandleStream::HandleStream() {
	mIsInit = false;
	mIsCamera = true;
	mStreamName = HANDLE_STREAM_DEFAULT_STREAM;
	mCapture = NULL;

	mDebugTime = 1000;

	mDumpImageTime = 1000;
	mDumpImageFrameIndent = 1000.0;
	mDumpSliderPosition = 0;
	mIsManualChanged = false;

	mSaveFileName = "handleStream-";
	mSaveFileCounter = 0;
	mSaveFileSuffixName = ".jpg";
	mSaveFileImageFrameIndent = 1000.0;
}

HandleStream::~HandleStream() {
	if (mIsInit == true) {
		end();
	}
}

void HandleStream::setDumpImageFrameIndent(const double dumpImageFrameIndent) {
	mDumpImageFrameIndent = dumpImageFrameIndent;
}

void HandleStream::setSaveFileImageFrameIndent(const double saveFileImageFrameIndent) {
	mSaveFileImageFrameIndent = saveFileImageFrameIndent;
}

void HandleStream::setStream(const std::string streamName, const bool isCamera) {
	mIsCamera = isCamera;
	mStreamName = streamName;
}

void HandleStream::setSaveFileName(const std::string saveFileName) {
	mSaveFileName = saveFileName;
}

IplImage* HandleStream::getImageCurrent() {
	IplImage* ret = NULL;

	if (mIsInit == false) {
		init();
	}

	if (mCapture == NULL) {
		return ret;
	}

#ifdef IS_USE_QUERY_FRAME // brab and retrieve or query
	ret = cvQueryFrame(mCapture);
	if (ret == NULL) {
		return ret;
	}
#else // brab and retrieve or query
	int error = 0;
	error = cvGrabFrame(mCapture);
	if (error < 0) {
		return ret;
	}

	ret = cvRetrieveFrame(mCapture);
	if (ret == NULL) {
		return ret;
	}
#endif // brab and retrieve or query

#ifdef HANDLE_STREAM_DEBUG
	std::string windowName = "HandleStreamDebug";
	cvShowImage(windowName.c_str(), ret);

	char key = cvWaitKey(mDebugTime);

	cvDestroyWindow(windowName.c_str());
#endif // HANDLE_STREAM_DEBUG

	return ret;
}

IplImage* HandleStream::getImageFrame(const double frame) {
	IplImage* ret = NULL;

	if (mIsInit == false) {
		init();
	}

	if (mCapture == NULL) {
		return ret;
	}

	int error = 0;

	if (frame >= 0.0) {
		error = setCaptureFrame(frame);
		if (error < 0) {
			return ret;
		}
	}

#ifdef IS_USE_QUERY_FRAME // brab and retrieve or query
	ret = cvQueryFrame(mCapture);
	if (ret == NULL) {
		return ret;
	}
#else // brab and retrieve or query
	error = cvGrabFrame(mCapture);
	if (error < 0) {
		return ret;
	}

	ret = cvRetrieveFrame(mCapture);
	if (ret == NULL) {
		return ret;
	}
#endif // brab and retrieve or query

#ifdef HANDLE_STREAM_DEBUG
	std::string windowName = "HandleStreamDebug";
	cvShowImage(windowName.c_str(), ret);

	char key = cvWaitKey(mDebugTime);

	cvDestroyWindow(windowName.c_str());
#endif // HANDLE_STREAM_DEBUG

	return ret;
}

void HandleStream::init() {
	if (mIsInit == true) {
		return;
	}

	if (mIsCamera == true) {
		// TODO
		// mStreamName to int
		int streamName = 0;
		mCapture = cvCaptureFromCAM(streamName);
	} else {
		mCapture = cvCaptureFromFile(mStreamName.c_str());
	}

	if (mCapture == NULL) {
		return;
	}

	mIsInit = true;
}

void HandleStream::end() {
	if (mIsInit == false) {
		return;
	}

	if (mCapture != NULL) {
		cvReleaseCapture(&mCapture);
	}
	
	mIsInit = false;
}

int HandleStream::saveFileCaptureImageOne(const double frame) {
	int ret = -1;

	if (mIsInit == false) {
		init();
	}

	if (mCapture == NULL) {
		return ret;
	}

	IplImage* image = getImageFrame(frame);
	if (image == NULL) {
		return ret;
	}
	
	std::string filename;
	std::string number;
	filename.append(mSaveFileName);
	number = intToString(mSaveFileCounter);
	mSaveFileCounter += 1;
	filename.append(number);
	filename.append(mSaveFileSuffixName);

	int error = cvSaveImage(filename.c_str(), image);
	if (error == false) {
		return ret;
	}

	ret = 0;

	return ret;
}

int HandleStream::saveFileCaptureImageAll() {
	int ret = -1;

	if (mIsInit == false) {
		init();
	}

	if (mCapture == NULL) {
		return ret;
	}
	
	double fps = getCaptureFPS();
	if (fps < 0.0) {
		fps = 30.0;
	}

	while (true) {
		IplImage* image = getImageCurrent();
		if (image == NULL) {
			break;
		}
		
		std::string filename;
		std::string number;
		filename.append(mSaveFileName);
		number = intToString(mSaveFileCounter);
		mSaveFileCounter += 1;
		filename.append(number);
		filename.append(mSaveFileSuffixName);

		int error = cvSaveImage(filename.c_str(), image);
		if (error == false) {
			return ret;
		}

		char key = cvWaitKey((int)(1000.0 / mSaveFileImageFrameIndent));
		if (key == 27) {
			break;
		}
	}

	return ret;
}

void HandleStream::dumpCaptureProperty() {
	if (mIsInit == false) {
		return;
	}

	if (mCapture == NULL) {
		return;
	}
	
	printf("StreamName(%s) dump start.\r\n", mStreamName.c_str());

	double value = 0.0;
	int param = 0;
	
	param = CV_CAP_PROP_POS_MSEC;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_POS_MSEC(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_POS_FRAMES;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_POS_FRAMES(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_POS_AVI_RATIO;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_POS_AVI_RATIO(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_FRAME_WIDTH;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_FRAME_WIDTH(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_FRAME_HEIGHT;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_FRAME_HEIGHT(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_FPS;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_FPS(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_FOURCC;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_FOURCC(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_FRAME_COUNT;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_FRAME_COUNT(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_FORMAT;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_FORMAT(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_MODE;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_MODE(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_BRIGHTNESS;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_BRIGHTNESS(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_CONTRAST;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_CONTRAST(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_SATURATION;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_SATURATION(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_HUE;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_HUE(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_GAIN;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_GAIN(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_EXPOSURE;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_EXPOSURE(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_CONVERT_RGB;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_CONVERT_RGB(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_WHITE_BALANCE;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_WHITE_BALANCE(%d) %lf\r\n", param, value);

	param = CV_CAP_PROP_RECTIFICATION;
	value = cvGetCaptureProperty(mCapture, param);
	printf("CV_CAP_PROP_RECTIFICATION(%d) %lf\r\n", param, value);

	printf("StreamName(%s) dump end.\r\n", mStreamName.c_str());
}

bool HandleStream::dumpCaptureImageOne(const double frame) {
	bool ret = false;

	if (mIsInit == false) {
		init();
	}

	if (mCapture == NULL) {
		return ret;
	}

	IplImage* image = getImageFrame(frame);
	if (image == NULL) {
		return ret;
	}
	
	std::string windowName = "HandleStreamDump frame";
	cvShowImage(windowName.c_str(), image);

	char key = cvWaitKey(mDumpImageTime);

	cvDestroyWindow(windowName.c_str());

	ret = true;

	return ret;
}

void HandleStream::dumpCaptureImageAll() {
	if (mIsInit == false) {
		init();
	}

	if (mCapture == NULL) {
		return;
	}
	
	std::string windowName = "HandleStreamDump video";
	cv::namedWindow (windowName.c_str(), CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

	double fps = getCaptureFPS();
	if (fps < 0.0) {
		fps = 30.0;
	}

	while (true) {
		IplImage* image = getImageCurrent();
		if (image == NULL) {
			break;
		}
		
		cvShowImage(windowName.c_str(), image);

		char key = cvWaitKey((int)(mDumpImageTime / fps));
		if (key == 27) {
			break;
		}
	}

	cvDestroyWindow(windowName.c_str());
}

// refer http://hyakuren-soft.sakura.ne.jp/opencv_practice/chapter_02_page.html#chapter_02_show_movie_2nd
void HandleStream::dumpCaptureImageAllOnTrackBar() {
	if (mIsInit == false) {
		init();
	}

	if (mCapture == NULL) {
		return;
	}

	std::string windowName = "HandleStreamDump video";
	cv::namedWindow (windowName.c_str(), CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

	double fps = getCaptureFPS();
	if (fps < 0.0) {
		fps = 30.0;
	}

	int frameCount = (int)getCaptureFrameCount();
	if (frameCount < 0) {
		return;
	}
	
	std::string trackbarName = "Position";
	CvTrackbarCallback callback = NULL;
	callback = globalOnTrackbarSlide;
	int error = cvCreateTrackbar(trackbarName.c_str(), windowName.c_str(), &mDumpSliderPosition, frameCount, callback);
	if (error < 0) {
		return;
	}

	sHandleStream = this;

	while (true) {
		IplImage* image = getImageCurrent();
		if (image == NULL) {
			break;
		}
		
		double frame = getCaptureFrame();
		cvSetTrackbarPos(trackbarName.c_str(), windowName.c_str(), (int)frame);
		mIsManualChanged = false;
		cvShowImage(windowName.c_str(), image);
		char key = cvWaitKey((int)(mDumpImageTime / fps));
		if (key == 27) {
			break;
		}
	}

	cvDestroyWindow(windowName.c_str());

	sHandleStream = NULL;
}

void HandleStream::globalOnTrackbarSlide(const int pos) {
	if (sHandleStream != NULL) {
		sHandleStream->onTrackbarSlide(pos);
	}
}

void HandleStream::onTrackbarSlide(const int pos) {
	if (mIsManualChanged == true) {
		if (mCapture != NULL) {
			cvSetCaptureProperty(mCapture, CV_CAP_PROP_POS_FRAMES, pos);
		}
	}
	mIsManualChanged = true;
}

// refer http://www.kkaneko.com/rinkou/opencv/avivideo.html
void HandleStream::playCapture() {
	double width;  // 幅
	double height; // 高さ
	double fps; // フレームレート
	double msec; // 現在位置
	double index = -1; // フレームのインデックス
	double ratio; // 相対位置

	IplImage *frame = 0;
	double prev_index; 
	int ch;

	if (mIsInit == false) {
		init();
	}

	if (mCapture == NULL) {
		return;
	}

	// 幅と高さの取得
	width = cvGetCaptureProperty(mCapture, CV_CAP_PROP_FRAME_WIDTH);
	height = cvGetCaptureProperty(mCapture, CV_CAP_PROP_FRAME_HEIGHT);
	fps = cvGetCaptureProperty(mCapture, CV_CAP_PROP_FPS);

	std::string windowName = "Video File";
	std::string showImageName = "HandleStream play";
	cv::namedWindow (windowName.c_str(), CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

	while (1) {
		frame = cvQueryFrame(mCapture);

		msec = cvGetCaptureProperty(mCapture, CV_CAP_PROP_POS_MSEC);
		prev_index = index; 
		index = cvGetCaptureProperty(mCapture, CV_CAP_PROP_POS_FRAMES);
		ratio = cvGetCaptureProperty(mCapture, CV_CAP_PROP_POS_AVI_RATIO);

		cvShowImage (showImageName.c_str(), frame);
		ch = cvWaitKey ((int)(1000.0 / fps)); // 0 はディレイ時間 (ミリ秒単位)
		if (ch == '\x1b') {
			// ESC キー
			break;
		}
#ifdef HANDLE_STREAM_DEBUG
		fprintf( stderr, "width = %f, height = %f, fps = %f, index = %f, msec = %f\n", width, height, fps, index, msec );
#endif // HANDLE_STREAM_DEBUG
		if (prev_index == index) {
			break;
			cvSetCaptureProperty(mCapture, CV_CAP_PROP_POS_AVI_RATIO, 0.0);
		}
	}

	cvDestroyWindow(showImageName.c_str());
}

int HandleStream::setCaptureFrame(const double frame) {
#ifdef HANDLE_STREAM_DEBUG
	dumpCaptureFrame();
#endif // HANDLE_STREAM_DEBUG

	int param = CV_CAP_PROP_POS_FRAMES;
	double value = frame;
	int ret = cvSetCaptureProperty(mCapture, param, value);

#ifdef HANDLE_STREAM_DEBUG
	dumpCaptureFrame();
#endif // HANDLE_STREAM_DEBUG

	return ret;
}

double HandleStream::getCaptureFrame() {
	double ret = 0.0;

	int param = CV_CAP_PROP_POS_FRAMES;
	ret = cvGetCaptureProperty(mCapture, param);

	return ret;
}

void HandleStream::dumpCaptureFrame() {
	double value = getCaptureFrame();

	printf("CV_CAP_PROP_FRAME_COUNT(%d) %lf\r\n", CV_CAP_PROP_FRAME_COUNT, value);
}

double HandleStream::getCaptureFPS() {
	double ret = 0.0;

	int param = CV_CAP_PROP_FPS;
	ret = cvGetCaptureProperty(mCapture, param);

	return ret;
}

double HandleStream::getCaptureFrameCount() {
	double ret = 0.0;

	int param = CV_CAP_PROP_FRAME_COUNT;
	ret = cvGetCaptureProperty(mCapture, param);

	return ret;
}

std::string HandleStream::intToString(const int number) {
	std::stringstream stringStream;
	stringStream << number;
	return stringStream.str();
}

