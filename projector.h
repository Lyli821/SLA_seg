#ifndef PROJECTOR_H

#include <QWidget>
#include <QLabel>

#include <cv.h>
#include <vector>

using namespace std;


class Projector:public QWidget{
	Q_OBJECT

public:
	Projector(QWidget *parent = 0);
	~Projector();

public:
	//成员函数
	void showBG();
	void showImage(int imgID);					//显示层数
	void showImage(int imgID, int blockID);		//显示分块
	void hideImage();							//不显示
	void pushback(int index, QPixmap *);					//进入
	void pushback(int index, cv::Mat *);					//进入
	void pushback();
	void clearImgList();						//初始化
	int num(int index);


public:
	//成员变量
	vector<vector<QPixmap *>> imgList;		//图片列表
	vector<vector<cv::Mat *>> matList;		//图片列表
	QLabel *imgTable;
	QPixmap *bg;

	QRect rect0;
	QRect rect1;
};

#endif