#ifndef tcdataimptsetupdlg_h

#define tcdataimptsetupdlg_h

#include <QtCore/QVariant>
#include <QtWidgets/QDialog>
#include "ui_ui_dataimptsetupdlg.h"

#include "tcdataimpt.h"

/*! \brief tcDataImporterSetupDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.18
 	
	数据导入设置对话框。
*/
class tcDataImporterSetupDialog : public QDialog, private Ui_tcDataImporterSetupDialog
{
	Q_OBJECT

public:
	tcDataImporterSetupDialog(QWidget *pParent, tcDataImporter *pDataImporter);

	~tcDataImporterSetupDialog();

protected:
	void LoadImportSourceList();

protected slots:
	void DoSourceSelectionChanged(QTableWidgetItem* pCurrent, QTableWidgetItem* pPrevious);

	void DoSourceSetting();

	void DoSourceImport();

private:
	tcDataImporter *mDataImporter;

};

#endif //tcdataimptsetupdlg_h
