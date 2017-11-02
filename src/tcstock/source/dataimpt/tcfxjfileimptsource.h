#ifndef tcfxjfileimptsource_h

#define tcfxjfileimptsource_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtNetwork/QNetworkAccessManager>

#include "tcimptsource.h"

typedef struct {
	bool DownloadZipFile;
	QString ZipFileUrl;
	QString DataFilePath;
	QString LastSuccessDate;
} tcFxjFileImportSourceOption;

/*! \brief tcFxjFileImportSource
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.22
 	
	http://www.fxj.net.cn
*/
class tcFxjFileImportSource : public tcImportSource
{
	Q_OBJECT

public:
	tcFxjFileImportSource();

	virtual QString GetDescription();

	virtual bool HaveSettingDialog();

	virtual void ShowSettingDialog(QWidget *pParent);

protected:
	virtual bool ImportProcess();

	virtual void CancelImportProcess();

	void GetOptions(tcFxjFileImportSourceOption &pOption);

	void SetOptions(const tcFxjFileImportSourceOption &pOption);

	bool ProcessForOnePage(const QDate &pDate, const QString &pPageUrl);

	bool ProcessForOneFile(const QString &pFileName);

	bool ProcessForOneZipFile(const QDate &pDate, const QString &pFileName);

	bool ProcessForOneDadFile(const QDate &pDate, const QString &pFileName);

	bool ProcessForOneDadStream(const QDate &pDate, const QByteArray &pData);

protected slots:
	void DoHttpDone(bool pError);

private:
	QNetworkAccessManager *mHttp;

	bool mIsReceiving;

	bool mIsCanceling;

	QByteArray mReceivedData;

};

#endif //tcfxjfileimptsource_h
