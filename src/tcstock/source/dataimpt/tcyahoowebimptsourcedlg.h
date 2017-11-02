#ifndef tcyahoowebimptsourcedlg_h

#define tcyahoowebimptsourcedlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_yahoowebimptsourcedlg.h"

/*! \brief tcYahooWebImportSourceDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.21
*/
class tcYahooWebImportSourceDialog : public QDialog, private Ui_tcYahooWebImportSourceDialog
{
	Q_OBJECT

public:
	tcYahooWebImportSourceDialog(QWidget *pParent);

	~tcYahooWebImportSourceDialog();

	bool SetSettings(const QStringList &pUrlList);

	bool GetSettings(QStringList &pUrlList);

protected slots:
	void UrlListChanged(QTableWidgetItem *pItem);

};

#endif //tcyahoowebimptsourcedlg_h

