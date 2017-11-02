/********************************************************************************
** Form generated from reading UI file 'ui_toolpadwgt.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_TOOLPADWGT_H
#define UI_UI_TOOLPADWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcToolPadWidget
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tab1;
    QWidget *tab;
    QVBoxLayout *vboxLayout1;
    QPushButton *pushButton;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout2;
    QPushButton *pushButton_2;
    QWidget *tab_3;
    QVBoxLayout *vboxLayout3;
    QPushButton *pushButton_3;

    void setupUi(QWidget *tcToolPadWidget)
    {
        if (tcToolPadWidget->objectName().isEmpty())
            tcToolPadWidget->setObjectName(QStringLiteral("tcToolPadWidget"));
        tcToolPadWidget->resize(283, 300);
        vboxLayout = new QVBoxLayout(tcToolPadWidget);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        tab1 = new QTabWidget(tcToolPadWidget);
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
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        vboxLayout1->addWidget(pushButton);

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
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        vboxLayout2->addWidget(pushButton_2);

        tab1->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        vboxLayout3 = new QVBoxLayout(tab_3);
#ifndef Q_OS_MAC
        vboxLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout3->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout3->setObjectName(QStringLiteral("vboxLayout3"));
        pushButton_3 = new QPushButton(tab_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        vboxLayout3->addWidget(pushButton_3);

        tab1->addTab(tab_3, QString());

        vboxLayout->addWidget(tab1);


        retranslateUi(tcToolPadWidget);

        tab1->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(tcToolPadWidget);
    } // setupUi

    void retranslateUi(QWidget *tcToolPadWidget)
    {
        tcToolPadWidget->setWindowTitle(QApplication::translate("tcToolPadWidget", "Tools", 0));
        pushButton->setText(QApplication::translate("tcToolPadWidget", "PushButton", 0));
        tab1->setTabText(tab1->indexOf(tab), QApplication::translate("tcToolPadWidget", "Stock List", 0));
        pushButton_2->setText(QApplication::translate("tcToolPadWidget", "PushButton", 0));
        tab1->setTabText(tab1->indexOf(tab_2), QApplication::translate("tcToolPadWidget", "Function1", 0));
        pushButton_3->setText(QApplication::translate("tcToolPadWidget", "PushButton", 0));
        tab1->setTabText(tab1->indexOf(tab_3), QApplication::translate("tcToolPadWidget", "Function2", 0));
    } // retranslateUi

};

namespace Ui {
    class tcToolPadWidget: public Ui_tcToolPadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_TOOLPADWGT_H
