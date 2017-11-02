#include "tcaboutdlg.h"

#include "tcdefine.h"

tcAboutDialog::tcAboutDialog(QWidget *pParent)
	: QDialog(pParent)
{
	setupUi(this);
	SetAboutText();
}

void tcAboutDialog::SetAboutText()
{
	QStringList slist;
	slist += "<b><font size=\"70\">" + QString(SYSTEM_NAME) + "</font></b>";
	slist += "";
	slist += QString(SYSTEM_NAME) + " Version: " + QString(SYSTEM_VERSION);
#ifdef WIN32
	slist += "Platform: WIN32";
#else
	slist += "Platform: LINUX";
#endif
	slist += "QT Version: " + QString(QT_VERSION_STR);
	slist += "Author: tony (<font color=blue>tonixinot@gmail.com</font>)";
	slist += "";

	txt1_1->setHtml(slist.join("<br>"));
}


