/********************************************************************************
** Form generated from reading UI file 'ui_fxjfileimptsourcedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_FXJFILEIMPTSOURCEDLG_H
#define UI_UI_FXJFILEIMPTSOURCEDLG_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcFxjFileImportSourceDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *gbx1;
    QVBoxLayout *vboxLayout1;
    QRadioButton *rdo1;
    QHBoxLayout *hboxLayout;
    QLabel *lbl1;
    QLabel *lbl2;
    QLineEdit *edt1;
    QRadioButton *rdo2;
    QHBoxLayout *hboxLayout1;
    QLabel *lbl3;
    QLabel *lbl4;
    QLineEdit *edt2;
    QToolButton *btn1;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcFxjFileImportSourceDialog)
    {
        if (tcFxjFileImportSourceDialog->objectName().isEmpty())
            tcFxjFileImportSourceDialog->setObjectName(QStringLiteral("tcFxjFileImportSourceDialog"));
        tcFxjFileImportSourceDialog->resize(473, 217);
        vboxLayout = new QVBoxLayout(tcFxjFileImportSourceDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        gbx1 = new QGroupBox(tcFxjFileImportSourceDialog);
        gbx1->setObjectName(QStringLiteral("gbx1"));
        vboxLayout1 = new QVBoxLayout(gbx1);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        rdo1 = new QRadioButton(gbx1);
        rdo1->setObjectName(QStringLiteral("rdo1"));
        rdo1->setChecked(true);

        vboxLayout1->addWidget(rdo1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        lbl1 = new QLabel(gbx1);
        lbl1->setObjectName(QStringLiteral("lbl1"));

        hboxLayout->addWidget(lbl1);

        lbl2 = new QLabel(gbx1);
        lbl2->setObjectName(QStringLiteral("lbl2"));

        hboxLayout->addWidget(lbl2);

        edt1 = new QLineEdit(gbx1);
        edt1->setObjectName(QStringLiteral("edt1"));

        hboxLayout->addWidget(edt1);


        vboxLayout1->addLayout(hboxLayout);

        rdo2 = new QRadioButton(gbx1);
        rdo2->setObjectName(QStringLiteral("rdo2"));

        vboxLayout1->addWidget(rdo2);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        lbl3 = new QLabel(gbx1);
        lbl3->setObjectName(QStringLiteral("lbl3"));

        hboxLayout1->addWidget(lbl3);

        lbl4 = new QLabel(gbx1);
        lbl4->setObjectName(QStringLiteral("lbl4"));

        hboxLayout1->addWidget(lbl4);

        edt2 = new QLineEdit(gbx1);
        edt2->setObjectName(QStringLiteral("edt2"));

        hboxLayout1->addWidget(edt2);

        btn1 = new QToolButton(gbx1);
        btn1->setObjectName(QStringLiteral("btn1"));

        hboxLayout1->addWidget(btn1);


        vboxLayout1->addLayout(hboxLayout1);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem);


        vboxLayout->addWidget(gbx1);

        buttonBox = new QDialogButtonBox(tcFxjFileImportSourceDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcFxjFileImportSourceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcFxjFileImportSourceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcFxjFileImportSourceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcFxjFileImportSourceDialog);
    } // setupUi

    void retranslateUi(QDialog *tcFxjFileImportSourceDialog)
    {
        tcFxjFileImportSourceDialog->setWindowTitle(QApplication::translate("tcFxjFileImportSourceDialog", "Fxj File Import Source Setting...", 0));
        gbx1->setTitle(QApplication::translate("tcFxjFileImportSourceDialog", "Setup:", 0));
        rdo1->setText(QApplication::translate("tcFxjFileImportSourceDialog", "Auto download daily file (ZIP format) from http://www.fxj.net.cn", 0));
        lbl1->setText(QString());
        lbl2->setText(QApplication::translate("tcFxjFileImportSourceDialog", "URL:", 0));
        rdo2->setText(QApplication::translate("tcFxjFileImportSourceDialog", "Use the daily files (ZIP or DAD format) on local system", 0));
        lbl3->setText(QString());
        lbl4->setText(QApplication::translate("tcFxjFileImportSourceDialog", "Path:", 0));
        btn1->setText(QApplication::translate("tcFxjFileImportSourceDialog", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class tcFxjFileImportSourceDialog: public Ui_tcFxjFileImportSourceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_FXJFILEIMPTSOURCEDLG_H
