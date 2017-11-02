/********************************************************************************
** Form generated from reading UI file 'ui_stockinfodlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_STOCKINFODLG_H
#define UI_UI_STOCKINFODLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcStockInfoDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *gbx1;
    QGridLayout *gridLayout;
    QLineEdit *edt1;
    QLineEdit *edt2;
    QLineEdit *edt3;
    QLabel *lbl1;
    QLabel *lbl2;
    QLabel *lbl3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcStockInfoDialog)
    {
        if (tcStockInfoDialog->objectName().isEmpty())
            tcStockInfoDialog->setObjectName(QStringLiteral("tcStockInfoDialog"));
        tcStockInfoDialog->resize(400, 155);
        vboxLayout = new QVBoxLayout(tcStockInfoDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        gbx1 = new QGroupBox(tcStockInfoDialog);
        gbx1->setObjectName(QStringLiteral("gbx1"));
        gridLayout = new QGridLayout(gbx1);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        edt1 = new QLineEdit(gbx1);
        edt1->setObjectName(QStringLiteral("edt1"));

        gridLayout->addWidget(edt1, 0, 1, 1, 1);

        edt2 = new QLineEdit(gbx1);
        edt2->setObjectName(QStringLiteral("edt2"));

        gridLayout->addWidget(edt2, 1, 1, 1, 1);

        edt3 = new QLineEdit(gbx1);
        edt3->setObjectName(QStringLiteral("edt3"));

        gridLayout->addWidget(edt3, 2, 1, 1, 1);

        lbl1 = new QLabel(gbx1);
        lbl1->setObjectName(QStringLiteral("lbl1"));

        gridLayout->addWidget(lbl1, 0, 0, 1, 1);

        lbl2 = new QLabel(gbx1);
        lbl2->setObjectName(QStringLiteral("lbl2"));

        gridLayout->addWidget(lbl2, 1, 0, 1, 1);

        lbl3 = new QLabel(gbx1);
        lbl3->setObjectName(QStringLiteral("lbl3"));

        gridLayout->addWidget(lbl3, 2, 0, 1, 1);


        vboxLayout->addWidget(gbx1);

        buttonBox = new QDialogButtonBox(tcStockInfoDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcStockInfoDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcStockInfoDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcStockInfoDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcStockInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *tcStockInfoDialog)
    {
        tcStockInfoDialog->setWindowTitle(QApplication::translate("tcStockInfoDialog", "Stock Info...", 0));
        gbx1->setTitle(QApplication::translate("tcStockInfoDialog", "Info:", 0));
        lbl1->setText(QApplication::translate("tcStockInfoDialog", "Stock Code:", 0));
        lbl2->setText(QApplication::translate("tcStockInfoDialog", "Name:", 0));
        lbl3->setText(QApplication::translate("tcStockInfoDialog", "Description:", 0));
    } // retranslateUi

};

namespace Ui {
    class tcStockInfoDialog: public Ui_tcStockInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_STOCKINFODLG_H
