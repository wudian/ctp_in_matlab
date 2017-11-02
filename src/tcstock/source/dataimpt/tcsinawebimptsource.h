#ifndef tcsinawebimptsource_h

#define tcsinawebimptsource_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtNetwork/QNetworkAccessManager>

#include "tcimptsource.h"

/*! \brief tcSinaWebImportSource
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.18
 	
	从新浪网站导入股票每日数据。
	http://stock.sina.com.cn/stock/quote/sha0.html
*/
class tcSinaWebImportSource : public tcImportSource
{
	Q_OBJECT

public:
	tcSinaWebImportSource();

	virtual QString GetDescription();

	virtual bool HaveSettingDialog();

	virtual void ShowSettingDialog(QWidget *pParent);

protected:
	virtual bool ImportProcess();

	virtual void CancelImportProcess();

	void GetImportUrlList(QStringList &pUrlList);

	void SetImportUrlList(const QStringList &pUrlList);

	bool ProcessForOnePage(const QString &pPageUrl);

	void ProcessForOneStock(const QString &pText);

protected slots:
	void DoHttpDone(bool pError);

private:
	QNetworkAccessManager *mHttp;

	bool mIsReceiving;

	bool mIsCanceling;

	QString mReceivedData;

};

#endif //tcsinawebimptsource_h
