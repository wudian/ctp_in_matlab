#include "EditOnekeyDialog.h"
#include <qboxlayout.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <qdebug.h>


EditOnekeyDialog::EditOnekeyDialog(){
	//初始化变量
	textArea = new QTextEdit(this);
	textArea->setFixedWidth(400);
	okButton = new QPushButton(QStringLiteral("确定"));
	cancelButton = new QPushButton(QStringLiteral("取消"));
	connect(okButton, SIGNAL(clicked()), this, SLOT(updateIni()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
	okButton->setFixedSize(okButton->sizeHint().width(), okButton->sizeHint().height());
	cancelButton->setFixedSize(cancelButton->sizeHint().width(), cancelButton->sizeHint().height());
	//读取文件内容
	QFile onekeyFile("ini/onekeySub.ini");
	if (!onekeyFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		QMessageBox::information(this, QStringLiteral("错误"), QStringLiteral("打开onekeySub.ini发生错误"));
		abort();
	}
	QTextStream in(&onekeyFile);
	in >> text;
	textArea->setPlainText(text);
	onekeyFile.close();
	//按钮布局
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
	//整体布局
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(textArea);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
	//设置
	setWindowTitle(QStringLiteral("一键订阅列表"));
	setModal(true);
	hide();
}

//展示窗口
void EditOnekeyDialog::showDialog(){
	textArea->setPlainText(text);
	update();
	show();
}

//点击保存后更新配置文件
void EditOnekeyDialog::updateIni(){
	//存下更新内容
	text = textArea->toPlainText().trimmed();
	//更新外部文件
	QFile onekeyFile("ini/onekeySub.ini");
	if (!onekeyFile.open(QIODevice::WriteOnly | QIODevice::Text)){
		QMessageBox::information(this, QStringLiteral("错误"), QStringLiteral("打开onekeySub.ini发生错误"));
		abort();
	}
	QTextStream out(&onekeyFile);
	out << text;
	out.flush();
	onekeyFile.close();
	//对用户发出提醒
	QMessageBox::information(this, QStringLiteral("提醒"), QStringLiteral("更新重启后生效"));
	hide();
}