#ifndef tcfavtinfodlt_h

#define tcfavtinfodlt_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QItemDelegate>

/*! \brief tcFavouriteInfoDelegate
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.26
 	
	自选股票列表显示用Delegate。被 tcFavouriteInfoDialog 使用。
*/
class tcFavouriteInfoDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	tcFavouriteInfoDelegate(QObject *pParent);

};

#endif //tcfavtinfodlt_h


