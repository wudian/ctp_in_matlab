#ifndef tctoolpadwgt_h

#define tctoolpadwgt_h

#include <QtCore/QVariant>
#include <QWidget>
#include "ui_ui_toolpadwgt.h"

#include "../stockinfo/tcstockinfopack.h"
#include "tcstocklistwgt.h"
class tcMarketManager;

/*! \brief tcToolPadWidget
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	工具组组面板。
*/
class tcToolPadWidget : public QWidget, private Ui_tcToolPadWidget
{
	Q_OBJECT

public:
	tcToolPadWidget(QWidget *pParent);

	~tcToolPadWidget();

protected slots:
	void DoTabStockSelected(tcStockInfoList *pStockInfoList);

private:
	tcStockListWidget *mStockListWidget;

signals:
	void OnStockSelected(tcStockInfoList *pStockInfoList);

};

#endif //tctoolpadwgt_h
