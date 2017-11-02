/********************************************************************************
** Form generated from reading UI file 'ui_marketlistdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_MARKETLISTDLG_H
#define UI_UI_MARKETLISTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcMarketListDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *gbx1;
    QHBoxLayout *hboxLayout;
    QLabel *lbl1_1;
    QComboBox *cbo1_1;
    QPushButton *btn1_1;
    QPushButton *btn1_2;
    QPushButton *btn1_3;
    QSpacerItem *spacerItem;
    QTableWidget *tbl1;
    QHBoxLayout *hboxLayout1;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QSpacerItem *spacerItem1;
    QPushButton *btn4;
    QPushButton *btn5;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcMarketListDialog)
    {
        if (tcMarketListDialog->objectName().isEmpty())
            tcMarketListDialog->setObjectName(QStringLiteral("tcMarketListDialog"));
        tcMarketListDialog->resize(643, 439);
        vboxLayout = new QVBoxLayout(tcMarketListDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        gbx1 = new QGroupBox(tcMarketListDialog);
        gbx1->setObjectName(QStringLiteral("gbx1"));
        hboxLayout = new QHBoxLayout(gbx1);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        lbl1_1 = new QLabel(gbx1);
        lbl1_1->setObjectName(QStringLiteral("lbl1_1"));

        hboxLayout->addWidget(lbl1_1);

        cbo1_1 = new QComboBox(gbx1);
        cbo1_1->setObjectName(QStringLiteral("cbo1_1"));

        hboxLayout->addWidget(cbo1_1);

        btn1_1 = new QPushButton(gbx1);
        btn1_1->setObjectName(QStringLiteral("btn1_1"));

        hboxLayout->addWidget(btn1_1);

        btn1_2 = new QPushButton(gbx1);
        btn1_2->setObjectName(QStringLiteral("btn1_2"));

        hboxLayout->addWidget(btn1_2);

        btn1_3 = new QPushButton(gbx1);
        btn1_3->setObjectName(QStringLiteral("btn1_3"));

        hboxLayout->addWidget(btn1_3);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addWidget(gbx1);

        tbl1 = new QTableWidget(tcMarketListDialog);
        tbl1->setObjectName(QStringLiteral("tbl1"));

        vboxLayout->addWidget(tbl1);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        btn1 = new QPushButton(tcMarketListDialog);
        btn1->setObjectName(QStringLiteral("btn1"));

        hboxLayout1->addWidget(btn1);

        btn2 = new QPushButton(tcMarketListDialog);
        btn2->setObjectName(QStringLiteral("btn2"));

        hboxLayout1->addWidget(btn2);

        btn3 = new QPushButton(tcMarketListDialog);
        btn3->setObjectName(QStringLiteral("btn3"));

        hboxLayout1->addWidget(btn3);

        spacerItem1 = new QSpacerItem(41, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem1);

        btn4 = new QPushButton(tcMarketListDialog);
        btn4->setObjectName(QStringLiteral("btn4"));

        hboxLayout1->addWidget(btn4);

        btn5 = new QPushButton(tcMarketListDialog);
        btn5->setObjectName(QStringLiteral("btn5"));

        hboxLayout1->addWidget(btn5);


        vboxLayout->addLayout(hboxLayout1);

        buttonBox = new QDialogButtonBox(tcMarketListDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcMarketListDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcMarketListDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcMarketListDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcMarketListDialog);
    } // setupUi

    void retranslateUi(QDialog *tcMarketListDialog)
    {
        tcMarketListDialog->setWindowTitle(QApplication::translate("tcMarketListDialog", "Market List...", 0));
        gbx1->setTitle(QApplication::translate("tcMarketListDialog", "Markets:", 0));
        lbl1_1->setText(QApplication::translate("tcMarketListDialog", "Market:", 0));
        btn1_1->setText(QApplication::translate("tcMarketListDialog", "Add Market", 0));
        btn1_2->setText(QApplication::translate("tcMarketListDialog", "Modify Market", 0));
        btn1_3->setText(QApplication::translate("tcMarketListDialog", "Remove Market", 0));
        btn1->setText(QApplication::translate("tcMarketListDialog", "Add Stock", 0));
        btn2->setText(QApplication::translate("tcMarketListDialog", "Modify Stock", 0));
        btn3->setText(QApplication::translate("tcMarketListDialog", "Remove Stock", 0));
        btn4->setText(QApplication::translate("tcMarketListDialog", "Import From CVS File", 0));
        btn5->setText(QApplication::translate("tcMarketListDialog", "Export To CSV File", 0));
    } // retranslateUi

};

namespace Ui {
    class tcMarketListDialog: public Ui_tcMarketListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_MARKETLISTDLG_H
