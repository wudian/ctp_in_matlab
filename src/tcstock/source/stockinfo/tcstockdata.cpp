#include "tcstockdata.h"

#include "../service/tcsvcpack.h"

typedef struct {
	unsigned char flag;
	unsigned char version;
} fileheader;

tcStockData::tcStockData(const QDir &pBasePath, const QString &pStockCode, int pYear)
{
	mIsModified = false;
	mBasePath = pBasePath;
	mStockCode = pStockCode;
	mYear = pYear;

	ResetData();

	LoadFromFile();
}

tcStockData::~tcStockData()
{
	if (mIsModified) {
		if (! SaveToFile()) {
			tcLogService::CreateLog(this, "Error when auto save data.");
		}
	}
}

bool tcStockData::CheckSaveData()
{
	if (mIsModified) {
		if (SaveToFile()) {
			mIsModified = false;
			return true;
		}
		return false;
	}
	return true;
}

QString tcStockData::GetStockCode()
{
	return mStockCode;
}

int tcStockData::GetYear()
{
	return mYear;
}

void tcStockData::LoadFromFile()
{
	QString filename = "%1_%2.dat";
	QFileInfo fileinfo(mBasePath, filename.arg(mStockCode).arg(mYear));
	QFile file(fileinfo.filePath());
	if (file.open(QIODevice::ReadOnly)) {
		fileheader header;
		if (file.read((char*)&header, sizeof(header)) != sizeof(header)) {
			tcLogService::CreateLog(this, "Error when read stock data header.");
			file.close();
			ResetData();
			return;
		}
		if (header.flag != 0xFF) {
			tcLogService::CreateLog(this, "Wrong format of the stock data file.");
			file.close();
			ResetData();
			return;
		}
		if (header.version != 0x01) {
			tcLogService::CreateLog(this, "Wrong version of the stock data file.");
			file.close();
			ResetData();
			return;
		}
		if (file.read((char*)mDailyData, sizeof(mDailyData)) != sizeof(mDailyData)) {
			tcLogService::CreateLog(this, "Error when read stock data from file.");
			file.close();
			ResetData();
			return;
		}
		file.close();
	}
}

bool tcStockData::SaveToFile()
{
	QString filename = "%1_%2.dat";
	QFileInfo fileinfo(mBasePath, filename.arg(mStockCode).arg(mYear));
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::WriteOnly)) {
		tcLogService::CreateLog(this, "Error when open file for write.");
		return false;
	}
	fileheader header;
	header.flag = 0xFF;
	header.version = 0x01;
	if (file.write((char*)&header, sizeof(header)) != sizeof(header)) {
		tcLogService::CreateLog(this, "Error when save header into file.");
		file.close();
		return false;
	}
	if (file.write((char*)mDailyData, sizeof(mDailyData)) != sizeof(mDailyData)) {
		tcLogService::CreateLog(this, "Error when save stock data into file.");
		file.close();
		return false;
	}
	file.close();
	return true;
}

void tcStockData::ResetData()
{
	memset(mDailyData, 0, sizeof(mDailyData));
}
