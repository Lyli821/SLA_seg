#include "sla.h"
#include "Calculator.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using namespace cv;

SLA::SLA(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	parainit();
	//Setting
	connect(ui.cbCom, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(cbComChanged(const QString &)));
	connect(ui.cbBaudRate, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(cbBaudChanged(const QString &)));
	connect(ui.btnConnect, SIGNAL(clicked()), this,  SLOT(btnConnectClicked()));
	connect(ui.btnDisconnect, SIGNAL(clicked()), this,  SLOT(btnDisconnectClicked()));
	connect(ui.btnSaveParameter, SIGNAL(clicked()), this,  SLOT(btnSaveParameterClicked()));
	connect(ui.btnCancelParameter, SIGNAL(clicked()), this,  SLOT(btnCancelParameterClicked()));
	connect(ui.btnLoad, SIGNAL(clicked()), this, SLOT(btnLoadClicked()));
	connect(ui.btnGenerate, SIGNAL(clicked()), this, SLOT(btnGenerateClicked()));

	//model view
	connect(ui.btnLoadModel, SIGNAL(clicked()), this, SLOT(btnLoadModelClicked()));
	connect(ui.btnSlice, SIGNAL(clicked()), this, SLOT(btnSliceClicked()));
	connect(ui.eScaleRate, SIGNAL(returnPressed()), this, SLOT(eScaleRateChecked()));
	connect(ui.eRx, SIGNAL(returnPressed()), this, SLOT(eRxChecked()));
	connect(ui.eRy, SIGNAL(returnPressed()), this, SLOT(eRyChecked()));
	connect(ui.eRz, SIGNAL(returnPressed()), this, SLOT(eRzChecked()));
	connect(ui.eMx, SIGNAL(returnPressed()), this, SLOT(eMxChecked()));
	connect(ui.eMy, SIGNAL(returnPressed()), this, SLOT(eMyChecked()));
	connect(ui.eMz, SIGNAL(returnPressed()), this, SLOT(eMzChecked()));
	
	//Control
	connect(ui.sliderUp, SIGNAL(valueChanged(int)),this, SLOT(sliderUpChanged(int)));
	connect(ui.sliderDown, SIGNAL(valueChanged(int)),this, SLOT(sliderDownChanged(int)));
	connect(ui.btnUp, SIGNAL(clicked()), this,  SLOT(btnUpClicked()));
	connect(ui.btnDown, SIGNAL(clicked()), this,  SLOT(btnDownClicked()));
	connect(ui.btnUpHome, SIGNAL(clicked()), this,  SLOT(btnUpHomeClicked()));
	connect(ui.btnDownHome, SIGNAL(clicked()), this,  SLOT(btnDownHomeClicked()));
	connect(ui.btnLeft, SIGNAL(clicked()), this,  SLOT(btnLeftClicked()));
	connect(ui.btnRight, SIGNAL(clicked()), this,  SLOT(btnRightClicked()));

	connect(ui.btnStart, SIGNAL(clicked()), this,  SLOT(btnStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this,  SLOT(btnStopClicked()));
	connect(ui.btnContinue, SIGNAL(clicked()), this,  SLOT(btnContinueClicked()));
	connect(ui.btnPause, SIGNAL(clicked()), this,  SLOT(btnPauseClicked()));

	//projector
	connect(ui.btnStartProjector, SIGNAL(clicked()), this,  SLOT(btnStartProjectorClicked()));
	connect(ui.btnEndProjector, SIGNAL(clicked()), this,  SLOT(btnEndProjectorClicked()));
	//QTimer
	connect(timer,SIGNAL(timeout()),this,SLOT(parsingGcode()));

	//close
	connect(this, SIGNAL(close()), myWidget, SLOT(close()));
}

void SLA::parainit(){
	myCom = NULL;
	projector = NULL;

	//端口信息
	comPort = QString("COM6");		//端口号
	baudRate = BAUD9600;		//波特率
	dataBits = DATA_8;			//数据位
	parity = PAR_NONE;			//校验位
	stopBits = STOP_1;			//停止位
	flowControl = FLOW_OFF;		//数据流控制
	timeout_Millisec = 500;			//延时设置

	//投影仪设置
	ph_xPos = 500.0f;
	ph_yPos = 500.0f;
	ph_width = 1024.0f;
	ph_height = 768.0f;

	//打印参数设置
	thickness = 0.1f;
	exposuretime =12000;
	supportinglayer = 3;
	SLexposuretime =15000;

	//控制层参数
	totalLayer = 0;

	//数据读取
	receiveMsg = "";

	//打印器
	projector = new Projector();					//打印机控制
	projector->show();

	//三维显示
	myWidget = new MyWidget(this);
	myWidget->resize(840, 700);
	myWidget->move(330, 30);

	//控制变量
	isWaiting = false;
	mode = NORMAL;
	timer = new QTimer(this);

	//Gcode
	currentGcodeLine = 0;
	Gcodes.clear();

	currentHeight = 0.0f;

	//初始myCom
	struct PortSettings myComSetting = {baudRate, dataBits, parity, stopBits, flowControl, timeout_Millisec};
	myCom = new Win_QextSerialPort(comPort, myComSetting, QextSerialBase::EventDriven);
}

void SLA::cbComChanged(const QString& comName){
	cout << comName.toStdString() << endl;
	
	comPort = comName;
	if(myCom){
		myCom->setPortName(comPort);
	}
}

void SLA::cbBaudChanged(const QString& baudName){
	cout << baudName.toStdString() << endl;

	if(baudName == tr("1200")){
		baudRate = BAUD1200;
	} else if(baudName == tr("9600")){
		baudRate = BAUD9600;
	} else if(baudName == tr("19200")){
		baudRate = BAUD19200;
	} else if(baudName == tr("38400")){
		baudRate = BAUD38400;
	} else if(baudName == tr("57600")){
		baudRate = BAUD57600;
	} else if(baudName == tr("115200")){
		baudRate = BAUD115200;
	} else {
		baudRate = BAUD9600;
	}

	if(myCom){
		myCom->setBaudRate(baudRate);
	}
}

void SLA::btnConnectClicked(){
	//按键使能
	if(!myCom){
		printf("myCom should be initialized before use!\n");
		return;
	}

	if(myCom ->open(QIODevice::ReadWrite)){
		connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));

		//setting
		ui.cbCom->setEnabled(false);
		ui.cbBaudRate->setEnabled(false);
		ui.btnConnect->setEnabled(false);
		ui.btnDisconnect->setEnabled(true);

		//control
		ui.btnUp->setEnabled(true);
		ui.btnDown->setEnabled(true);
		ui.btnUpHome->setEnabled(true);
		ui.btnDownHome->setEnabled(true);
		ui.btnLeft->setEnabled(true);
		ui.btnRight->setEnabled(true);
		ui.btnStart->setEnabled(true);
		//ui.btnStop->setEnabled(true);
		//ui.btnPause->setEnabled(true);
		//ui.btnContinue->setEnabled(true);

		printf("connect success!\n");
	} else {
		printf("connect failed!\n");
	}
}

void SLA::btnDisconnectClicked(){
	if(myCom){
		myCom->close();
	}

	//setting
	ui.cbCom->setEnabled(true);
	ui.cbBaudRate->setEnabled(true);
	ui.btnConnect->setEnabled(true);
	ui.btnConnect->setEnabled(true);
	ui.btnDisconnect->setEnabled(false);

	//control
	ui.btnUp->setEnabled(false);
	ui.btnDown->setEnabled(false);
	ui.btnUpHome->setEnabled(false);
	ui.btnDownHome->setEnabled(false);
	ui.btnLeft->setEnabled(false);
	ui.btnRight->setEnabled(false);
	ui.btnStart->setEnabled(false);
	ui.btnStop->setEnabled(false);
	ui.btnPause->setEnabled(false);
	ui.btnContinue->setEnabled(false);

}

void SLA::btnSaveParameterClicked(){
	thickness = ui.eThickness->text().toFloat();
	exposuretime = ui.eExposuretime->text().toInt();
	supportinglayer = ui.eSupportinglayer->text().toInt();
	SLexposuretime = ui.eSLExposuretime->text().toInt();

	printf("Thickness = %f, Exposuretime = %d, Supportinglayer = %d, SLexposuretime = %d\n", thickness, exposuretime, supportinglayer, SLexposuretime);
}

void SLA::btnCancelParameterClicked(){
	ui.eThickness->setText(QString("%1").arg(thickness));
	ui.eExposuretime->setText(QString("%1").arg(exposuretime));
	ui.eSupportinglayer->setText(QString("%1").arg(supportinglayer));
	ui.eSLExposuretime->setText(QString("%1").arg(SLexposuretime));
}

void SLA::btnLoadClicked(){

	//选择文件
	QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "Resources", tr("data or images (*.data *.png *.xpm *.jpg)"));

	if(file == ""){
		return;
	}

	slafile = SLAFile(file);
	int block;
	if(slafile.prefix == "jpg" || slafile.prefix == "png"){
		//判断序列是否一致
		QStringList words = slafile.filename.split("_");
		pathFolder = slafile.fileroot + words[0] + QString("_");
		totalLayer = 0;
		projector->clearImgList();
		while(true){
			totalLayer ++;
			projector->pushback();
			//QString imagePath = slafile.fileroot + words[0] + QString("_") + QString("%1").arg(totalLayer) + QString(".") + slafile.prefix;
			QDir dir;
			QString folderPath = slafile.fileroot + words[0] + QString("_") + QString("%1").arg(totalLayer);
			dir.setPath(folderPath);
			block = 0;
			if(dir.exists()){
				printf("%s\n", folderPath.toStdString().c_str());
				while(true){
					QString imagePath = folderPath + QString("/%1").arg(block) + slafile.prefix;
					if(QFileInfo(imagePath).exists()){
						QPixmap *pixmap = new QPixmap(imagePath);
						projector->pushback(totalLayer-1, pixmap);
						Mat *mat = new Mat(imread(imagePath.toStdString()));
						projector->pushback(totalLayer-1, mat);
						block++;
					}else{
						break;
					}
				}
				continue;
			} else{
				totalLayer --;
				break;
			}
		}
		ui.eTotalLayer->setText(QString("%1").arg(totalLayer));
		//按键使能
		ui.btnGenerate->setEnabled(true);
	} 
	else if(slafile.prefix == "data"){
		ifstream fin(file.toStdString().c_str());
		int Layers = 0;
		while(!fin.eof()){
			string tline;
			getline(fin, tline);
			QString line = QString::fromStdString(tline);
			QStringList words = line.split("=");
			if(words[0] == "Thickness"){
				thickness = words[1].toFloat();
				ui.eThickness->setText(words[1]);
			} else if(words[0] == "Layers"){
				Layers = words[1].toInt();
			}
		}
		fin.close();
		QStringList words = slafile.filename.split("_");
		pathFolder = slafile.fileroot + words[0] + QString("_");
		totalLayer = 0;
		projector->clearImgList();
		for(int i = 0; i < Layers; i ++){
			totalLayer ++;
			projector->pushback();
			QDir dir;
			QString folderPath = slafile.fileroot + words[0] + QString("_") + QString("%1").arg(totalLayer);
			dir.setPath(folderPath);
			block = 0;
			if(dir.exists()){
				printf("%s\n", folderPath.toStdString().c_str());
				while(true){
					QString imagePath = folderPath + QString("/%1").arg(block) + QString(".jpg");
					if(QFileInfo(imagePath).exists()){
						QPixmap *pixmap = new QPixmap(imagePath);
						projector->pushback(totalLayer-1, pixmap);
						Mat *mat = new Mat(imread(imagePath.toStdString()));
						projector->pushback(totalLayer-1, mat);
						block++;
					}else{
						break;
					}
				}
				continue;
			} else{
				totalLayer --;
				break;
			}
		}
		ui.eTotalLayer->setText(QString("%1").arg(totalLayer));
		//按键使能
		ui.btnGenerate->setEnabled(true);
	} 
	else {
		warning(QString("not legal image type!"));
	}
}

void SLA::btnGenerateClicked(){

	//获取参数
	btnSaveParameterClicked();

	//=======================================================================================
	//生成Gcode

	//清空
	Gcodes.clear();
	currentGcodeLine = 0;
	ui.eGCode->clear();
	
	//参数
	if(thickness > 1 || thickness < 0.1){
		warning(QString("thickness should be in 0.1~1mm"));
		return;
	}

	if(supportinglayer > 8 || supportinglayer < 2){
		warning(QString("supporting layer should be in 2~10 layers"));
		return;
	}

	//int steps = thickness * STEP_PER_MM;
	float steps = thickness;

	//Gcode for initialize
	Gcodes.push_back(Gcode("UP_HOME"));
	Gcodes.push_back(Gcode("DOWN_HOME"));
	Gcodes.push_back(Gcode("CLOSE PROJECTOR"));

	double center_x = 0;
	double center_y = 0;
	double angle = 0;
	bool rotate = true;
	//Gcode for supporting layers
	for(int i = 0; i < supportinglayer; i ++){
		Gcodes.push_back(QString("UP %1").arg(steps));
		if(ui.cbBlock->isChecked()){
			for(int j = 0; j < projector->num(i); j ++){
				Gcodes.push_back(QString("MOVE %1 %2").arg(center_x).arg(center_y));
				Gcodes.push_back(QString("SHOW IMAGE %1 %2").arg(i).arg(j));
				Gcodes.push_back(QString("EXPOSURE %1").arg(SLexposuretime));
				Gcodes.push_back(QString("CLOSE PROJECTOR"));
			}
		} else {
			Gcodes.push_back(QString("SHOW IMAGE %1").arg(i));
			Gcodes.push_back(QString("EXPOSURE %1").arg(SLexposuretime));
			Gcodes.push_back(QString("CLOSE PROJECTOR"));
		}
	}

	//Gcode for models
	for(int i = supportinglayer; i < totalLayer; i ++){
		Gcodes.push_back(QString("UP %1").arg(steps));
		if(ui.cbBlock->isChecked()){
			QString dataFolder = pathFolder + QString("%1").arg(i+1) + QString("/data.txt");
			readPath(dataFolder);
			for(int j = 0; j < projector->num(i); j ++){
				if(rotate && angles[j] != angle){
					angle = angles[j];
					Gcodes.push_back(QString("ROTATE TO %1").arg(angle));
				}
				Gcodes.push_back(QString("MOVE %1 %2").arg(centers_set[j].x()).arg(centers_set[j].y()));
				Gcodes.push_back(QString("SHOW IMAGE %1 %2").arg(i).arg(j));
				Gcodes.push_back(QString("EXPOSURE %1").arg(exposuretime));
				Gcodes.push_back(QString("CLOSE PROJECTOR"));
			}
		} else {
			Gcodes.push_back(QString("SHOW IMAGE %1").arg(i));
			Gcodes.push_back(QString("EXPOSURE %1").arg(exposuretime));
			Gcodes.push_back(QString("CLOSE PROJECTOR"));
		}
	}

	//Gcode for END
	Gcodes.push_back(QString("UP_HOME"));

	//show Gcode
	for(int i = 0; i < Gcodes.size(); i ++){
		ui.eGCode->append(QString("%1: ").arg(i) + Gcodes[i].line);
	}

	//生成Gcode
	//=======================================================================================
}

void SLA::btnLoadModelClicked(){
	//选择文件
	QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "Resources", tr("3D models(*.STL)"));

	if(file == ""){
		return;
	}

	slafile = SLAFile(file);

	if(slafile.prefix == "STL" || slafile.prefix == "stl"){
		myWidget->readModel(file);
		//按键使能
		ui.btnSlice->setEnabled(true);
	} else {
		warning(QString("not legal model type!"));
	}
}

void SLA::btnSliceClicked(){

	//清空图片
	float sliceThickness = ui.eSliceThickness->text().toFloat();
	bool fill = ui.cbFill->isChecked();
	

	float max_h = myWidget->max_y();
	float min_h = myWidget->min_y();
	float model_height = max_h - min_h;

	if(model_height > 100.0f){
		printf("model should be not higher than 100.0f\n");
		return;
	}

	QDir dir;
	Calculator::removeDirWithContent(slafile.fileroot + slafile.filename);
	dir.mkdir(slafile.fileroot + slafile.filename);

	int GFloor = 3;
	int currentLayer = 0;
	int totalLayer = int(model_height / sliceThickness) + GFloor + 1;
	//底层
	for(int i = 0; i < GFloor; i ++){
		currentLayer ++;
		Mat image = myWidget->getGFloor();

		QDir dir;
		Calculator::removeDirWithContent(slafile.fileroot + slafile.filename + QString("/") + slafile.filename + QString("_%1").arg(currentLayer));
		dir.mkdir(slafile.fileroot + slafile.filename + QString("/") + slafile.filename + QString("_%1").arg(currentLayer));
		QString imagename = slafile.fileroot + slafile.filename + QString("/") + slafile.filename + QString("_%1").arg(currentLayer) + QString("/0.jpg");
		imwrite(imagename.toStdString(), image);
	}

	for(float pos = min_h; pos < max_h; pos += sliceThickness){
		currentLayer ++;

		printf("current = %d, totallayer = %d, pos = %f\n", currentLayer, totalLayer, pos);
		QString folder = slafile.fileroot + slafile.filename + QString("/") + slafile.filename + QString("_%1").arg(currentLayer);
		myWidget->slice(pos, fill, folder);
	}

	QString datafile = slafile.fileroot + slafile.filename + QString("/") + slafile.filename + QString(".data");
	ofstream fout(datafile.toStdString().c_str());
	fout << "Thickness=" << sliceThickness << endl; 
	fout << "Layers=" << currentLayer << endl;
	fout.close();
}

void SLA::eScaleRateChecked(){
	//输入检测
	float scalerate = ui.eScaleRate->text().toFloat() / 100;
	if(scalerate < 0.01 && scalerate > 100){

		warning(QString("Scale should be in 0.1 to 10!"));
		return;
	}
	myWidget->body_scaleChanged(scalerate);
}

void SLA::eRxChecked(){
	float rx = ui.eRx->text().toFloat();
	if(rx < 0 || rx > 360){
		warning(QString("Angle should be in 0 to 360!"));
		return;
	}
	myWidget->body_rxChanged(rx);
}

void SLA::eRyChecked(){
	float ry = ui.eRy->text().toFloat();
	if(ry < 0 || ry > 360){
		warning(QString("Angle should be in 0 to 360!"));
		return;
	}
	myWidget->body_ryChanged(ry);
}

void SLA::eRzChecked(){
	float rz = ui.eRz->text().toFloat();
	if(rz < 0 || rz > 360){
		warning(QString("Angle should be in 0 to 360!"));
		return;
	}
	myWidget->body_rzChanged(rz);
}

void SLA::eMxChecked(){
	float mx = ui.eMx->text().toFloat();
	if(mx < -100 || mx > 100){
		warning(QString("Offset should be in -100 to 100!"));
		return;
	}
	myWidget->body_mxChanged(mx);
}

void SLA::eMyChecked(){
	float my = ui.eMy->text().toFloat();
	if(my < -100 || my > 100){
		warning(QString("Offset should be in -100 to 100!"));
		return;
	}
	myWidget->body_myChanged(my);
}

void SLA::eMzChecked(){
	float mz = ui.eMz->text().toFloat();
	if(mz < -100 || mz > 100){
		warning(QString("Offset should be in -100 to 100!"));
		return;
	}
	myWidget->body_mzChanged(mz);
}

void SLA::sliderUpChanged(int value){
	float step = 0;
	if(value < 5)
		step = 0;
	else if(value < 25)
		step = 1.0f;
	else if(value < 50)
		step = 10.0f;
	else if(value < 75)
		step = 50.0f;
	else 
		step = 100.0f;

	ui.eUp->setText(QString("%1").arg(step));
}

void SLA::sliderDownChanged(int value){
	float step = 0;
	if(value < 5)
		step = 0;
	else if(value < 25)
		step = 1.0f;
	else if(value < 50)
		step = 10.0f;
	else if(value < 75)
		step = 50.0f;
	else 
		step = 100.0f;

	ui.eDown->setText(QString("%1").arg(step));
}

void SLA::btnUpClicked(){
	if(isWaiting){
		warning(QString("The printer is running!"));
		return;
	}
	float h = ui.eUp->text().toFloat();
	if( h < 0 || h > 240 ){
		printf("error: invalid number!\n");
		return;
	}
	currentHeight += h;
	QString msg = QString("G1 X0 Y0 Z%1").arg(currentHeight);
	writeMyCom(msg);
}

void SLA::btnDownClicked(){
	if(isWaiting){
		warning(QString("The printer is running!"));
		return;
	}
	float h = ui.eDown->text().toFloat();
	if( h < 0 || h > 240 ){
		printf("error: invalid number!\n");
		return;
	}
	currentHeight -= h;
	QString msg = QString("G1 X0 Y0 Z%1").arg(currentHeight);
	writeMyCom(msg);
}

void SLA::btnUpHomeClicked(){
	if(isWaiting){
		warning(QString("The printer is running!"));
		return;
	}
	currentHeight = 240.0f;
	writeMyCom(QString("G28"));
}

void SLA::btnDownHomeClicked(){
	if(isWaiting){
		warning(QString("The printer is running!"));
		return;
	}
	currentHeight = 0.0f;
	writeMyCom(QString("G1 X0 Y0 Z0"));
}

void SLA::btnLeftClicked(){
	if(isWaiting){
		warning(QString("The printer is running!"));
		return;
	}
}

void SLA::btnRightClicked(){
	if(isWaiting){
		warning(QString("The printer is running!"));
		return;
	}
}

void SLA::btnStartClicked(){
	if(isWaiting){
		warning(QString("The printer is running!"));
		return;
	}

	if(Gcodes.size() == 0){
		warning(QString("Please Generate Gcode First!"));
		return;
	}

	//control
	ui.btnUp->setEnabled(false);
	ui.btnDown->setEnabled(false);
	ui.btnUpHome->setEnabled(false);
	ui.btnDownHome->setEnabled(false);
	ui.btnLeft->setEnabled(false);
	ui.btnRight->setEnabled(false);

	ui.btnStart->setEnabled(false);
	ui.btnStop->setEnabled(true);
	ui.btnPause->setEnabled(true);
	ui.btnContinue->setEnabled(false);

	//开始
	mode = PRINTING;
	parsingGcode();
}

void SLA::btnStopClicked(){

	//control
	ui.btnUp->setEnabled(true);
	ui.btnDown->setEnabled(true);
	ui.btnUpHome->setEnabled(true);
	ui.btnDownHome->setEnabled(true);
	ui.btnLeft->setEnabled(true);
	ui.btnRight->setEnabled(true);

	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnPause->setEnabled(false);
	ui.btnContinue->setEnabled(false);

	mode = STOP;
}

void SLA::btnPauseClicked(){
	ui.btnPause->setEnabled(false);
	ui.btnContinue->setEnabled(true);

	mode = PAUSE;
}

void SLA::btnContinueClicked(){
	ui.btnPause->setEnabled(true);
	ui.btnContinue->setEnabled(false);

	mode = PRINTING;
	parsingGcode();
}

void SLA::btnStartProjectorClicked(){
	projector->showBG();
}

void SLA::btnEndProjectorClicked(){
	projector->hideImage();
}

void SLA::readMyCom(){
	while(myCom->bytesAvailable()){
		char *c = new char[1];
		myCom->getChar(c);
		
		if(*c == '\n'){
			receiveMsg = receiveMsg.mid(0, receiveMsg.size() - 1);
			//printf("%s\n", receiveMsg.toStdString().c_str());
			parsing(receiveMsg);

			receiveMsg = "";
		} else {
			receiveMsg += *c;
		}
	}
}

void SLA::writeMyCom(QString &qdata){
	
	//添加结束符号
	QString endLabel = "\n";
	qdata += endLabel;
	if(myCom){
		myCom->write(qdata.toStdString().c_str());
	}
}

void SLA::closeEvent(QCloseEvent *event){

}

void SLA::warning(QString &warning){
	QMessageBox::warning(this, tr("WARNING"), warning);
}

void SLA::parsing(QString &receiveMsg){
	if(receiveMsg == QString("ok")){
		isWaiting = false;

		if(mode == PRINTING){
			parsingGcode();
		}
	}
}

void SLA::parsingGcode(){

	//将时钟停止
	if(timer->isActive()){
		timer->stop();
		//close projector
		projector->hideImage();
	}

	if(currentGcodeLine >= Gcodes.size()){
		//结束
		printf("printing end!\n");
		return;
	}

	if(mode == PRINTING){
		
	} else if (mode == PAUSE){
		return;
	} else if(mode == STOP){
		currentGcodeLine = 0;
		return;
	}

	currentGcodeLine ++;		//阅读下一行代码

	//拆分代码
	QStringList words = Gcodes[currentGcodeLine - 1].words;
	QString line = Gcodes[currentGcodeLine - 1].line;
	
	printf("%d: %s\n", currentGcodeLine, line.toStdString().c_str());

	//判断
	if(words[0] == "DOWN_HOME"){
		currentHeight = 0.0f;
		writeMyCom(QString("G1 X0 Y0 Z0"));
		//等待反馈
	} else if(words[0] == "UP_HOME"){
		currentHeight = 240.0f;
		writeMyCom(QString("G28"));
		//等待反馈
	} else if(words[0] == "UP"){
		currentHeight += words[1].toFloat();
		QString msg = QString("G1 X0 Y0 Z%1").arg(currentHeight);
		writeMyCom(msg);
		//等待反馈
	} else if(words[0] == "DOWN"){
		currentHeight -= words[1].toFloat();
		QString msg = QString("G1 X0 Y0 Z%1").arg(currentHeight);
		writeMyCom(msg);
		//等待反馈
	} else if(words[0] == "MOVE"){//平面内运动
		QString msg = QString("G1 X%1 Y%2 Z%3").arg(words[1]).arg(words[2]).arg(currentHeight);
		writeMyCom(msg);
		//等待反馈
	} else if(words[0] == "ROTATE"){//旋转
		QString msg = QString("");
		writeMyCom(msg);
		//等待反馈
	}
	else if(words[0] == "CLOSE"){
		// do close projector
		projector->hideImage();
		// 继续下一行代码
		parsingGcode();
		return;
	} else if (words[0] == "SHOW"){
		if(words.size() == 3){
			//show image
			projector->showImage(words[2].toInt());
			ui.eCurrentLayer->setText(QString("%1").arg(words[2].toInt()));
		}
		if(words.size() == 4){
			projector->showImage(words[2].toInt(), words[3].toInt());
			ui.eCurrentLayer->setText(QString("%1").arg(words[2].toInt()));
		}
		// 继续下一行代码
		parsingGcode();
		return;
	} else if (words[0] == "EXPOSURE"){
		//EXPOSURE
		timer->start(words[1].toInt());
		//等待反馈
	}
}

void SLA::readPath(QString dataFolder){
	ifstream fin(dataFolder.toStdString());

	centers_set.clear();
	angles.clear();

	int numPolygon;
	char c;
	double angle, c_x, c_y;

	fin >> numPolygon;
	fin >> c;
	while(c != '#'){
		if(c == 'a'){
			fin >> angle;
			fin >> c;
		}
		if(c == 'c'){
			fin >> c_x >> c_y;
			centers_set.push_back(Point_2(c_x,c_y));
			angles.push_back(angle);
			fin >> c;
		}
	}

}

SLA::~SLA()
{

}