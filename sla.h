#ifndef SLA_H
#define SLA_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <vector>
#include "ui_sla.h"
#include "Serial/win_qextserialport.h"
#include "projector.h"
#include "MyWidget.h"

using namespace std;

enum PRINTERMODE {NORMAL, PRINTING, PAUSE, STOP};


class SLAFile{
public:

	SLAFile(){
		prefix = "";
		filename = "";
		fileroot = "";
	}
	SLAFile(QString filepath){
		fileroot = filepath.left(filepath.lastIndexOf('/') + 1);
		filename = filepath.mid(filepath.lastIndexOf('/') + 1, filepath.lastIndexOf('.') - filepath.lastIndexOf('/') - 1);
		prefix = filepath.right(filepath.length() - filepath.lastIndexOf('.') - 1);
	}

	QString prefix;
	QString filename;
	QString fileroot;
};

//G代码，打印代码
class Gcode{
public:
	Gcode(QString line){
		this->line = line;
		words = line.split(" ");
	}
	QString		line;			//原代码，行
	QStringList words;			//单词分割

};

class SLA : public QMainWindow
{
	Q_OBJECT

public:
	SLA(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SLA();

//成员函数
public:
	void parainit();

//响应函数
public slots:
	//setting view
	void cbComChanged(const QString& comName);			//端口号更改响应
	void cbBaudChanged(const QString& baudName);		//波特率更改响应
	void btnConnectClicked();							//连接端口
	void btnDisconnectClicked();						//断开端口
	void btnSaveParameterClicked();						//保存打印参数设置
	void btnCancelParameterClicked();					//取消设置
	void btnLoadClicked();								//加载模型
	void btnGenerateClicked();							//生成G Code

	//model layer
	void btnLoadModelClicked();							//加载模型
	void btnSliceClicked();								//切割
	void eScaleRateChecked();							//文本框更改
	void eRxChecked();									//旋转角度更改
	void eRyChecked();
	void eRzChecked();
	void eMxChecked();									//旋转角度更改
	void eMyChecked();
	void eMzChecked();

	//comtrol view
	void sliderUpChanged(int value);					//滚轮
	void sliderDownChanged(int value);					//滚轮
	void btnUpClicked();								//Up按钮
	void btnDownClicked();								
	void btnUpHomeClicked();
	void btnDownHomeClicked();
	void btnLeftClicked();
	void btnRightClicked();
	void btnStartClicked();
	void btnStopClicked();
	void btnPauseClicked();
	void btnContinueClicked();


	//projector view
	void btnStartProjectorClicked();
	void btnEndProjectorClicked();

	//read & write
	void readMyCom();
	void writeMyCom(QString &qdata);
	void parsingGcode();								//解析Gcode，运行程序

private:
	void closeEvent(QCloseEvent *event);
	void warning(QString &warning);						//显示警告
	void parsing(QString &receiveMsg);					//解析芯片发送过来的字符串
	void readPath(QString dataFolder);                  //更新centers_set和angles

private:
	Ui::SLAClass ui;

//私有数据成员
private:
	//端口通信
	Win_QextSerialPort *myCom;

	//端口信息
	QString comPort;						//端口号
	BaudRateType baudRate;					//波特率
	DataBitsType dataBits; //= DATA_8;		//数据位
	ParityType parity; //= PAR_NONE;		//校验位
	StopBitsType stopBits; //= STOP_1;		//停止位
	FlowType flowControl; //= FLOW_OFF;		//数据流控制
	long timeout_Millisec; //= 500;			//延时设置

	//投影仪设置
	float ph_xPos; //= 500.0f;
	float ph_yPos; //= 500.0f;
	float ph_width; //= 1024.0f;
	float ph_height; //= 768.0f;

	//打印参数设置
	float thickness; //=0.1 mm;
	int exposuretime; //=3000 ms;
	int supportinglayer; //=2
	int SLexposuretime; //=8000 ms

	//控制层参数
	int totalLayer;

	//数据读取
	QString receiveMsg;						//接收消息

	//打印器
	Projector *projector;					//打印机控制
	MyWidget *myWidget;						//三维显示

	//控制变量
	bool isWaiting;							//等待芯片返回
	PRINTERMODE mode;						//工作状态
	QTimer *timer;							//时钟

	//G代码存放
	SLAFile slafile;
	int currentGcodeLine;					//解析的行数
	vector<Gcode> Gcodes;				//G代码

	//路径信息
	QString pathFolder;
	Points centers_set;
	vector<double> angles;

	float currentHeight;

	//常量区设置
	static const int STEP_PER_MM = 200;		//每升高1mm，需要电机转200次。
};

#endif // SLA_H
