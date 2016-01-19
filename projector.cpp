#include "projector.h"
#include <QDesktopWidget>
#include <QApplication>


#include "Calculator.h"
#include "highgui.h"

using namespace std;
using namespace cv;

Projector::Projector(QWidget *parent /* = 0 */)
	:QWidget(parent)
{
	//多显示屏设置
	QDesktopWidget *desktop = QApplication::desktop();

	int deskID = desktop->primaryScreen();
	int deskCount = desktop->screenCount();

	for(int i = deskID; i < deskCount; i ++){
		QRect rect = desktop->screenGeometry(i);
		printf("num %d\tw = %d, h = %d\n", i, rect.width(), rect.height());
	}

	if (deskCount < 2){
		printf("no projector!\n");
		

		this->setWindowOpacity(1);
		//this->setWindowFlags(Qt::FramelessWindowHint);      
		this->setAutoFillBackground(true);
		QPalette palette;
		palette.setColor(QPalette::Background, QColor(0,0,0));
		this->setPalette(palette);

		rect0 = desktop->screenGeometry(deskID);
		rect1 = QRect(rect0.width() / 4, rect0.height() / 4, rect0.width() / 2, rect0.height() / 2);
		this->setFixedSize(rect1.size());
		this->move(rect0.width() / 4, rect0.height() / 4);

	} else {
		this->setWindowOpacity(1);
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setAutoFillBackground(true);
		QPalette palette;
		palette.setColor(QPalette::Background, QColor(0,0,0));
		this->setPalette(palette);

		rect0 = desktop->screenGeometry(deskID);
		rect1 = desktop->screenGeometry(deskID + 1);
		this->setFixedSize(rect1.size());
		this->move(rect0.width(), 0);
	}

	imgTable = new QLabel(this);
	imgTable->setVisible(false);

	//设置背景图片
	cv::Mat mat(rect1.height(), rect1.height(), CV_8UC1, cv::Scalar(255));
	bg = new QPixmap(Calculator::Mat2QPixmap(mat));

	//垃圾回收
	//delete desktop;	//会出现问题
}

Projector::~Projector(){
	clearImgList();
}

void Projector::showBG(){

	int x = rect1.width() - bg->width();
	int y = rect1.height() - bg->height();

	imgTable->setPixmap(*bg);
	imgTable->move(x, y);
	imgTable->setVisible(true);
}

void Projector::showImage(int imgID){
}

void Projector::showImage(int imgID, int blockID){
	//获取图片位置
	int index = imgID;
	float scale = float(rect1.height()) / float(imgList[index][blockID]->height());
	

	QPixmap *image = new QPixmap(imgList[index][blockID]->scaled(imgList[index][blockID]->width() * scale, imgList[index][blockID]->height() * scale));
	int x = rect1.width() - image->width();
	int y = rect1.height() - image->height();

	imgTable->setPixmap(*image);
	imgTable->move(x, y);
	imgTable->setVisible(true);

	//垃圾回收
	delete image;
}

void Projector::hideImage(){
	imgTable->setVisible(false);
}

void Projector::pushback(int index, QPixmap *image){
	imgList[index].push_back(image);
}

void Projector::pushback(int index, Mat *mat){
	matList[index].push_back(mat);
}

void Projector::pushback(){
	vector<QPixmap *> imgs;
	vector<cv::Mat *> mats;
	imgList.push_back(imgs);
	matList.push_back(mats);
}

void Projector::clearImgList(){
	for(int i = 0; i < imgList.size(); i ++){
		for(int j = 0; j < imgList[j].size(); j++){
			delete imgList[i][j];
		}
		imgList[i].clear();
	}
	for(int i = 0; i < matList.size(); i ++){
		for(int j = 0; j < matList[j].size(); j++){
			delete matList[i][j];
		}
		matList[i].clear();
	}
	imgList.clear();
	matList.clear();
}

int Projector::num(int index){
	return imgList[index].size();
}
