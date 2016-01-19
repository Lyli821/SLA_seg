#include "sla.h"
#include <QTextCodec>
#include <QtGui/QApplication>

#include "../../src/opengl/qgl.h"

int main(int argc, char *argv[])
{
	QTextCodec *utf8 = QTextCodec::codecForName("utf8");
	QTextCodec::setCodecForCStrings(utf8);
	QTextCodec::setCodecForLocale(utf8);
	QTextCodec::setCodecForTr(utf8);

	AllocConsole(); //open the console window
	freopen ("CONOUT$", "w", stdout); //set output available to this console


	QApplication a(argc, argv);
	SLA w;
	w.show();
	return a.exec();
}
