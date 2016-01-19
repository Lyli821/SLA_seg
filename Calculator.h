#ifndef _CALCULATOR_H_
#define	_CALCULATOR_H_

#include "cv.h"
#include <QPixmap>

class Calculator{
private:

public:
	static bool pointInContours(int **data, int m, int n, cv::Point point);

	static QPixmap Mat2QPixmap(cv::Mat &image);

	static bool removeDirWithContent(const QString &dirName);
	
};

#endif