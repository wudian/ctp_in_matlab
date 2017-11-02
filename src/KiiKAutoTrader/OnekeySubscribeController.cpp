#include "OnekeySubsribeController.h"
#include "GVAR.h"
#include <qmessagebox.h>
using std::shared_ptr;

OnekeySubsribeController::OnekeySubsribeController(){
	receiver = nullptr;
}

void OnekeySubsribeController::setReceiver(shared_ptr<Receiver> r){
	receiver = r;
}

//恢复初始状态
void OnekeySubsribeController::reset(){
	receiver = nullptr;
}

//一键订阅
void OnekeySubsribeController::onekeySubscribe(){
	int count = onekeyInstru.size();
	if (count == 0){
		QMessageBox::information(0, QStringLiteral("提示"), QStringLiteral("一键订阅合约列表为空"));
		return;
	}
	char* *ppwdTickID = new char*[count];
	for (int i = 0; i < count; i++){
		ppwdTickID[i] = new char[7];
		strcpy(ppwdTickID[i], onekeyInstru.at(i).toStdString().c_str());
	}
	receiver->subscribeData(ppwdTickID, count);
	QMessageBox::information(0, QStringLiteral("提示"), QStringLiteral("订阅成功"));
}