#include "tcyahoowebimptsource.h"

#include <QApplication>
#include <QtCore/QUrl>

#include "../service/tcsvcpack.h"
#include "../stockinfo/tcstockinfopack.h"
#include "tcyahoowebimptsourcedlg.h"

tcYahooWebImportSource::tcYahooWebImportSource()
{
	mHttp = NULL;
}

QString tcYahooWebImportSource::GetDescription()
{
	return tr("yahoo stock (http://cn.biz.yahoo.com)");
}

bool tcYahooWebImportSource::HaveSettingDialog()
{
	return true;
}

void tcYahooWebImportSource::ShowSettingDialog(QWidget *pParent)
{
	QStringList urllist;
	GetImportUrlList(urllist);

	tcYahooWebImportSourceDialog dlg(pParent);
	if (! dlg.SetSettings(urllist)) {
		tcLogService::CreateLog(this, "Error when set dialog settings.");
		return;
	}
	if (dlg.exec() != QDialog::Accepted) {
		return;
	}
	if (! dlg.GetSettings(urllist)) {
		tcLogService::CreateLog(this, "Error when get dialog settings.");
		return;
	}
	SetImportUrlList(urllist);
}

bool tcYahooWebImportSource::ImportProcess()
{
	mIsCanceling = false;
	mHttp = new QNetworkAccessManager();
	connect(mHttp, SIGNAL(done(bool)), this, SLOT(DoHttpDone(bool)));

	QString useproxy = tcCfgService::GetGlobalAttribute("UseProxy", "false");
	if (useproxy == "true") {
		QString proxyserver = tcCfgService::GetGlobalAttribute("ProxyServer", "");
		QString proxyport = tcCfgService::GetGlobalAttribute("ProxyPort", "80");
		QString proxyusername = tcCfgService::GetGlobalAttribute("ProxyUserName", "");
		QString proxypassword = tcCfgService::GetGlobalAttribute("ProxyPassword", "");
		//mHttp->setProxy(proxyserver, proxyport.toInt(), proxyusername, proxypassword);
	}

	QStringList urllist;
	GetImportUrlList(urllist);
	int i;
	for (i=0; i<urllist.count(); i++) {
		ProcessForOnePage(urllist[i]);
		if (mIsCanceling) {
			emit OnAppendMessage(tr("Import procedure canceled by user."), false);
			break;
		}
		emit OnUpdateProgress(i*100 / urllist.count());
	}
	emit OnUpdateProgress(100);

	delete mHttp;
	mHttp = NULL;

	OnAppendMessage(tr("All done."), true);
	return true;
}

void tcYahooWebImportSource::CancelImportProcess()
{
	mIsCanceling = true;
}

void tcYahooWebImportSource::GetImportUrlList(QStringList &pUrlList)
{
	pUrlList.clear();
	int urlcount = tcCfgService::GetAttribute(this, "UrlCount", "0").toInt();
	int i;
	QString urlkey = "Url_%1";
	for (i=0; i<urlcount; i++) {
		QString url = tcCfgService::GetAttribute(this, urlkey.arg(i), "");
		pUrlList.append(url);
	};
}

void tcYahooWebImportSource::SetImportUrlList(const QStringList &pUrlList)
{
	QString urlcount = "%1";
	tcCfgService::SetAttribute(this, "UrlCount", urlcount.arg(pUrlList.count()));
	int i;
	QString urlkey = "Url_%1";
	for (i=0; i<pUrlList.count(); i++) {
		tcCfgService::SetAttribute(this, urlkey.arg(i), pUrlList[i]);
	}
}

bool tcYahooWebImportSource::ProcessForOnePage(const QString &pPageUrl)
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

	//get the date from received data
	QRegExp rxdate("<td><div>(\\d\\d\\d\\d-\\d\\d-\\d\\d) \\d\\d:\\d\\d:\\d\\d</div></td>");
	rxdate.setMinimal(true);
	int datepos = 0;
	datepos = rxdate.indexIn(mReceivedData, datepos);
	if (datepos == -1) {
		emit OnAppendMessage(tr("Can not extract the date from this page."), false);
		return true;
	}
	emit OnAppendMessage(tr("The date is: %1").arg(rxdate.cap(1)), true);
	QDate date = QDate::fromString(rxdate.cap(1), "yyyy-MM-dd");

	//process the data
	QRegExp rx("<tr align=center bgcolor=(?:\\S+)><td>(?:\\S+)</td>(.+)(?=</tr>)");
	rx.setMinimal(true);
	int pos = 0;
	while ((pos = rx.indexIn(mReceivedData, pos)) != -1) {
		ProcessForOneStock(date, rx.cap(1));
		pos += rx.matchedLength();
	}
	return true;
}

void tcYahooWebImportSource::ProcessForOneStock(const QDate &pDate, const QString &pText)
{
	/* process the text like this:
		<td><a target=_blank href=http://cn.finance.yahoo.com/q?s=600701.SS>600701</a></td>
		<td><a target=_blank href=http://cn.finance.yahoo.com/q?s=600701.SS>XXXXX</a></td>
		<td align=right><span class=black>5.15</span></td>
		<td align=right><span class=STYLE4>5.16</span></td>
		<td><span class=black>5.11-5.67</span></td>
		<td align=right><span class=STYLE4>5.67</span></td>
		<td align=right><span class=STYLE4>10.10%</span></td>
		<td align=right><span class=STYLE4>0.52</span></td>
		<td align=right><span class=black>21552.92</span></td>
		<td align=right class=black>397073.36</td>
		<td align=right><span class=style4>10.87%</span></td>
		<td align=right><span class=style4>11.37%</span></td>
		<td><a target=_blank href=http://cn.finance.yahoo.com/q?s=600701.SS><img src=http://ichart.finance.yahoo.com/h?s=600701.SS width=60 height=16 border=0 /></a></td>
	*/
	QRegExp rx("<.+>([^<>]+)</.+>");
	rx.setMinimal(true);
	int pos = 0;
	int itemindex = 0;
	QString stockcode, stockname, closeprice, openprice, minmaxprice, minprice, maxprice, currentprice, totalprice, quantity;
	while ((pos = rx.indexIn(pText, pos)) != -1) {
		switch (itemindex) {
		case 0:	//stock code
			stockcode = rx.cap(1);
			break;
		case 1:	//stock name
			stockname = rx.cap(1);
			break;
		case 2: //close price (yesterday)
			closeprice = rx.cap(1);
			break;
		case 3:	//open price
			openprice = rx.cap(1);
			break;
		case 4:	//min/max price
			minmaxprice = rx.cap(1);	//this data's format is like: 22.01-23.71
			if (minmaxprice.indexOf('-')>=0) {
				minprice = minmaxprice.left(minmaxprice.indexOf('-'));
				minmaxprice.remove(0, minmaxprice.indexOf('-')+1);
				maxprice = minmaxprice;
			}
			break;
		case 5:	//current price
			currentprice = rx.cap(1);
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:	//total price
			totalprice = rx.cap(1);
			break;
		case 9:	//quantity
			quantity = rx.cap(1);
			break;
		default:
			break;
		}
		pos += rx.matchedLength();
		itemindex++;
	}

	emit OnAppendMessage(tr("Processing stock %1 ...").arg(stockcode), true);

	if (itemindex <10) {
		emit OnAppendMessage(tr("Error when extract data of stock."), false);
		return;
	}

	//get the stock object
	tcStockInfo stockinfo(stockcode);
	if (! stockinfo.IsAvailable()) {
		emit OnAppendMessage(tr("The stock not exists."), false);
		return;
	}

	//set the data of yesterday
	QDate date = pDate.addDays(-1);
	if (date.dayOfWeek() == 6) {
		date = date.addDays(-1);
	}
	else if (date.dayOfWeek() == 7) {
		date = date.addDays(-2);
	}

	tcStockDailyData dailydata;
	if (! stockinfo->ReadData(date, &dailydata)) {
		emit OnAppendMessage(tr("Error when get daily data of stock."), false);
		return;
	}
	dailydata.ClosePrice = long(closeprice.toFloat() * 100);
	if (! stockinfo->WriteData(date, &dailydata)) {
		emit OnAppendMessage(tr("Error when set daily data of stock."), false);
		return;
	}

	//set the data of today
	date = pDate;
	if (! stockinfo->ReadData(date, &dailydata)) {
		emit OnAppendMessage(tr("Error when get daily data of stock."), false);
		return;
	}
	dailydata.OpenPrice = long(openprice.toFloat() * 100);
	dailydata.ClosePrice = long(currentprice.toFloat() * 100);
	dailydata.MaxPrice = long(maxprice.toFloat() * 100);
	dailydata.MinPrice = long(minprice.toFloat() * 100);
	dailydata.TotalPrice = long(totalprice.toFloat());
	dailydata.Quantity = long(quantity.toFloat());
	if (! stockinfo->WriteData(date, &dailydata)) {
		emit OnAppendMessage(tr("Error when set daily data of stock."), false);
		return;
	}
}

void tcYahooWebImportSource::DoHttpDone(bool pError)
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
