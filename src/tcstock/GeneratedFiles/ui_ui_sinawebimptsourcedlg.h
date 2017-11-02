/********************************************************************************
** Form generated from reading UI file 'ui_sinawebimptsourcedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_SINAWEBIMPTSOURCEDLG_H
#define UI_UI_SINAWEBIMPTSOURCEDLG_H

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

class Ui_tcSinaWebImportSourceDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *grp1;
    QVBoxLayout *vboxLayout1;
    QTableWidget *tbl1;
    QLabel *lbl1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcSinaWebImportSourceDialog)
    {
        if (tcSinaWebImportSourceDialog->objectName().isEmpty())
            tcSinaWebImportSourceDialog->setObjectName(QStringLiteral("tcSinaWebImportSourceDialog"));
        tcSinaWebImportSourceDialog->resize(493, 254);
        vboxLayout = new QVBoxLayout(tcSinaWebImportSourceDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        grp1 = new QGroupBox(tcSinaWebImportSourceDialog);
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

        buttonBox = new QDialogButtonBox(tcSinaWebImportSourceDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcSinaWebImportSourceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcSinaWebImportSourceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcSinaWebImportSourceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcSinaWebImportSourceDialog);
    } // setupUi

    void retranslateUi(QDialog *tcSinaWebImportSourceDialog)
    {
        tcSinaWebImportSourceDialog->setWindowTitle(QApplication::translate("tcSinaWebImportSourceDialog", "Sina Web Import Source Setting...", 0));
        grp1->setTitle(QApplication::translate("tcSinaWebImportSourceDialog", "Setting:", 0));
        lbl1->setText(QApplication::translate("tcSinaWebImportSourceDialog", "Thanks http://stock.sina.com.cn for it's stock data.", 0));
    } // retranslateUi

};

namespace Ui {
    class tcSinaWebImportSourceDialog: public Ui_tcSinaWebImportSourceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_SINAWEBIMPTSOURCEDLG_H
