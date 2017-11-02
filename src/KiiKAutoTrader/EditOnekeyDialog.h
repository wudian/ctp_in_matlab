#ifndef _EDIT_ONEKEY_DIALOG_H_
#define _EDIT_ONEKEY_DIALOG_H_

#include <qdialog.h>
#include <qtextedit.h>
#include <qpushbutton.h>

class EditOnekeyDialog :public QDialog{
	Q_OBJECT
public:
	EditOnekeyDialog();
	void showDialog();
private:
	QTextEdit *textArea;
	QPushButton *okButton;
	QPushButton *cancelButton;
	QString text;			//记录原来文件中的内容
private slots:
	void updateIni();
};

#endif