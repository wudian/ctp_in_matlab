/********************************************************************************
** Form generated from reading UI file 'ui_aboutdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_ABOUTDLG_H
#define UI_UI_ABOUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcAboutDialog
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tab1;
    QWidget *tab;
    QVBoxLayout *vboxLayout1;
    QTextBrowser *txt1_1;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout2;
    QTextBrowser *txt1_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcAboutDialog)
    {
        if (tcAboutDialog->objectName().isEmpty())
            tcAboutDialog->setObjectName(QStringLiteral("tcAboutDialog"));
        tcAboutDialog->resize(510, 306);
        vboxLayout = new QVBoxLayout(tcAboutDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        tab1 = new QTabWidget(tcAboutDialog);
        tab1->setObjectName(QStringLiteral("tab1"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        vboxLayout1 = new QVBoxLayout(tab);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        txt1_1 = new QTextBrowser(tab);
        txt1_1->setObjectName(QStringLiteral("txt1_1"));

        vboxLayout1->addWidget(txt1_1);

        tab1->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        vboxLayout2 = new QVBoxLayout(tab_2);
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout2->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        txt1_2 = new QTextBrowser(tab_2);
        txt1_2->setObjectName(QStringLiteral("txt1_2"));

        vboxLayout2->addWidget(txt1_2);

        tab1->addTab(tab_2, QString());

        vboxLayout->addWidget(tab1);

        buttonBox = new QDialogButtonBox(tcAboutDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcAboutDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcAboutDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcAboutDialog, SLOT(reject()));

        tab1->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(tcAboutDialog);
    } // setupUi

    void retranslateUi(QDialog *tcAboutDialog)
    {
        tcAboutDialog->setWindowTitle(QApplication::translate("tcAboutDialog", "About...", 0));
        tab1->setTabText(tab1->indexOf(tab), QApplication::translate("tcAboutDialog", "About", 0));
        tab1->setTabText(tab1->indexOf(tab_2), QApplication::translate("tcAboutDialog", "Release Notes", 0));
    } // retranslateUi

};

namespace Ui {
    class tcAboutDialog: public Ui_tcAboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_ABOUTDLG_H
