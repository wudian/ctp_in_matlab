/*! \brief Teacher.Cheng Stock
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.02
*/

#include <QApplication>
#include <QSplashScreen>
//#include <QCleanlooksStyle>
#include <QtCore/QTranslator>

#include "tcdefine.h"
#include "tcresource.h"
#include "service/tcsvcpack.h"
#include "tcmainwnd.h"

int main(int argc, char* argv[])
{
	int sts;

	QApplication app(argc, argv);

	//QApplication::setStyle(new QCleanlooksStyle);

	tcLogService::Initialize(argc, argv);
	tcLogService::CreateLog(&app, "=========== SYSTEM START ===========");
	tcLogService::CreateLog(&app, "System Name : " + QString(SYSTEM_NAME));
	tcLogService::CreateLog(&app, "System Version : " + QString(SYSTEM_VERSION));

	sts = qInitResources();
	if (! sts) {
		tcLogService::CreateLog(&app, "Error when ini resource.");
		return -1;
	}

	QPixmap pixmap(":/images/splash.png");
	QSplashScreen splash(pixmap);
	splash.show();

#ifdef WIN32
	QFont font;
	font.setFamily(QString::fromUtf8("simsun"));
	font.setPointSize(9);
	font.setBold(false);
	font.setItalic(false);
	font.setUnderline(false);
	font.setWeight(50);
	font.setStrikeOut(false);
	app.setFont(font);
#endif

	QTranslator translator;
	sts = translator.load("F:/CTP-MATLAB/bin/tcstock.qm");
	if (! sts) {
		tcLogService::CreateLog(&app, "Error when load translate file");
		return -1;
	}
	app.installTranslator(&translator);

	if (! tcCfgService::Initialize(argc, argv)) {
		tcLogService::CreateLog(&app, "Error when init config service.");
		return -1;
	}
	if (! tcObjService::Initialize(argc, argv)) {
		tcLogService::CreateLog(&app, "Error when init object service.");
		return -1;
	}

	tcMainWindow window(NULL);
	window.showMaximized();
	splash.finish(&window);

	sts = app.exec();

	tcLogService::CreateLog(&app, "=========== SYSTEM END ===========");

	qCleanupResources();

	tcObjService::Finalize();
	tcCfgService::Finalize();
	tcLogService::Finalize();

	return 0;
}
