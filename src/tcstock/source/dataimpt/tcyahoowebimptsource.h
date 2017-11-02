#ifndef tcyahoowebimptsource_h

#define tcyahoowebimptsource_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtNetwork/QNetworkAccessManager>

#include "tcimptsource.h"

/*! \brief tcYahooWebImportSource
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.21

	http://cn.biz.yahoo.com/zhph/shamakeup/index.html
*/
class tcYahooWebImportSource : public tcImportSource
{
	Q_OBJECT

public:
	tcYahooWebImportSource();

	virtual QString GetDescription();

	virtual bool HaveSettingDialog();

	virtual void ShowSettingDialog(QWidget *pParent);

protected:
	virtual bool ImportProcess();

	virtual void CancelImportProcess();

	void GetImportUrlList(QStringList &pUrlList);

	void SetImportUrlList(const QStringList &pUrlList);

	bool ProcessForOnePage(const QString &pPageUrl);

	void ProcessForOneStock(const QDate &pDate, const QString &pText);

protected slots:
	void DoHttpDone(bool pError);

private:
	QNetworkAccessManager *mHttp;

	bool mIsReceiving;

	bool mIsCanceling;

	QString mReceivedData;

};

#endif //tcyahoowebimptsource_h
