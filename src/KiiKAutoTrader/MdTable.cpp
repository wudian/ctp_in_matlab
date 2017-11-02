#include "MdTable.h"
using namespace std;

MdTable::MdTable()
{
	this->setColumnCount(7);
	//设置表头内容 
	QStringList header;
	header << QStringLiteral("合约代码") << QStringLiteral("合约名") << QStringLiteral("最新价") << QStringLiteral("买价") << QStringLiteral("买量") << QStringLiteral("卖价") <<
		QStringLiteral("卖量");
	this->setHorizontalHeaderLabels(header);
	//设置不可编辑
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//设置定时器
	updateTimer = new QTimer(this);
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(refreshTable()));
	unsubUpdateTimer = new QTimer(this);
	unsubUpdateTimer->setSingleShot(true);
	connect(unsubUpdateTimer, SIGNAL(timeout()), this, SLOT(updateTableForUnsub()));
}

//断开连接后初始化表格
void MdTable::resetTable(){
	updateTimer->stop();
	this->clearContents();	//清除表格内容
	//注意从最后一行往前删除
	int i = instruInTable.size();
	for (; i >= 0; i--){
		this->removeRow(i);
	}
	instruInTable.clear();
}

//刷新表格
void MdTable::refreshTable()
{
	
}

//因为用户选择而更新列表,参数newInstru由用户在对话框中选择合约后传过来
void MdTable::updateTableForSelect(set<QString>& newInstru)
{
	updateTimer->stop();   //停止更新表格
	for (auto iter = instruInTable.begin(); iter != instruInTable.end();){
		if (newInstru.find(*iter) == newInstru.end()){	//去掉不要的合约
			iter = instruInTable.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	for (auto iter = newInstru.begin(); iter != newInstru.end(); iter++){
		auto i = instruInTable.begin();
		for (; i != instruInTable.end(); i++){
			if ((*i) == (*iter)){
				break;
			}
		}
		if (i == instruInTable.end()){ //添加新进来的合约
			instruInTable.push_back((*iter));
		}
	}
	
	//更新显示的表格
	this->clearContents();
	int rowCount = this->rowCount();
	for (; rowCount >= 0; rowCount--){
		this->removeRow(rowCount);
	}
	int row = 0;
	for (auto iter = instruInTable.begin(); iter != instruInTable.end(); iter++){
		
		row++;
	}
	this->update();
	updateTimer->start(1000);
}

//退订后过1.5秒更新
void MdTable::callUnsubUpdateTimer(){
	unsubUpdateTimer->start(1500);
}

//因为用户退订而更新列表
void MdTable::updateTableForUnsub(){
	
}