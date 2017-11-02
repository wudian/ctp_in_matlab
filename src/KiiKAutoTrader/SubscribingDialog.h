#ifndef _SUBSCRIBING_DIALOG_H_
#define _SUBSCRIBING_DIALOG_H_

#include <qdialog.h>
#include <qtextedit.h>
#include <qpushbutton.h>

class SubscribingDialog : public QDialog
{
	Q_OBJECT
public:
	SubscribingDialog();
	void showDialog();
private:
	QTextEdit *textArea;
	QPushButton *okButton;
};

#endif