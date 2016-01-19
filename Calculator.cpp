#include "Calculator.h"
#include <QDir>
using namespace std;
using namespace cv;

bool Calculator::pointInContours(int **data, int m, int n, cv::Point point){
	if(!data){
		return false;
	}

	int x = point.x;
	int y = point.y;

	//点就在轮廓上
	if(data[x][y] == 255){
		return true;
	}

	//判断点是否在轮廓内部
	int rayInnConturs = 0;					//穿过奇数个轮廓的射线数量，表明点在轮廓内部
	int rayNotInContours = 0;				//穿过偶数个轮廓的射线数量，表明点在轮廓外部
	int contours = 0;						//射线经过的轮廓的数量，奇数则rayInnContours++，偶数则rayNotInContours++
	int px = x, py = y;						//坐标的副本

	//x轴正方向的射线 px++
	contours = 0;						
	px = x, py = y;
	while(px < m - 1){
		if(data[px][py] == 0 && data[px + 1][py] == 255)
			contours ++;
		px ++;
	}
	if(contours % 2 == 0)
		rayNotInContours ++;
	else
		rayInnConturs ++;

	//x轴负方向的射线 px--
	contours = 0;						
	px = x, py = y;
	while(px > 0){
		if(data[px][py] == 0 && data[px - 1][py] == 255)
			contours ++;
		px --;
	}
	if(contours % 2 == 0)
		rayNotInContours ++;
	else
		rayInnConturs ++;

	//y轴正方向的射线 py++
	contours = 0;						
	px = x, py = y;
	while(py < n - 1){
		if(data[px][py] == 0 && data[px][py + 1] == 255)
			contours ++;
		py++;
	}
	if(contours % 2 == 0)
		rayNotInContours ++;
	else
		rayInnConturs ++;

	//y轴负方向的射线 py--
	contours = 0;						
	px = x, py = y;
	while(py > 0){
		if(data[px][py] == 0 && data[px][py - 1] == 255)
			contours ++;
		py--;
	}
	if(contours % 2 == 0)
		rayNotInContours ++;
	else
		rayInnConturs ++;


	//+x, +y方向的射线 px++ py++
	contours = 0;						
	px = x, py = y;
	while(px < m - 1 && py < n - 1){
		if(data[px][py] == 0 && data[px + 1][py + 1] == 255)
			contours ++;
		px ++;
		py ++;
	}
	if(contours % 2 == 0)
		rayNotInContours ++;
	else
		rayInnConturs ++;

	//+x, -y方向的射线 px++ py--
	contours = 0;						
	px = x, py = y;
	while(px < m - 1 && py > 0){
		if(data[px][py] == 0 && data[px + 1][py - 1] == 255)
			contours ++;
		px ++;
		py --;
	}
	if(contours % 2 == 0)
		rayNotInContours ++;
	else
		rayInnConturs ++;

	//-x, +y方向的射线 px-- py++
	contours = 0;						
	px = x, py = y;
	while(px > 0 && py < n - 1){
		if(data[px][py] == 0 && data[px - 1][py + 1] == 255)
			contours ++;
		px --;
		py ++;
	}
	if(contours % 2 == 0)
		rayNotInContours ++;
	else
		rayInnConturs ++;

	//-x, -y方向的射线 px-- py--
	contours = 0;						
	px = x, py = y;
	while(px > 0 && py > 0){
		if(data[px][py] == 0 && data[px - 1][py - 1] == 255)
			contours ++;
		px --;
		py --;
	}
	if(contours % 2 == 0)
		rayNotInContours ++;
	else
		rayInnConturs ++;

	if(rayInnConturs >= rayNotInContours){
		return true;
	} else {
		return false;
	}
}

QPixmap Calculator::Mat2QPixmap(cv::Mat &image){
	Mat rgb;  
	QImage img;  
	if(image.channels() == 3)    // RGB image  
	{  
		cvtColor(image,rgb,CV_BGR2RGB);  
		img = QImage((const uchar*)(rgb.data),  //(const unsigned char*)  
			rgb.cols,rgb.rows,  
			rgb.cols*rgb.channels(),   //new add  
			QImage::Format_RGB888);  
	}else                     // gray image  
	{  
		img = QImage((const uchar*)(image.data),  
			image.cols,image.rows,  
			image.cols*image.channels(),    //new add  
			QImage::Format_Indexed8);  
	}

	QPixmap imgdata = QPixmap::fromImage(img);
	return imgdata;
}

bool Calculator::removeDirWithContent(const QString &dirName){  
	static QVector<QString> dirNames;  
	static QString funcErrMsg="删除[%1]失败.";  
	static QString funcInfFndMsg="发现[%1].";  
	static QString funcInfDelMsg="删除[%1]成功.";  
	QDir dir;  
	QFileInfoList filst;  
	QFileInfoList::iterator curFi;  
	//初始化
	dirNames.clear();  
	if(dir.exists()){  
		dirNames<<dirName;  
	}  
	else{  
		return true;  
	}  
	//遍历各级文件夹，并将这些文件夹中的文件删除  
	for(int i=0;i<dirNames.size();++i){  
		dir.setPath(dirNames[i]);  
		filst=dir.entryInfoList(QDir::Dirs|QDir::Files  
			|QDir::Readable|QDir::Writable  
			|QDir::Hidden|QDir::NoDotAndDotDot  
			,QDir::Name);  
		if(filst.size()>0){  
			curFi=filst.begin();  
			while(curFi!=filst.end()){  
				//遇到文件夹,则添加至文件夹列表dirs尾部  
				if(curFi->isDir()){  
					dirNames.push_back(curFi->filePath());  
				}else if(curFi->isFile()){  
					//遇到文件,则删除之  
					if(!dir.remove(curFi->fileName())){  
						return false;  
					}  
				}  
				curFi++;  
			}//end of while  
		}  
	}  
	//删除文件夹  
	for(int i=dirNames.size()-1;i>=0;--i){  
		dir.setPath(dirNames[i]);  
		if(!dir.rmdir(".")){  
			return false;  
		}  
	}   
	return true;  
}  
