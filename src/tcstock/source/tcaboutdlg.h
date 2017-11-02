#ifndef tcaboutdlg_h

#define tcaboutdlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_aboutdlg.h"

/*! \brief tcAboutDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.13
 	
	系统“关于”对话框。
*/
class tcAboutDialog : public QDialog, private Ui_tcAboutDialog
{
	Q_OBJECT

public:
	tcAboutDialog(QWidget *pParent);

protected:
	void SetAboutText();

};


#endif //tcaboutdlg_h
