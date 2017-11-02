#include "tcfxjfileimptsource.h"

#include <QApplication>
#include <QtCore/QUrl>
#include <QtCore/QTemporaryFile>
#include <QtNetwork/QNetworkProxy>

#include "../service/tcsvcpack.h"
#include "../stockinfo/tcstockinfopack.h"
#include "tcfxjfileimptsourcedlg.h"
#include "../thirdparty/quazip/quazip.h"
#include "../thirdparty/quazip/quazipfile.h"

#pragma pack(push, 1)
typedef struct {
	char header[4];
	char market[2];
	char stockcode[6];
	float data1;
	float data2;
	float data3;
	float data4;
	float data5;
	float data6;
	float openprice;
	float maxprice;
	float minprice;
	float closeprice;
	float quantity;
	float totalprice;
	float reserved;
} fxjdata;
#pragma pack(pop)

tcFxjFileImportSource::tcFxjFileImportSource()
{
	mHttp = NULL;
}

QString tcFxjFileImportSource::GetDescription()
{
	return tr("daily file of fxj (http://www.fxj.net.cn)");
}

bool tcFxjFileImportSource::HaveSettingDialog()
{
	return true;
}

void tcFxjFileImportSource::ShowSettingDialog(QWidget *pParent)
{
	tcFxjFileImportSourceOption option;
	GetOptions(option);

	tcFxjFileImportSourceDialog dlg(pParent);
	if (! dlg.SetSettings(option)) {
		tcLogService::CreateLog(this, "Error when set dialog settings.");
		return;
	}
	if (dlg.exec() != QDialog::Accepted) {
		return;
	}
	if (! dlg.GetSettings(option)) {
		tcLogService::CreateLog(this, "Error when get dialog settings.");
		return;
	}
	SetOptions(option);
}

bool tcFxjFileImportSource::ImportProcess()
{
	mIsCanceling = false;

	tcFxjFileImportSourceOption option;
	GetOptions(option);
	QDate successdate = QDate::fromString(option.LastSuccessDate, "yyyyMMdd");
	QDate begindate = successdate.addDays(1);
	QDate curdate = QDate::currentDate();
	if (curdate.addDays(-30) > begindate) {	//receive max 30 day's data
		begindate = curdate.addDays(-30);
	}

	if (option.DownloadZipFile) {	//download zip file from web site
		if (begindate.daysTo(curdate) >= 0) {
			mHttp = new QNetworkAccessManager();
			connect(mHttp, SIGNAL(done(bool)), this, SLOT(DoHttpDone(bool)));

			QString useproxy = tcCfgService::GetGlobalAttribute("UseProxy", "false)");
			if (useproxy == "true") {
				QString proxyserver = tcCfgService::GetGlobalAttribute("ProxyServer", "");
				QString proxyport = tcCfgService::GetGlobalAttribute("ProxyPort", "80");
				QString proxyusername = tcCfgService::GetGlobalAttribute("ProxyUserName", "");
				QString proxypassword = tcCfgService::GetGlobalAttribute("ProxyPassword", "");
				QNetworkProxy *proxy = new	QNetworkProxy(QNetworkProxy::HttpProxy, proxyserver, proxyport.toInt(), proxyusername, proxypassword);
				mHttp->setProxy(*proxy);
			}

			QDate date;
			for (date = begindate; date <= curdate; date = date.addDays(1)) {
				if (ProcessForOnePage(date, option.ZipFileUrl.arg(date.toString("yyyyMMdd")))) {
					successdate = date;	//update the success date
				}
				if (mIsCanceling) {
					emit OnAppendMessage(tr("Import procedure canceled by user."), false);
					break;
				}
				emit OnUpdateProgress(begindate.daysTo(date) * 100 / (begindate.daysTo(curdate)+1));\
			}

			delete mHttp;
			mHttp = NULL;
		}
	}
	else {		//load the zip/dad file from local system
		QDir dir(option.DataFilePath);
		QStringList filelist = dir.entryList(QDir::Files | QDir::Readable, QDir::Name | QDir::IgnoreCase);
		int i;
		for (i=0; i<filelist.count(); i++) {
			ProcessForOneFile(dir.absoluteFilePath(filelist[i]));
			if (mIsCanceling) {
				emit OnAppendMessage(tr("Import procedure canceled by user."), false);
				break;
			}
			emit OnUpdateProgress(i * 100 / filelist.count());
			qApp->processEvents();
		}
	}

	option.LastSuccessDate = successdate.toString("yyyyMMdd");
	SetOptions(option);
	OnUpdateProgress(100);

	OnAppendMessage(tr("All done."), true);
	return true;
}

void tcFxjFileImportSource::CancelImportProcess()
{
	mIsCanceling = true;
}

void tcFxjFileImportSource::GetOptions(tcFxjFileImportSourceOption &pOption)
{
	pOption.DownloadZipFile = (tcCfgService::GetAttribute(this, "DownloadZipFile", "true") == "true");
	pOption.ZipFileUrl = tcCfgService::GetAttribute(this, "ZipFileUrl", "http://down.fxj.net.cn/sjdownload/day/%1.zip");
	pOption.DataFilePath = tcCfgService::GetAttribute(this, "DataFilePath", "");
	pOption.LastSuccessDate = tcCfgService::GetAttribute(this, "LastSuccessDate", "");
}

void tcFxjFileImportSource::SetOptions(const tcFxjFileImportSourceOption &pOption)
{
	tcCfgService::SetAttribute(this, "DownloadZipFile", pOption.DownloadZipFile ? "true" : "false");
	tcCfgService::SetAttribute(this, "ZipFileUrl", pOption.ZipFileUrl);
	tcCfgService::SetAttribute(this, "DataFilePath", pOption.DataFilePath);
	tcCfgService::SetAttribute(this, "LastSuccessDate", pOption.LastSuccessDate);
}

bool tcFxjFileImportSource::ProcessForOnePage(const QDate &pDate, const QString &pPageUrl)
{
	emit OnAppendMessage(tr("Begin import from page: %1.").arg(pPageUrl), true);

	/*QUrl url(pPageUrl);
	mHttp->setHost(url.host(), url.port() != -1 ? url.port() : 80);
	if (! url.userName().isEmpty()) {
		mHttp->setUser(url.userName(), url.password());
	}
	
	mIsReceiving = true;
	mHttp->get(pPageUrl);*/

	while (mIsReceiving) {
		qApp->processEvents();
		if (mIsCanceling) {
			return false;
		}
	}
	if (mReceivedData.isEmpty()) {
		return false;
	}

	QTemporaryFile file;	//this file will delete it's self when destruct
	if (! file.open()) {
		emit OnAppendMessage(tr("Error when open temporary file."), false);
		return false;
	}
	if (file.write(mReceivedData) != mReceivedData.size()) {
		emit OnAppendMessage(tr("Error when write temporary file."), false);
		return false;
	}
	if (! ProcessForOneZipFile(pDate, file.fileName())) {
		return false;
	}
	file.close();
	return true;
}

bool tcFxjFileImportSource::ProcessForOneFile(const QString &pFileName)
{
	QFileInfo fileinfo(pFileName);
	QDate date = QDate::fromString(fileinfo.baseName(), "yyyyMMdd");
	QString fileextname = fileinfo.completeSuffix();
	if (fileextname.compare("zip", Qt::CaseInsensitive) == 0) {	//this is a zip file
		return ProcessForOneZipFile(date, pFileName);
	}
	else if (fileextname.compare("dad", Qt::CaseInsensitive) == 0) {	//this is a dad file
		return ProcessForOneDadFile(date, pFileName);
	}
	else {	//unknown file format, ignore it
		return true;
	}
}

bool tcFxjFileImportSource::ProcessForOneZipFile(const QDate &pDate, const QString &pFileName)
{
	emit OnAppendMessage(tr("Processing ZIP file: %1.").arg(pFileName), true);
	QuaZip zip(pFileName);
	if (! zip.open(QuaZip::mdUnzip)) {
		emit OnAppendMessage(tr("Error when open zip file."), false);
		return false;
	}
	if (! zip.goToFirstFile()) {
		emit OnAppendMessage(tr("Not data in the zip file."), false);
		return false;
	}
	do {
		QuaZipFile file(&zip);
		emit OnAppendMessage(tr("Processing archive %1.").arg(file.getActualFileName()), true);

		if (! file.open(QIODevice::ReadOnly)) {
			emit OnAppendMessage(tr("Error when extract zip data."), false);
			return false;
		}
		QByteArray dadbytearray = file.readAll();
		ProcessForOneDadStream(pDate, dadbytearray);
	} while (zip.goToNextFile());
	return true;
}

bool tcFxjFileImportSource::ProcessForOneDadFile(const QDate &pDate, const QString &pFileName)
{
	emit OnAppendMessage(tr("Processing DAD file: %1.").arg(pFileName), true);
	QFile file(pFileName);
	if (! file.open(QIODevice::ReadOnly)) {
		emit OnAppendMessage(tr("Error when open dad file."), false);
		return false;
	}
	QByteArray dadbytearray = file.readAll();
	return ProcessForOneDadStream(pDate, dadbytearray);
}

bool tcFxjFileImportSource::ProcessForOneDadStream(const QDate &pDate, const QByteArray &pData)
{
	QDataStream stream(pData);

	char fileheader[16];
	if (stream.readRawData(fileheader, sizeof(fileheader)) != sizeof(fileheader)) {
		emit OnAppendMessage(tr("Error when read file header."), false);
		return false;
	}
	if ((fileheader[0] != char(0x8c)) || (fileheader[1] != char(0x19)) || (fileheader[2] != char(0xfc)) || (fileheader[3] != char(0x33))) {
		emit OnAppendMessage(tr("Wrong DAD file format."), false);
		return false;
	}

	fxjdata data;
	QString stockcode;
	while (! stream.atEnd()) {
		if (mIsCanceling) {
			return false;
		}
		qApp->processEvents();

		if (stream.readRawData((char*)&data, sizeof(data)) != sizeof(data)) {
			emit OnAppendMessage(tr("End of file."), true);
			break;
		}
		stockcode = data.stockcode;
		emit OnAppendMessage(tr("Processing stock %1 ...").arg(stockcode), true);

		tcStockInfo stockinfo(stockcode);
		if (! stockinfo.IsAvailable()) {
			emit OnAppendMessage(tr("The stock not exists."), false);
			continue;
		}
		tcStockDailyData dailydata;
		if (! stockinfo->ReadData(pDate, &dailydata)) {
			emit OnAppendMessage(tr("Error when get daily data of stock."), false);
			continue;
		}
		dailydata.OpenPrice = data.openprice * 100;
		dailydata.ClosePrice = data.closeprice * 100;
		dailydata.MaxPrice = data.maxprice * 100;
		dailydata.MinPrice = data.minprice * 100;
		dailydata.TotalPrice = data.totalprice / 1000;
		dailydata.Quantity = data.quantity;
		if (! stockinfo->WriteData(pDate, &dailydata)) {
			emit OnAppendMessage(tr("Error when set daily data of stock."), false);
			continue;
		}
	}

	return true;
}

void tcFxjFileImportSource::DoHttpDone(bool pError)
{
	/*if (pError) {
		tcLogService::CreateLog(this, "Done Error: " + mHttp->errorString());
		emit OnAppendMessage(tr("Error: %1").arg(mHttp->errorString()), false);
	}
	else {
		Q_ASSERT(mHttp);
		mReceivedData = mHttp->readAll();
		emit OnAppendMessage(tr("Received successful."), true);
	}*/
	mIsReceiving = false;
}
