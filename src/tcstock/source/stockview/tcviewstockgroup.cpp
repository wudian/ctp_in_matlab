#include "tcviewstockgroup.h"

#include "tcviewentitygroup.h"
#include "tcviewquantitygroup.h"

#define ENTITY_OFFSET 300

tcViewStockGroup::tcViewStockGroup(QObject *pParent, const tcStockInfo pStockInfo, tcViewModel *pViewModel)
	: QObject(pParent)
{
	int i;
	//create the entity group, and the quantity group
	QList<tcViewEntityGroup*> entitylist;
	QList<tcViewQuantityGroup*> quantitylist;
	long minentityval = 0, maxentityval = 0;
	long maxquantityval = 0;
	for (i=0; i<pViewModel->GetViewItemCount(); i++) {
		tcViewModelStockData *data = pViewModel->GetViewItemData(i, pStockInfo);
		Q_ASSERT(data);
		tcViewEntityGroup *entitygroup = new tcViewEntityGroup(this, data);
		entitylist.append(entitygroup);
		if (data->MinPrice != 0 && (data->MinPrice < minentityval || minentityval == 0)) {
			minentityval = data->MinPrice;
		}
		if (data->MaxPrice != 0 && data->MaxPrice > maxentityval) {
			maxentityval = data->MaxPrice;
		}
		tcViewQuantityGroup *quantitygroup = new tcViewQuantityGroup(this, data);
		quantitylist.append(quantitygroup);
		if (data->Quantity != 0 && data->Quantity > maxquantityval) {
			maxquantityval = data->Quantity;
		}
	}
	//reposition and insert entity into this
	if (maxentityval != 0) {
		i = 0;
		foreach(tcViewEntityGroup* entitygroup, entitylist) {
			qreal scale = (pViewModel->GetViewEntityHeight()) / (maxentityval-minentityval);
			entitygroup->SetPosAndScale(i * pViewModel->GetViewItemWidth(), minentityval * scale - pViewModel->GetViewEntityOffset(), scale);
			this->addToGroup(entitygroup);
			i++;
		}
	}
	//reposition and insert quantity into this
	if (maxquantityval != 0) {
		i = 0;
		foreach(tcViewQuantityGroup* quantitygroup, quantitylist) {
			quantitygroup->SetPosAndScale(i * pViewModel->GetViewItemWidth(), (pViewModel->GetViewQuantityHeight()) / maxquantityval);
			this->addToGroup(quantitygroup);
			i++;
		}
	}
}
