#include <QApplication>
#include "MainWindow.h"
#include "DB.h"

int main(int argc,char **argv)
{
	QApplication app(argc,argv);
	if(!DB::init())
		return -1;
	MainWindow win;
	return app.exec();
}