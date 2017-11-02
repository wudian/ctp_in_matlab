#ifndef tcsinawebimptsourcedlg_h

#define tcsinawebimptsourcedlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_sinawebimptsourcedlg.h"

/*! \brief tcSinaWebImportSourceDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.21
*/
class tcSinaWebImportSourceDialog : public QDialog, private Ui_tcSinaWebImportSourceDialog
{
	Q_OBJECT

public:
	tcSinaWebImportSourceDialog(QWidget *pParent);

	~tcSinaWebImportSourceDialog();

	bool SetSettings(const QStringList &pUrlList);

	bool GetSettings(QStringList &pUrlList);

protected slots:
	void UrlListChanged(QTableWidgetItem *pItem);

};

#endif //tcsinawebimptsourcedlg_h

