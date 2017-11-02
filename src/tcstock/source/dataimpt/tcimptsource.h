#ifndef tcimptsource_h

#define tcimptsource_h

#include <QtCore/QVariant>
#include <QtCore/QObject>

/*! \brief tcImportSource
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.18
 	
	数据导入源的基类。
*/
class tcImportSource : public QObject
{
	Q_OBJECT

public:
	tcImportSource();

	~tcImportSource();

	virtual QString GetDescription();

	virtual bool HaveSettingDialog();

	virtual void ShowSettingDialog(QWidget *pParent);

	bool Import();

	/*!
		this function called by tcImportProgressDialog when user press the "Abort" button.
	*/
	void CancelImport();

	bool IsImporting() { return mIsImporting; }

protected:
	virtual bool ImportProcess();

	virtual void CancelImportProcess();

protected:
	bool mIsImporting;

signals:
	void OnUpdateProgress(int pProgress);

	void OnAppendMessage(const QString &pMessage, bool pSuccess);

	void OnImportFinished();

};

#endif //tcimptsource_h
