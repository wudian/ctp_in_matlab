/********************************************************************************
** Form generated from reading UI file 'ui_imptprogressdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_IMPTPROGRESSDLG_H
#define UI_UI_IMPTPROGRESSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcImportProgressDialog
{
public:
    QVBoxLayout *vboxLayout;
    QProgressBar *pgs1;
    QTextEdit *edt1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcImportProgressDialog)
    {
        if (tcImportProgressDialog->objectName().isEmpty())
            tcImportProgressDialog->setObjectName(QStringLiteral("tcImportProgressDialog"));
        tcImportProgressDialog->resize(599, 343);
        vboxLayout = new QVBoxLayout(tcImportProgressDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        pgs1 = new QProgressBar(tcImportProgressDialog);
        pgs1->setObjectName(QStringLiteral("pgs1"));
        pgs1->setValue(0);
        pgs1->setOrientation(Qt::Horizontal);

        vboxLayout->addWidget(pgs1);

        edt1 = new QTextEdit(tcImportProgressDialog);
        edt1->setObjectName(QStringLiteral("edt1"));
        edt1->setReadOnly(true);

        vboxLayout->addWidget(edt1);

        buttonBox = new QDialogButtonBox(tcImportProgressDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Abort|QDialogButtonBox::Close|QDialogButtonBox::NoButton);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcImportProgressDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcImportProgressDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcImportProgressDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcImportProgressDialog);
    } // setupUi

    void retranslateUi(QDialog *tcImportProgressDialog)
    {
        tcImportProgressDialog->setWindowTitle(QApplication::translate("tcImportProgressDialog", "Import Progress...", 0));
    } // retranslateUi

};

namespace Ui {
    class tcImportProgressDialog: public Ui_tcImportProgressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_IMPTPROGRESSDLG_H
