#include <QtCore/QCoreApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	/*QMediaPlayer *player = new QMediaPlayer;
	player->setMedia(QUrl::fromLocalFile("F:\\CTP-MATLAB\\src\\qtTest\\a.wav"));
	player->setVolume(50);
	player->play();*/
	system("ping www.baidu.com");

	return a.exec();
}
