
#include <QApplication>
#include "wdMainWindow.h"


int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	
	wdMainWindow win;
	win.showMaximized();

	return a.exec();
}
