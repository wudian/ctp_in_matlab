#ifndef tcqianlongfileimptsource_h

#define tcqianlongfileimptsource_h

#include <QtCore/QVariant>
#include <QtCore/QObject>

#include "tcimptsource.h"

/*! \brief tcQianLongFileImportSource
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.22
 	
	http://www.qianlong.com.cn
*/
class tcQianLongFileImportSource : public tcImportSource
{
	Q_OBJECT

public:
	tcQianLongFileImportSource();

	virtual QString GetDescription();

	virtual bool HaveSettingDialog();

	virtual void ShowSettingDialog(QWidget *pParent);

protected:
	virtual bool ImportProcess();

	virtual void CancelImportProcess();

};

#endif //tcqianlongfileimptsource_h

