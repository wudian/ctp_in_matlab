#include "tcstockscene.h"

#include "../service/tcsvcpack.h"
#include "tcstockviewdef.h"
#include "tcviewstockgroup.h"

#define VIEW_DAY_COUNT 100
#define VIEW_DAY_WIDTH 20

#define VIEW_COORDINATE_SPACE 40

tcStockScene::tcStockScene(QObject *pParent)
	: QGraphicsScene(pParent)
{
	SetViewModel(NULL);
}

tcStockScene::~tcStockScene()
{
	ClearAll();
}

void tcStockScene::SetViewModel(tcViewModel *pViewModel)
{
	mViewModel = pViewModel;
	if (mViewModel != NULL) {
		setSceneRect(0, 0, 1, 1);	//refresh the whole view
		setSceneRect(-1 * VIEW_COORDINATE_SPACE, -1 * mViewModel->GetViewHeight(), mViewModel->GetViewItemCount() * mViewModel->GetViewItemWidth() + VIEW_COORDINATE_SPACE + 100, mViewModel->GetViewHeight() + VIEW_COORDINATE_SPACE);
		ReloadStockInfoList();
	}
	else {
		setSceneRect(0, 0, 1, 1);
		ClearAll();
	}
}

bool tcStockScene::LoadStockInfoList(tcStockInfoList *pStockInfoList)
{
	mViewStockInfoList = *pStockInfoList;

	return ReloadStockInfoList();
}

bool tcStockScene::ReloadStockInfoList()
{
	ClearAll();
	if (mViewModel == NULL) {
		tcLogService::CreateLog(this, "View model not defined.");
		return false;
	}

	foreach (tcStockInfo info, mViewStockInfoList) {
		tcViewStockGroup *stockgroup = new tcViewStockGroup(NULL, info, mViewModel);
		this->addItem(stockgroup);
		mViewStockGroupList.append(stockgroup);
	}
	return true;
}

void tcStockScene::ClearAll()
{
	foreach (tcViewStockGroup *stockgroup, mViewStockGroupList) {
		delete stockgroup;
	}
	mViewStockGroupList.clear();
}

void tcStockScene::drawBackground(QPainter *pPainter, const QRectF &pRect)
{
	QRectF scenerect = sceneRect();
	QRectF viewrect = pRect;

	pPainter->setBrush(BACKGROUND_COLOR);
	pPainter->setPen(Qt::NoPen);
	pPainter->drawRect(scenerect);

	if (mViewModel != NULL) {
		//draw x line
		qreal xlinepos = 0;
		pPainter->setPen(Qt::black);
		pPainter->drawLine(0, xlinepos, scenerect.right(), xlinepos);
		QPen pen;
		pen.setColor(Qt::gray);
		pen.setStyle(Qt::DotLine);
		pPainter->setPen(pen);
		int i, j;
		for (i=0, j=0; i<scenerect.right(); i+=mViewModel->GetViewItemWidth(), j++) {
			pPainter->drawLine(i, scenerect.top(), i, xlinepos-1);
			if (j == mViewModel->GetViewItemCount() - 2) {
				pen.setColor(Qt::blue);
				pPainter->setPen(pen);
			}
			else if (j == mViewModel->GetViewItemCount() - 1) {
				pen.setColor(Qt::gray);
				pPainter->setPen(pen);
			}
		}
		//draw the date text
		pPainter->setPen(Qt::black);
		QString itemtext;
		for (i=0, j=0; i<scenerect.right(); i+=mViewModel->GetViewItemWidth(), j++) {
			itemtext = mViewModel->GetViewItemText(j);
			if (itemtext.length() > 0) {
				pPainter->drawLine(i, xlinepos, i, xlinepos+3);
				pPainter->drawText(i, xlinepos + 15, mViewModel->GetViewItemText(j));
			}
			if (mViewModel->IsCurrentItem(j)) {
				pPainter->setPen(Qt::gray);
			}
		}

		//draw y line
		qreal ylinepos = 0;
		pPainter->setPen(Qt::black);
		pPainter->drawLine(ylinepos, scenerect.top(), ylinepos, 0);
		pPainter->setPen(pen);
	}
}
