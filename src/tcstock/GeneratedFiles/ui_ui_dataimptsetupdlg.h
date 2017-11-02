/********************************************************************************
** Form generated from reading UI file 'ui_dataimptsetupdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_DATAIMPTSETUPDLG_H
#define UI_UI_DATAIMPTSETUPDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcDataImporterSetupDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QGroupBox *gbx1;
    QVBoxLayout *vboxLayout1;
    QTableWidget *tbl1_1;
    QHBoxLayout *hboxLayout1;
    QPushButton *btn1_1;
    QPushButton *btn1_2;
    QSpacerItem *spacerItem;
    QGroupBox *gbx2;
    QVBoxLayout *vboxLayout2;
    QRadioButton *rdo2_1;
    QRadioButton *rdo2_2;
    QHBoxLayout *hboxLayout2;
    QLabel *lbl2_1;
    QLabel *lbl2_2;
    QLineEdit *edt2_1;
    QSpacerItem *spacerItem1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcDataImporterSetupDialog)
    {
        if (tcDataImporterSetupDialog->objectName().isEmpty())
            tcDataImporterSetupDialog->setObjectName(QStringLiteral("tcDataImporterSetupDialog"));
        tcDataImporterSetupDialog->resize(574, 326);
        vboxLayout = new QVBoxLayout(tcDataImporterSetupDialog);
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
        gbx1 = new QGroupBox(tcDataImporterSetupDialog);
        gbx1->setObjectName(QStringLiteral("gbx1"));
        vboxLayout1 = new QVBoxLayout(gbx1);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        tbl1_1 = new QTableWidget(gbx1);
        tbl1_1->setObjectName(QStringLiteral("tbl1_1"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(7));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tbl1_1->sizePolicy().hasHeightForWidth());
        tbl1_1->setSizePolicy(sizePolicy);

        vboxLayout1->addWidget(tbl1_1);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        btn1_1 = new QPushButton(gbx1);
        btn1_1->setObjectName(QStringLiteral("btn1_1"));

        hboxLayout1->addWidget(btn1_1);

        btn1_2 = new QPushButton(gbx1);
        btn1_2->setObjectName(QStringLiteral("btn1_2"));

        hboxLayout1->addWidget(btn1_2);

        spacerItem = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);


        vboxLayout1->addLayout(hboxLayout1);


        hboxLayout->addWidget(gbx1);

        gbx2 = new QGroupBox(tcDataImporterSetupDialog);
        gbx2->setObjectName(QStringLiteral("gbx2"));
        vboxLayout2 = new QVBoxLayout(gbx2);
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout2->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        rdo2_1 = new QRadioButton(gbx2);
        rdo2_1->setObjectName(QStringLiteral("rdo2_1"));
        rdo2_1->setChecked(true);

        vboxLayout2->addWidget(rdo2_1);

        rdo2_2 = new QRadioButton(gbx2);
        rdo2_2->setObjectName(QStringLiteral("rdo2_2"));

        vboxLayout2->addWidget(rdo2_2);

        hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout2->setSpacing(6);
#endif
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        lbl2_1 = new QLabel(gbx2);
        lbl2_1->setObjectName(QStringLiteral("lbl2_1"));

        hboxLayout2->addWidget(lbl2_1);

        lbl2_2 = new QLabel(gbx2);
        lbl2_2->setObjectName(QStringLiteral("lbl2_2"));

        hboxLayout2->addWidget(lbl2_2);

        edt2_1 = new QLineEdit(gbx2);
        edt2_1->setObjectName(QStringLiteral("edt2_1"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(0));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(edt2_1->sizePolicy().hasHeightForWidth());
        edt2_1->setSizePolicy(sizePolicy1);

        hboxLayout2->addWidget(edt2_1);


        vboxLayout2->addLayout(hboxLayout2);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout2->addItem(spacerItem1);


        hboxLayout->addWidget(gbx2);


        vboxLayout->addLayout(hboxLayout);

        buttonBox = new QDialogButtonBox(tcDataImporterSetupDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcDataImporterSetupDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcDataImporterSetupDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcDataImporterSetupDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcDataImporterSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *tcDataImporterSetupDialog)
    {
        tcDataImporterSetupDialog->setWindowTitle(QApplication::translate("tcDataImporterSetupDialog", "Data Import Setup...", 0));
        gbx1->setTitle(QApplication::translate("tcDataImporterSetupDialog", "Source List:", 0));
        btn1_1->setText(QApplication::translate("tcDataImporterSetupDialog", "Setting...", 0));
        btn1_2->setText(QApplication::translate("tcDataImporterSetupDialog", "Import Now", 0));
        gbx2->setTitle(QApplication::translate("tcDataImporterSetupDialog", "Setup:", 0));
        rdo2_1->setText(QApplication::translate("tcDataImporterSetupDialog", "Do not Auto Import", 0));
        rdo2_2->setText(QApplication::translate("tcDataImporterSetupDialog", "Auto Import", 0));
        lbl2_1->setText(QString());
        lbl2_2->setText(QApplication::translate("tcDataImporterSetupDialog", "Interval (minutes):", 0));
    } // retranslateUi

};

namespace Ui {
    class tcDataImporterSetupDialog: public Ui_tcDataImporterSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_DATAIMPTSETUPDLG_H
