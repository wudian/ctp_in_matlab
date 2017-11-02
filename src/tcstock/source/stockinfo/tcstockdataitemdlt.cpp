#include "tcstockdataitemdlt.h"

#include <QtCore/QModelIndex>
#include <QLineEdit>

#include "tcstockdataitemmdl.h"

tcStockDataItemDelegate::tcStockDataItemDelegate(QObject *pParent)
	: QItemDelegate(pParent)
{

}

QWidget* tcStockDataItemDelegate::createEditor(QWidget *pParent, const QStyleOptionViewItem &pViewItem, const QModelIndex &pIndex) const
{
	switch (pIndex.column()) {
		case 2: case 3: case 4: case 5:
			{
			QLineEdit *editor = new QLineEdit(pParent);
			editor->setInputMask("00000.00");
			//editor->setValidator(new QDoubleValidator(0, 9999, 2, editor));
			connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
			return editor;
			}
		case 6: case 7:
			{
			QLineEdit *editor = new QLineEdit(pParent);
			editor->setInputMask("000000");
			//editor->setValidator(new QIntValidator(editor));
			connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
			return editor;
			}
		default:
			return NULL;
	}
}

void tcStockDataItemDelegate::setEditorData(QWidget *pEditor, const QModelIndex &pIndex) const
{
	QLineEdit *editor = qobject_cast<QLineEdit*>(pEditor);
	if (! editor) {
		return;
	}
	tcStockDataItemModel *model = (tcStockDataItemModel*)(pIndex.model());
	if (! model) {
		return;
	}
	const tcStockDailyData *data = model->ReadData(pIndex.row());
	if (! data) {
		return;
	}
	QString floatstr;
	if (pIndex.column() == 2) {
		floatstr.setNum(qreal(data->OpenPrice) / 100.0, 'F', 2);
	}
	else if (pIndex.column() == 3) {
		floatstr.setNum(qreal(data->ClosePrice) / 100.0, 'F', 2);
	}
	else if (pIndex.column() == 4) {
		floatstr.setNum(qreal(data->MaxPrice) / 100.0, 'F', 2);
	}
	else if (pIndex.column() == 5) {
		floatstr.setNum(qreal(data->MinPrice) / 100.0, 'F', 2);
	}
	else if (pIndex.column() == 6) {
		floatstr.setNum(data->TotalPrice);
	}
	else if (pIndex.column() == 7) {
		floatstr.setNum(data->Quantity);
	}
	else {
		return;
	}
	editor->setText(floatstr);
}

void tcStockDataItemDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &pIndex) const
{
	QLineEdit *editor = qobject_cast<QLineEdit*>(pEditor);
	if (! editor) {
		return;
	}
	tcStockDataItemModel *model = (tcStockDataItemModel*)(pIndex.model());
	if (! model) {
		return;
	}
	const tcStockDailyData *data = model->ReadData(pIndex.row());
	if (! data) {
		return;
	}
	tcStockDailyData newdata = *data;
	if (pIndex.column() == 2) {
		newdata.OpenPrice = long(editor->text().toDouble() * 100);
	}
	else if (pIndex.column() == 3) {
		newdata.ClosePrice = long(editor->text().toDouble() * 100);
	}
	else if (pIndex.column() == 4) {
		newdata.MaxPrice = long(editor->text().toDouble() * 100);
	}
	else if (pIndex.column() == 5) {
		newdata.MinPrice = long(editor->text().toDouble() * 100);
	}
	else if (pIndex.column() == 6) {
		newdata.TotalPrice = editor->text().toInt();
	}
	else if (pIndex.column() == 7) {
		newdata.Quantity = editor->text().toInt();
	}
	else {
		return;
	}
	if (! model->WriteData(pIndex.row(), &newdata)) {
		return;
	}
}

void tcStockDataItemDelegate::commitAndCloseEditor()
{
	QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}
