/********************************************************************************
** Form generated from reading UI file 'ui_stockdatainfodlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_STOCKDATAINFODLG_H
#define UI_UI_STOCKDATAINFODLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcStockDataInfoDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QGroupBox *gbx1;
    QHBoxLayout *hboxLayout1;
    QDateEdit *cld1;
    QGroupBox *gbx2;
    QHBoxLayout *hboxLayout2;
    QLabel *lbl1;
    QComboBox *cbo1;
    QLabel *lbl2;
    QLineEdit *edt1;
    QLabel *lbl3;
    QLineEdit *edt2;
    QSpacerItem *spacerItem;
    QTableView *tbl1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcStockDataInfoDialog)
    {
        if (tcStockDataInfoDialog->objectName().isEmpty())
            tcStockDataInfoDialog->setObjectName(QStringLiteral("tcStockDataInfoDialog"));
        tcStockDataInfoDialog->resize(872, 536);
        vboxLayout = new QVBoxLayout(tcStockDataInfoDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        gbx1 = new QGroupBox(tcStockDataInfoDialog);
        gbx1->setObjectName(QStringLiteral("gbx1"));
        hboxLayout1 = new QHBoxLayout(gbx1);
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        cld1 = new QDateEdit(gbx1);
        cld1->setObjectName(QStringLiteral("cld1"));
        cld1->setCalendarPopup(true);

        hboxLayout1->addWidget(cld1);


        hboxLayout->addWidget(gbx1);

        gbx2 = new QGroupBox(tcStockDataInfoDialog);
        gbx2->setObjectName(QStringLiteral("gbx2"));
        hboxLayout2 = new QHBoxLayout(gbx2);
#ifndef Q_OS_MAC
        hboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout2->setContentsMargins(9, 9, 9, 9);
#endif
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        lbl1 = new QLabel(gbx2);
        lbl1->setObjectName(QStringLiteral("lbl1"));

        hboxLayout2->addWidget(lbl1);

        cbo1 = new QComboBox(gbx2);
        cbo1->setObjectName(QStringLiteral("cbo1"));

        hboxLayout2->addWidget(cbo1);

        lbl2 = new QLabel(gbx2);
        lbl2->setObjectName(QStringLiteral("lbl2"));

        hboxLayout2->addWidget(lbl2);

        edt1 = new QLineEdit(gbx2);
        edt1->setObjectName(QStringLiteral("edt1"));

        hboxLayout2->addWidget(edt1);

        lbl3 = new QLabel(gbx2);
        lbl3->setObjectName(QStringLiteral("lbl3"));

        hboxLayout2->addWidget(lbl3);

        edt2 = new QLineEdit(gbx2);
        edt2->setObjectName(QStringLiteral("edt2"));

        hboxLayout2->addWidget(edt2);


        hboxLayout->addWidget(gbx2);

        spacerItem = new QSpacerItem(281, 56, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

        tbl1 = new QTableView(tcStockDataInfoDialog);
        tbl1->setObjectName(QStringLiteral("tbl1"));

        vboxLayout->addWidget(tbl1);

        buttonBox = new QDialogButtonBox(tcStockDataInfoDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcStockDataInfoDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcStockDataInfoDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcStockDataInfoDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcStockDataInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *tcStockDataInfoDialog)
    {
        tcStockDataInfoDialog->setWindowTitle(QApplication::translate("tcStockDataInfoDialog", "Stock Data...", 0));
        gbx1->setTitle(QApplication::translate("tcStockDataInfoDialog", "Date:", 0));
        gbx2->setTitle(QApplication::translate("tcStockDataInfoDialog", "Filter:", 0));
        lbl1->setText(QApplication::translate("tcStockDataInfoDialog", "Group:", 0));
        lbl2->setText(QApplication::translate("tcStockDataInfoDialog", "Stock Code:", 0));
        lbl3->setText(QApplication::translate("tcStockDataInfoDialog", "Name:", 0));
    } // retranslateUi

};

namespace Ui {
    class tcStockDataInfoDialog: public Ui_tcStockDataInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_STOCKDATAINFODLG_H
