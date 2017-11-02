#ifndef tcqianlongimpt_h

#define tcqianlongimpt_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QDir>

/*! \brief tcQianlongImporter
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.10

	从钱龙数据导入的管理类，数据来自 www.qianlong.com.cn 。
	目前开发中。
*/
class tcQianlongImporter : public QObject
{
	Q_OBJECT

public:
	tcQianlongImporter();

	~tcQianlongImporter();

	bool ReadFile(const QDir &pPath);

};

#endif //tcqianlongimpt_h
