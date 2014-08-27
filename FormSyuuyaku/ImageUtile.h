#ifndef _IMAGE_UTILE_H_
#define _IMAGE_UTILE_H_

#include <string>

#include <opencv2/highgui/highgui.hpp>



class ImageUtile {
public:
	static int sDebugTime;

	ImageUtile();

	virtual ~ImageUtile();

	static IplImage* combineImage(const IplImage* image1, const IplImage* image2);
};

#endif // _IMAGE_UTILE_H_

