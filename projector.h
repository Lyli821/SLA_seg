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
	//��Ա����
	void showBG();
	void showImage(int imgID);					//��ʾ����
	void showImage(int imgID, int blockID);		//��ʾ�ֿ�
	void hideImage();							//����ʾ
	void pushback(int index, QPixmap *);					//����
	void pushback(int index, cv::Mat *);					//����
	void pushback();
	void clearImgList();						//��ʼ��
	int num(int index);


public:
	//��Ա����
	vector<vector<QPixmap *>> imgList;		//ͼƬ�б�
	vector<vector<cv::Mat *>> matList;		//ͼƬ�б�
	QLabel *imgTable;
	QPixmap *bg;

	QRect rect0;
	QRect rect1;
};

#endif