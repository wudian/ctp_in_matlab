/********************************************************************************
** Form generated from reading UI file 'ui_stockselectdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_STOCKSELECTDLG_H
#define UI_UI_STOCKSELECTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcStockSelectDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QGroupBox *grp1;
    QVBoxLayout *vboxLayout1;
    QComboBox *cbo1;
    QGroupBox *grp2;
    QHBoxLayout *hboxLayout1;
    QLabel *lbl1;
    QLineEdit *edt1;
    QLabel *lbl2;
    QLineEdit *edt2;
    QSpacerItem *spacerItem;
    QTableWidget *tbl1;
    QCheckBox *chk1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcStockSelectDialog)
    {
        if (tcStockSelectDialog->objectName().isEmpty())
            tcStockSelectDialog->setObjectName(QStringLiteral("tcStockSelectDialog"));
        tcStockSelectDialog->resize(664, 437);
        vboxLayout = new QVBoxLayout(tcStockSelectDialog);
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
        grp1 = new QGroupBox(tcStockSelectDialog);
        grp1->setObjectName(QStringLiteral("grp1"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(5));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(grp1->sizePolicy().hasHeightForWidth());
        grp1->setSizePolicy(sizePolicy);
        vboxLayout1 = new QVBoxLayout(grp1);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        cbo1 = new QComboBox(grp1);
        cbo1->setObjectName(QStringLiteral("cbo1"));

        vboxLayout1->addWidget(cbo1);


        hboxLayout->addWidget(grp1);

        grp2 = new QGroupBox(tcStockSelectDialog);
        grp2->setObjectName(QStringLiteral("grp2"));
        hboxLayout1 = new QHBoxLayout(grp2);
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        lbl1 = new QLabel(grp2);
        lbl1->setObjectName(QStringLiteral("lbl1"));

        hboxLayout1->addWidget(lbl1);

        edt1 = new QLineEdit(grp2);
        edt1->setObjectName(QStringLiteral("edt1"));

        hboxLayout1->addWidget(edt1);

        lbl2 = new QLabel(grp2);
        lbl2->setObjectName(QStringLiteral("lbl2"));

        hboxLayout1->addWidget(lbl2);

        edt2 = new QLineEdit(grp2);
        edt2->setObjectName(QStringLiteral("edt2"));

        hboxLayout1->addWidget(edt2);


        hboxLayout->addWidget(grp2);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

        tbl1 = new QTableWidget(tcStockSelectDialog);
        tbl1->setObjectName(QStringLiteral("tbl1"));

        vboxLayout->addWidget(tbl1);

        chk1 = new QCheckBox(tcStockSelectDialog);
        chk1->setObjectName(QStringLiteral("chk1"));

        vboxLayout->addWidget(chk1);

        buttonBox = new QDialogButtonBox(tcStockSelectDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcStockSelectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcStockSelectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcStockSelectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcStockSelectDialog);
    } // setupUi

    void retranslateUi(QDialog *tcStockSelectDialog)
    {
        tcStockSelectDialog->setWindowTitle(QApplication::translate("tcStockSelectDialog", "Select Stock...", 0));
        grp1->setTitle(QApplication::translate("tcStockSelectDialog", "Market:", 0));
        grp2->setTitle(QApplication::translate("tcStockSelectDialog", "Filter:", 0));
        lbl1->setText(QApplication::translate("tcStockSelectDialog", "Stock Code:", 0));
        lbl2->setText(QApplication::translate("tcStockSelectDialog", "Name:", 0));
        chk1->setText(QApplication::translate("tcStockSelectDialog", "Select All Stocks", 0));
    } // retranslateUi

};

namespace Ui {
    class tcStockSelectDialog: public Ui_tcStockSelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_STOCKSELECTDLG_H
