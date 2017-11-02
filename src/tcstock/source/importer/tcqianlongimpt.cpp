#include "tcqianlongimpt.h"

#include "../service/tcsvcpack.h"

#pragma pack(push, 1)
typedef struct {
	int date;
	int openprice;
	int maxprice;
	int minprice;
	int closeprice;
	int totalprice;
	int quantity;
	int reserve1;
	int reserve2;
	int reserve3;
} qianlongdata;
#pragma pack(pop)

tcQianlongImporter::tcQianlongImporter()
{
}

tcQianlongImporter::~tcQianlongImporter()
{
}

bool tcQianlongImporter::ReadFile(const QDir &pPath)
{
	QFileInfo fileinfo(pPath, "SHA.DA_");
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::ReadOnly)) {
		return false;
	}
	while (! file.atEnd()) {
		char stockname[16];
		if (file.read(stockname, sizeof(stockname)) != sizeof(stockname)) {
			return false;
		}
		//int datalen;
		//if (file.read((char*)&datalen, sizeof(datalen)) != sizeof(datalen)) {
		//	return false;
		//}
		/*
		int data1;
		if (file.read((char*)&data1, sizeof(data1)) != sizeof(data1)) {
			return false;
		}
		float data2;
		if (file.read((char*)&data2, sizeof(data2)) != sizeof(data2)) {
			return false;
		}
		QString text = "StockName: %1, DataLen: %2, data1: %3, data2: %4";
		text = text.arg(stockname).arg(datalen).arg(data1).arg(data2);
		*/
		qianlongdata data;
		if (file.read((char*)&data, sizeof(data)) != sizeof(data)) {
			return false;
		}
		QString text = "StockName=%1, %2";
		text = text.arg(stockname).arg(sizeof(long));
		tcLogService::CreateLog(this, text);
		break;
	}
	file.close();
	return true;
}
