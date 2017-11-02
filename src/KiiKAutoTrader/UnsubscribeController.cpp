#include "UnsubscribeController.h"
#include <qstringlist.h>
#include "QuantBoxApi.h"

UnsubscribeController::UnsubscribeController() {}

void UnsubscribeController::unsubscribe(){
	//从文本框获取输入
	QString &instruments = source->text();
	MD_Unsubscribe(instruments.toStdString().c_str());
	//清空输入框
	source->clear();
}