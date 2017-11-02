/********************************************************************************
** Form generated from reading UI file 'ui_yahoowebimptsourcedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_YAHOOWEBIMPTSOURCEDLG_H
#define UI_UI_YAHOOWEBIMPTSOURCEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcYahooWebImportSourceDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *grp1;
    QVBoxLayout *vboxLayout1;
    QTableWidget *tbl1;
    QLabel *lbl1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcYahooWebImportSourceDialog)
    {
        if (tcYahooWebImportSourceDialog->objectName().isEmpty())
            tcYahooWebImportSourceDialog->setObjectName(QStringLiteral("tcYahooWebImportSourceDialog"));
        tcYahooWebImportSourceDialog->resize(493, 254);
        vboxLayout = new QVBoxLayout(tcYahooWebImportSourceDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        grp1 = new QGroupBox(tcYahooWebImportSourceDialog);
        grp1->setObjectName(QStringLiteral("grp1"));
        vboxLayout1 = new QVBoxLayout(grp1);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        tbl1 = new QTableWidget(grp1);
        tbl1->setObjectName(QStringLiteral("tbl1"));

        vboxLayout1->addWidget(tbl1);

        lbl1 = new QLabel(grp1);
        lbl1->setObjectName(QStringLiteral("lbl1"));

        vboxLayout1->addWidget(lbl1);


        vboxLayout->addWidget(grp1);

        buttonBox = new QDialogButtonBox(tcYahooWebImportSourceDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcYahooWebImportSourceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcYahooWebImportSourceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcYahooWebImportSourceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcYahooWebImportSourceDialog);
    } // setupUi

    void retranslateUi(QDialog *tcYahooWebImportSourceDialog)
    {
        tcYahooWebImportSourceDialog->setWindowTitle(QApplication::translate("tcYahooWebImportSourceDialog", "Yahoo Web Import Source Setting...", 0));
        grp1->setTitle(QApplication::translate("tcYahooWebImportSourceDialog", "Setting:", 0));
        lbl1->setText(QApplication::translate("tcYahooWebImportSourceDialog", "Thanks http://cn.biz.yahoo.com for it's stock data.", 0));
    } // retranslateUi

};

namespace Ui {
    class tcYahooWebImportSourceDialog: public Ui_tcYahooWebImportSourceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_YAHOOWEBIMPTSOURCEDLG_H
