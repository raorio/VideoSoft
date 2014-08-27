
#include "stdafx.h"

#include "ImageUtile.h"


//#define IMAGE_UTILE_DEBUG


int ImageUtile::sDebugTime = 1000;


ImageUtile::ImageUtile() {
}

ImageUtile::~ImageUtile() {
}

IplImage* ImageUtile::combineImage(const IplImage* image1, const IplImage* image2) {
	IplImage* ret = NULL;

	if (image1 == NULL) {
		return ret;
	}

	if (image2 == NULL) {
		return ret;
	}

	if (image1->imageSize != image2->imageSize) {
		return ret;
	}

	ret = cvCloneImage(image1);
	if (ret == NULL) {
		return ret;
	}

	unsigned char* retPixels = (unsigned char*)ret->imageData;
	unsigned char* image2Pixels = (unsigned char*)image2->imageData;
	
	for(int i = 0; i < image1->imageSize; i++){
		// 平均値なので、複数合成する場合、後の画像が有効性が高い
		retPixels[i] = (retPixels[i] + image2Pixels[i]) / 2;
	}

#ifdef IMAGE_UTILE_DEBUG
	std::string windowName = "ImageUtileDebug";
	cvShowImage(windowName.c_str(), ret);

	cvWaitKey(sDebugTime);

	cvDestroyWindow(windowName.c_str());
#endif // IMAGE_UTILE_DEBUG

	return ret;
}

