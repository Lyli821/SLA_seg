/********************************************************************************
** Form generated from reading UI file 'sla.ui'
**
** Created: Fri Jan 15 12:39:47 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLA_H
#define UI_SLA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SLAClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *mySetting;
    QGroupBox *groupBox;
    QLabel *label;
    QComboBox *cbCom;
    QLabel *label_2;
    QComboBox *cbBaudRate;
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QGroupBox *groupBox_3;
    QLabel *label_7;
    QLineEdit *eThickness;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *eExposuretime;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *eSupportinglayer;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *eSLExposuretime;
    QLabel *label_14;
    QPushButton *btnSaveParameter;
    QPushButton *btnCancelParameter;
    QGroupBox *groupBox_9;
    QLabel *label_33;
    QPushButton *btnGenerate;
    QLabel *label_34;
    QPushButton *btnLoad;
    QTextEdit *eGCode;
    QLineEdit *eTotalLayer;
    QLabel *label_18;
    QLineEdit *eCurrentLayer;
    QLabel *label_17;
    QCheckBox *cbBlock;
    QWidget *myControl;
    QGroupBox *groupBox_4;
    QTextEdit *eInfo;
    QGroupBox *groupBox_5;
    QSlider *sliderUp;
    QLineEdit *eUp;
    QLabel *label_21;
    QPushButton *btnUp;
    QSlider *sliderDown;
    QPushButton *btnDown;
    QLineEdit *eDown;
    QLabel *label_22;
    QPushButton *btnUpHome;
    QPushButton *btnDownHome;
    QPushButton *btnLeft;
    QPushButton *btnRight;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QGroupBox *groupBox_6;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnPause;
    QPushButton *btnContinue;
    QGroupBox *groupBox_7;
    QPushButton *btnStartProjector;
    QPushButton *btnEndProjector;
    QLabel *label_35;
    QLabel *label_36;
    QWidget *tab_2;
    QGroupBox *groupBox_10;
    QPushButton *btnSlice;
    QLabel *label_38;
    QPushButton *btnLoadModel;
    QLabel *label_41;
    QLabel *label_42;
    QLineEdit *eScaleRate;
    QLabel *label_43;
    QLabel *label_44;
    QLineEdit *eRx;
    QLineEdit *eRy;
    QLineEdit *eMz;
    QLabel *label_46;
    QLineEdit *eMx;
    QLabel *label_45;
    QLabel *label_16;
    QLineEdit *eSliceThickness;
    QLabel *label_15;
    QCheckBox *cbFill;
    QLineEdit *eRz;
    QLineEdit *eMy;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SLAClass)
    {
        if (SLAClass->objectName().isEmpty())
            SLAClass->setObjectName(QString::fromUtf8("SLAClass"));
        SLAClass->resize(1200, 780);
        centralWidget = new QWidget(SLAClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 0, 300, 721));
        mySetting = new QWidget();
        mySetting->setObjectName(QString::fromUtf8("mySetting"));
        groupBox = new QGroupBox(mySetting);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 261, 141));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 60, 20));
        cbCom = new QComboBox(groupBox);
        cbCom->setObjectName(QString::fromUtf8("cbCom"));
        cbCom->setGeometry(QRect(130, 30, 110, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 60, 20));
        cbBaudRate = new QComboBox(groupBox);
        cbBaudRate->setObjectName(QString::fromUtf8("cbBaudRate"));
        cbBaudRate->setGeometry(QRect(130, 60, 111, 20));
        btnConnect = new QPushButton(groupBox);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setGeometry(QRect(30, 100, 75, 23));
        btnDisconnect = new QPushButton(groupBox);
        btnDisconnect->setObjectName(QString::fromUtf8("btnDisconnect"));
        btnDisconnect->setEnabled(false);
        btnDisconnect->setGeometry(QRect(130, 100, 75, 23));
        groupBox_3 = new QGroupBox(mySetting);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 180, 261, 191));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 30, 100, 20));
        eThickness = new QLineEdit(groupBox_3);
        eThickness->setObjectName(QString::fromUtf8("eThickness"));
        eThickness->setGeometry(QRect(130, 30, 80, 20));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(220, 30, 31, 15));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 60, 91, 20));
        eExposuretime = new QLineEdit(groupBox_3);
        eExposuretime->setObjectName(QString::fromUtf8("eExposuretime"));
        eExposuretime->setEnabled(true);
        eExposuretime->setGeometry(QRect(130, 60, 80, 20));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(220, 60, 31, 15));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 90, 111, 20));
        eSupportinglayer = new QLineEdit(groupBox_3);
        eSupportinglayer->setObjectName(QString::fromUtf8("eSupportinglayer"));
        eSupportinglayer->setGeometry(QRect(131, 90, 80, 20));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(220, 90, 54, 15));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 120, 111, 20));
        eSLExposuretime = new QLineEdit(groupBox_3);
        eSLExposuretime->setObjectName(QString::fromUtf8("eSLExposuretime"));
        eSLExposuretime->setEnabled(true);
        eSLExposuretime->setGeometry(QRect(130, 120, 80, 20));
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(222, 120, 30, 15));
        btnSaveParameter = new QPushButton(groupBox_3);
        btnSaveParameter->setObjectName(QString::fromUtf8("btnSaveParameter"));
        btnSaveParameter->setGeometry(QRect(40, 150, 75, 23));
        btnCancelParameter = new QPushButton(groupBox_3);
        btnCancelParameter->setObjectName(QString::fromUtf8("btnCancelParameter"));
        btnCancelParameter->setGeometry(QRect(146, 150, 75, 23));
        groupBox_9 = new QGroupBox(mySetting);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(20, 380, 261, 311));
        label_33 = new QLabel(groupBox_9);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(20, 60, 111, 20));
        btnGenerate = new QPushButton(groupBox_9);
        btnGenerate->setObjectName(QString::fromUtf8("btnGenerate"));
        btnGenerate->setEnabled(false);
        btnGenerate->setGeometry(QRect(180, 60, 60, 20));
        label_34 = new QLabel(groupBox_9);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(20, 30, 141, 20));
        btnLoad = new QPushButton(groupBox_9);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));
        btnLoad->setEnabled(true);
        btnLoad->setGeometry(QRect(180, 30, 60, 20));
        eGCode = new QTextEdit(groupBox_9);
        eGCode->setObjectName(QString::fromUtf8("eGCode"));
        eGCode->setEnabled(true);
        eGCode->setGeometry(QRect(20, 140, 221, 161));
        eTotalLayer = new QLineEdit(groupBox_9);
        eTotalLayer->setObjectName(QString::fromUtf8("eTotalLayer"));
        eTotalLayer->setEnabled(false);
        eTotalLayer->setGeometry(QRect(200, 110, 40, 20));
        label_18 = new QLabel(groupBox_9);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(20, 110, 91, 16));
        eCurrentLayer = new QLineEdit(groupBox_9);
        eCurrentLayer->setObjectName(QString::fromUtf8("eCurrentLayer"));
        eCurrentLayer->setEnabled(false);
        eCurrentLayer->setGeometry(QRect(147, 110, 40, 20));
        label_17 = new QLabel(groupBox_9);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(191, 110, 16, 16));
        cbBlock = new QCheckBox(groupBox_9);
        cbBlock->setObjectName(QString::fromUtf8("cbBlock"));
        cbBlock->setGeometry(QRect(20, 90, 71, 16));
        tabWidget->addTab(mySetting, QString());
        myControl = new QWidget();
        myControl->setObjectName(QString::fromUtf8("myControl"));
        groupBox_4 = new QGroupBox(myControl);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 510, 281, 181));
        eInfo = new QTextEdit(groupBox_4);
        eInfo->setObjectName(QString::fromUtf8("eInfo"));
        eInfo->setEnabled(false);
        eInfo->setGeometry(QRect(10, 20, 251, 151));
        groupBox_5 = new QGroupBox(myControl);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 20, 281, 211));
        sliderUp = new QSlider(groupBox_5);
        sliderUp->setObjectName(QString::fromUtf8("sliderUp"));
        sliderUp->setGeometry(QRect(10, 30, 90, 20));
        sliderUp->setOrientation(Qt::Horizontal);
        eUp = new QLineEdit(groupBox_5);
        eUp->setObjectName(QString::fromUtf8("eUp"));
        eUp->setEnabled(false);
        eUp->setGeometry(QRect(110, 30, 50, 20));
        label_21 = new QLabel(groupBox_5);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(170, 30, 40, 20));
        btnUp = new QPushButton(groupBox_5);
        btnUp->setObjectName(QString::fromUtf8("btnUp"));
        btnUp->setEnabled(false);
        btnUp->setGeometry(QRect(200, 30, 60, 20));
        sliderDown = new QSlider(groupBox_5);
        sliderDown->setObjectName(QString::fromUtf8("sliderDown"));
        sliderDown->setGeometry(QRect(10, 60, 90, 20));
        sliderDown->setOrientation(Qt::Horizontal);
        btnDown = new QPushButton(groupBox_5);
        btnDown->setObjectName(QString::fromUtf8("btnDown"));
        btnDown->setEnabled(false);
        btnDown->setGeometry(QRect(200, 60, 60, 20));
        eDown = new QLineEdit(groupBox_5);
        eDown->setObjectName(QString::fromUtf8("eDown"));
        eDown->setEnabled(false);
        eDown->setGeometry(QRect(110, 60, 50, 20));
        label_22 = new QLabel(groupBox_5);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(170, 60, 40, 20));
        btnUpHome = new QPushButton(groupBox_5);
        btnUpHome->setObjectName(QString::fromUtf8("btnUpHome"));
        btnUpHome->setEnabled(false);
        btnUpHome->setGeometry(QRect(200, 90, 60, 20));
        btnDownHome = new QPushButton(groupBox_5);
        btnDownHome->setObjectName(QString::fromUtf8("btnDownHome"));
        btnDownHome->setEnabled(false);
        btnDownHome->setGeometry(QRect(200, 120, 60, 20));
        btnLeft = new QPushButton(groupBox_5);
        btnLeft->setObjectName(QString::fromUtf8("btnLeft"));
        btnLeft->setEnabled(false);
        btnLeft->setGeometry(QRect(200, 150, 60, 20));
        btnRight = new QPushButton(groupBox_5);
        btnRight->setObjectName(QString::fromUtf8("btnRight"));
        btnRight->setEnabled(false);
        btnRight->setGeometry(QRect(200, 180, 60, 20));
        label_23 = new QLabel(groupBox_5);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(10, 90, 101, 20));
        label_24 = new QLabel(groupBox_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(10, 120, 111, 20));
        label_25 = new QLabel(groupBox_5);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(10, 150, 111, 20));
        label_26 = new QLabel(groupBox_5);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(10, 180, 111, 20));
        groupBox_6 = new QGroupBox(myControl);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 360, 281, 141));
        label_27 = new QLabel(groupBox_6);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(20, 20, 111, 20));
        label_28 = new QLabel(groupBox_6);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(20, 50, 111, 20));
        label_29 = new QLabel(groupBox_6);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(20, 80, 51, 20));
        label_30 = new QLabel(groupBox_6);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(20, 110, 61, 20));
        btnStart = new QPushButton(groupBox_6);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setEnabled(false);
        btnStart->setGeometry(QRect(200, 20, 60, 20));
        btnStop = new QPushButton(groupBox_6);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setEnabled(false);
        btnStop->setGeometry(QRect(200, 50, 60, 20));
        btnPause = new QPushButton(groupBox_6);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));
        btnPause->setEnabled(false);
        btnPause->setGeometry(QRect(200, 80, 60, 20));
        btnContinue = new QPushButton(groupBox_6);
        btnContinue->setObjectName(QString::fromUtf8("btnContinue"));
        btnContinue->setEnabled(false);
        btnContinue->setGeometry(QRect(200, 110, 60, 20));
        groupBox_7 = new QGroupBox(myControl);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 240, 281, 111));
        btnStartProjector = new QPushButton(groupBox_7);
        btnStartProjector->setObjectName(QString::fromUtf8("btnStartProjector"));
        btnStartProjector->setGeometry(QRect(200, 30, 61, 23));
        btnEndProjector = new QPushButton(groupBox_7);
        btnEndProjector->setObjectName(QString::fromUtf8("btnEndProjector"));
        btnEndProjector->setGeometry(QRect(200, 70, 61, 23));
        label_35 = new QLabel(groupBox_7);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(20, 30, 111, 20));
        label_36 = new QLabel(groupBox_7);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(20, 70, 111, 20));
        tabWidget->addTab(myControl, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        groupBox_10 = new QGroupBox(tab_2);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(20, 30, 261, 211));
        btnSlice = new QPushButton(groupBox_10);
        btnSlice->setObjectName(QString::fromUtf8("btnSlice"));
        btnSlice->setEnabled(false);
        btnSlice->setGeometry(QRect(180, 60, 60, 20));
        label_38 = new QLabel(groupBox_10);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(20, 30, 111, 20));
        btnLoadModel = new QPushButton(groupBox_10);
        btnLoadModel->setObjectName(QString::fromUtf8("btnLoadModel"));
        btnLoadModel->setEnabled(true);
        btnLoadModel->setGeometry(QRect(180, 30, 60, 20));
        label_41 = new QLabel(groupBox_10);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setGeometry(QRect(220, 120, 30, 15));
        label_42 = new QLabel(groupBox_10);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        label_42->setGeometry(QRect(20, 120, 54, 20));
        eScaleRate = new QLineEdit(groupBox_10);
        eScaleRate->setObjectName(QString::fromUtf8("eScaleRate"));
        eScaleRate->setGeometry(QRect(179, 120, 31, 20));
        label_43 = new QLabel(groupBox_10);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        label_43->setGeometry(QRect(20, 150, 54, 20));
        label_44 = new QLabel(groupBox_10);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        label_44->setGeometry(QRect(80, 150, 161, 20));
        eRx = new QLineEdit(groupBox_10);
        eRx->setObjectName(QString::fromUtf8("eRx"));
        eRx->setGeometry(QRect(91, 150, 31, 20));
        eRy = new QLineEdit(groupBox_10);
        eRy->setObjectName(QString::fromUtf8("eRy"));
        eRy->setGeometry(QRect(210, 150, 31, 20));
        eMz = new QLineEdit(groupBox_10);
        eMz->setObjectName(QString::fromUtf8("eMz"));
        eMz->setGeometry(QRect(150, 180, 31, 20));
        label_46 = new QLabel(groupBox_10);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setGeometry(QRect(80, 180, 141, 20));
        eMx = new QLineEdit(groupBox_10);
        eMx->setObjectName(QString::fromUtf8("eMx"));
        eMx->setGeometry(QRect(91, 180, 31, 20));
        label_45 = new QLabel(groupBox_10);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setGeometry(QRect(20, 180, 54, 20));
        label_16 = new QLabel(groupBox_10);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(20, 90, 100, 20));
        eSliceThickness = new QLineEdit(groupBox_10);
        eSliceThickness->setObjectName(QString::fromUtf8("eSliceThickness"));
        eSliceThickness->setGeometry(QRect(130, 90, 80, 20));
        label_15 = new QLabel(groupBox_10);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(220, 90, 31, 15));
        cbFill = new QCheckBox(groupBox_10);
        cbFill->setObjectName(QString::fromUtf8("cbFill"));
        cbFill->setGeometry(QRect(20, 60, 71, 16));
        eRz = new QLineEdit(groupBox_10);
        eRz->setObjectName(QString::fromUtf8("eRz"));
        eRz->setGeometry(QRect(150, 150, 31, 20));
        eMy = new QLineEdit(groupBox_10);
        eMy->setObjectName(QString::fromUtf8("eMy"));
        eMy->setGeometry(QRect(210, 180, 31, 20));
        tabWidget->addTab(tab_2, QString());
        SLAClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SLAClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 23));
        SLAClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SLAClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SLAClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SLAClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SLAClass->setStatusBar(statusBar);

        retranslateUi(SLAClass);

        tabWidget->setCurrentIndex(0);
        cbCom->setCurrentIndex(5);
        cbBaudRate->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SLAClass);
    } // setupUi

    void retranslateUi(QMainWindow *SLAClass)
    {
        SLAClass->setWindowTitle(QApplication::translate("SLAClass", "SLA", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SLAClass", "Parameter for Serial", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SLAClass", "COM Port:", 0, QApplication::UnicodeUTF8));
        cbCom->clear();
        cbCom->insertItems(0, QStringList()
         << QApplication::translate("SLAClass", "COM1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "COM2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "COM3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "COM4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "COM5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "COM6", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("SLAClass", "Baud Rate:", 0, QApplication::UnicodeUTF8));
        cbBaudRate->clear();
        cbBaudRate->insertItems(0, QStringList()
         << QApplication::translate("SLAClass", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SLAClass", "115200", 0, QApplication::UnicodeUTF8)
        );
        btnConnect->setText(QApplication::translate("SLAClass", "Connect", 0, QApplication::UnicodeUTF8));
        btnDisconnect->setText(QApplication::translate("SLAClass", "Disconnect", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("SLAClass", "Parameter for Printing", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SLAClass", "Layer Thickness:", 0, QApplication::UnicodeUTF8));
        eThickness->setText(QApplication::translate("SLAClass", "0.100000", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SLAClass", "mm", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("SLAClass", "Exposure   Time:", 0, QApplication::UnicodeUTF8));
        eExposuretime->setText(QApplication::translate("SLAClass", "12000", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("SLAClass", "ms", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("SLAClass", "Supporting Layer:", 0, QApplication::UnicodeUTF8));
        eSupportinglayer->setText(QApplication::translate("SLAClass", "3", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("SLAClass", "layers", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("SLAClass", "SL Exposure Time:", 0, QApplication::UnicodeUTF8));
        eSLExposuretime->setText(QApplication::translate("SLAClass", "15000", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("SLAClass", "ms", 0, QApplication::UnicodeUTF8));
        btnSaveParameter->setText(QApplication::translate("SLAClass", "Save", 0, QApplication::UnicodeUTF8));
        btnCancelParameter->setText(QApplication::translate("SLAClass", "Cancel", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("SLAClass", "G-Code", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("SLAClass", "Generate G-Code:", 0, QApplication::UnicodeUTF8));
        btnGenerate->setText(QApplication::translate("SLAClass", "Generate", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("SLAClass", "Load Printing Sequence:", 0, QApplication::UnicodeUTF8));
        btnLoad->setText(QApplication::translate("SLAClass", "Load", 0, QApplication::UnicodeUTF8));
        eTotalLayer->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("SLAClass", "current layers:", 0, QApplication::UnicodeUTF8));
        eCurrentLayer->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("SLAClass", "/", 0, QApplication::UnicodeUTF8));
        cbBlock->setText(QApplication::translate("SLAClass", "Block", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(mySetting), QApplication::translate("SLAClass", "GCode", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("SLAClass", "System Info", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("SLAClass", "Control Part", 0, QApplication::UnicodeUTF8));
        eUp->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("SLAClass", "mm", 0, QApplication::UnicodeUTF8));
        btnUp->setText(QApplication::translate("SLAClass", "UP", 0, QApplication::UnicodeUTF8));
        btnDown->setText(QApplication::translate("SLAClass", "DOWN", 0, QApplication::UnicodeUTF8));
        eDown->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("SLAClass", "mm", 0, QApplication::UnicodeUTF8));
        btnUpHome->setText(QApplication::translate("SLAClass", "Up Home", 0, QApplication::UnicodeUTF8));
        btnDownHome->setText(QApplication::translate("SLAClass", "Down Home", 0, QApplication::UnicodeUTF8));
        btnLeft->setText(QApplication::translate("SLAClass", "Left", 0, QApplication::UnicodeUTF8));
        btnRight->setText(QApplication::translate("SLAClass", "Right", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("SLAClass", "Go to top layer:", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("SLAClass", "Go to ottom layer:", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("SLAClass", "Go to left:", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("SLAClass", "Go to right:", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("SLAClass", "Printing", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("SLAClass", "Start:", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("SLAClass", "Stop:", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("SLAClass", "Pause:", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("SLAClass", "Continue:", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("SLAClass", "Start", 0, QApplication::UnicodeUTF8));
        btnStop->setText(QApplication::translate("SLAClass", "Stop", 0, QApplication::UnicodeUTF8));
        btnPause->setText(QApplication::translate("SLAClass", "Pause", 0, QApplication::UnicodeUTF8));
        btnContinue->setText(QApplication::translate("SLAClass", "Continue", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("SLAClass", "Projector", 0, QApplication::UnicodeUTF8));
        btnStartProjector->setText(QApplication::translate("SLAClass", "Open", 0, QApplication::UnicodeUTF8));
        btnEndProjector->setText(QApplication::translate("SLAClass", "Close", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("SLAClass", "Open Projector:", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("SLAClass", "CLose Projector:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(myControl), QApplication::translate("SLAClass", "Control", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("SLAClass", "Model", 0, QApplication::UnicodeUTF8));
        btnSlice->setText(QApplication::translate("SLAClass", "SLice", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("SLAClass", "Load 3-D Model:", 0, QApplication::UnicodeUTF8));
        btnLoadModel->setText(QApplication::translate("SLAClass", "Load", 0, QApplication::UnicodeUTF8));
        label_41->setText(QApplication::translate("SLAClass", "%", 0, QApplication::UnicodeUTF8));
        label_42->setText(QApplication::translate("SLAClass", "Sclae:", 0, QApplication::UnicodeUTF8));
        eScaleRate->setText(QApplication::translate("SLAClass", "100", 0, QApplication::UnicodeUTF8));
        label_43->setText(QApplication::translate("SLAClass", "Rotate:", 0, QApplication::UnicodeUTF8));
        label_44->setText(QApplication::translate("SLAClass", "x:       y:        z:", 0, QApplication::UnicodeUTF8));
        eRx->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        eRy->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        eMz->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("SLAClass", "x:       y:        z:", 0, QApplication::UnicodeUTF8));
        eMx->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        label_45->setText(QApplication::translate("SLAClass", "Move:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("SLAClass", "Slice Thickness:", 0, QApplication::UnicodeUTF8));
        eSliceThickness->setText(QApplication::translate("SLAClass", "0.1", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("SLAClass", "mm", 0, QApplication::UnicodeUTF8));
        cbFill->setText(QApplication::translate("SLAClass", "Fill", 0, QApplication::UnicodeUTF8));
        eRz->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        eMy->setText(QApplication::translate("SLAClass", "0", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SLAClass", "SLice", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SLAClass: public Ui_SLAClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLA_H
