#ifndef _HANDLE_STREAM_H_
#define _HANDLE_STREAM_H_

#include <string>

#include <opencv2/highgui/highgui.hpp>


#define HANDLE_STREAM_DEFAULT_STREAM "0"


class HandleStream {
protected:
	static HandleStream* sHandleStream;

	bool mIsInit;
	bool mIsCamera;

	int mDebugTime;

	int mDumpImageTime;
	double mDumpImageFrameIndent;
	int mDumpSliderPosition;
	bool mIsManualChanged;

	std::string mStreamName;

	CvCapture* mCapture;

	std::string mSaveFileName;

	int mSaveFileCounter;

	std::string mSaveFileSuffixName;

	double mSaveFileImageFrameIndent;

	virtual int setCaptureFrame(const double frame);
	virtual double getCaptureFrame();
	virtual void dumpCaptureFrame();
	virtual double getCaptureFPS();
	virtual double getCaptureFrameCount();

	std::string intToString(const int number);

	static void globalOnTrackbarSlide(const int pos);
	void onTrackbarSlide(const int pos);
	
public:
	HandleStream();

	virtual ~HandleStream();

	// setter
	virtual void setDumpImageFrameIndent(const double dumpImageFrameIndent);
	virtual void setSaveFileImageFrameIndent(const double saveFileImageFrameIndent);
	virtual void setStream(const std::string streamName, const bool isCamera = true);
	virtual void setSaveFileName(const std::string saveFileName);

	// getter
	// TODO

	virtual void init();

	virtual void end();

	virtual IplImage* getImageCurrent();

	virtual IplImage* getImageFrame(const double frame);

	// save file
	virtual int saveFileCaptureImageOne(const double frame);
	virtual int saveFileCaptureImageAll();

	// dump method
	virtual void dumpCaptureProperty();
	virtual bool dumpCaptureImageOne(const double frame);
	virtual void dumpCaptureImageAll();
	virtual void dumpCaptureImageAllOnTrackBar();

	// play
	virtual void playCapture();
};

#endif // _HANDLE_STREAM_H_

