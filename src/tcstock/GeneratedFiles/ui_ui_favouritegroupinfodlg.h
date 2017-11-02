/********************************************************************************
** Form generated from reading UI file 'ui_favouritegroupinfodlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_FAVOURITEGROUPINFODLG_H
#define UI_UI_FAVOURITEGROUPINFODLG_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcFavouriteGroupInfoDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *grp1;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout1;
    QLabel *lbl1;
    QLabel *lbl2;
    QVBoxLayout *vboxLayout2;
    QLineEdit *edt1;
    QLineEdit *edt2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcFavouriteGroupInfoDialog)
    {
        if (tcFavouriteGroupInfoDialog->objectName().isEmpty())
            tcFavouriteGroupInfoDialog->setObjectName(QStringLiteral("tcFavouriteGroupInfoDialog"));
        tcFavouriteGroupInfoDialog->resize(336, 130);
        vboxLayout = new QVBoxLayout(tcFavouriteGroupInfoDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        grp1 = new QGroupBox(tcFavouriteGroupInfoDialog);
        grp1->setObjectName(QStringLiteral("grp1"));
        hboxLayout = new QHBoxLayout(grp1);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        vboxLayout1 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
#endif
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        lbl1 = new QLabel(grp1);
        lbl1->setObjectName(QStringLiteral("lbl1"));

        vboxLayout1->addWidget(lbl1);

        lbl2 = new QLabel(grp1);
        lbl2->setObjectName(QStringLiteral("lbl2"));

        vboxLayout1->addWidget(lbl2);


        hboxLayout->addLayout(vboxLayout1);

        vboxLayout2 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        edt1 = new QLineEdit(grp1);
        edt1->setObjectName(QStringLiteral("edt1"));

        vboxLayout2->addWidget(edt1);

        edt2 = new QLineEdit(grp1);
        edt2->setObjectName(QStringLiteral("edt2"));

        vboxLayout2->addWidget(edt2);


        hboxLayout->addLayout(vboxLayout2);


        vboxLayout->addWidget(grp1);

        buttonBox = new QDialogButtonBox(tcFavouriteGroupInfoDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcFavouriteGroupInfoDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcFavouriteGroupInfoDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcFavouriteGroupInfoDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcFavouriteGroupInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *tcFavouriteGroupInfoDialog)
    {
        tcFavouriteGroupInfoDialog->setWindowTitle(QApplication::translate("tcFavouriteGroupInfoDialog", "Favourite Group...", 0));
        grp1->setTitle(QApplication::translate("tcFavouriteGroupInfoDialog", "Info:", 0));
        lbl1->setText(QApplication::translate("tcFavouriteGroupInfoDialog", "Group Name:", 0));
        lbl2->setText(QApplication::translate("tcFavouriteGroupInfoDialog", "Description:", 0));
    } // retranslateUi

};

namespace Ui {
    class tcFavouriteGroupInfoDialog: public Ui_tcFavouriteGroupInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_FAVOURITEGROUPINFODLG_H
