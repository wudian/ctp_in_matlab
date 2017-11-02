/********************************************************************************
** Form generated from reading UI file 'ui_marketselectdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_MARKETSELECTDLG_H
#define UI_UI_MARKETSELECTDLG_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcMarketSelectDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *gbx1;
    QHBoxLayout *hboxLayout;
    QLabel *lbl1;
    QComboBox *cbo1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcMarketSelectDialog)
    {
        if (tcMarketSelectDialog->objectName().isEmpty())
            tcMarketSelectDialog->setObjectName(QStringLiteral("tcMarketSelectDialog"));
        tcMarketSelectDialog->resize(292, 101);
        vboxLayout = new QVBoxLayout(tcMarketSelectDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        gbx1 = new QGroupBox(tcMarketSelectDialog);
        gbx1->setObjectName(QStringLiteral("gbx1"));
        hboxLayout = new QHBoxLayout(gbx1);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        lbl1 = new QLabel(gbx1);
        lbl1->setObjectName(QStringLiteral("lbl1"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(4), static_cast<QSizePolicy::Policy>(5));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbl1->sizePolicy().hasHeightForWidth());
        lbl1->setSizePolicy(sizePolicy);

        hboxLayout->addWidget(lbl1);

        cbo1 = new QComboBox(gbx1);
        cbo1->setObjectName(QStringLiteral("cbo1"));

        hboxLayout->addWidget(cbo1);


        vboxLayout->addWidget(gbx1);

        buttonBox = new QDialogButtonBox(tcMarketSelectDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcMarketSelectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcMarketSelectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcMarketSelectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcMarketSelectDialog);
    } // setupUi

    void retranslateUi(QDialog *tcMarketSelectDialog)
    {
        tcMarketSelectDialog->setWindowTitle(QApplication::translate("tcMarketSelectDialog", "Select Market...", 0));
        gbx1->setTitle(QApplication::translate("tcMarketSelectDialog", "Info:", 0));
        lbl1->setText(QApplication::translate("tcMarketSelectDialog", "Market:", 0));
    } // retranslateUi

};

namespace Ui {
    class tcMarketSelectDialog: public Ui_tcMarketSelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_MARKETSELECTDLG_H
