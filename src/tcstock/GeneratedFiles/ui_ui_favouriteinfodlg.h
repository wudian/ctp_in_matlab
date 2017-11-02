/********************************************************************************
** Form generated from reading UI file 'ui_favouriteinfodlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_FAVOURITEINFODLG_H
#define UI_UI_FAVOURITEINFODLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tcFavouriteInfoDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QComboBox *cbo1;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QSpacerItem *spacerItem;
    QTableView *tbl1;
    QHBoxLayout *hboxLayout1;
    QPushButton *btn4;
    QPushButton *btn5;
    QSpacerItem *spacerItem1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tcFavouriteInfoDialog)
    {
        if (tcFavouriteInfoDialog->objectName().isEmpty())
            tcFavouriteInfoDialog->setObjectName(QStringLiteral("tcFavouriteInfoDialog"));
        tcFavouriteInfoDialog->resize(565, 420);
        vboxLayout = new QVBoxLayout(tcFavouriteInfoDialog);
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
        cbo1 = new QComboBox(tcFavouriteInfoDialog);
        cbo1->setObjectName(QStringLiteral("cbo1"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cbo1->sizePolicy().hasHeightForWidth());
        cbo1->setSizePolicy(sizePolicy);

        hboxLayout->addWidget(cbo1);

        btn1 = new QPushButton(tcFavouriteInfoDialog);
        btn1->setObjectName(QStringLiteral("btn1"));

        hboxLayout->addWidget(btn1);

        btn2 = new QPushButton(tcFavouriteInfoDialog);
        btn2->setObjectName(QStringLiteral("btn2"));

        hboxLayout->addWidget(btn2);

        btn3 = new QPushButton(tcFavouriteInfoDialog);
        btn3->setObjectName(QStringLiteral("btn3"));

        hboxLayout->addWidget(btn3);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

        tbl1 = new QTableView(tcFavouriteInfoDialog);
        tbl1->setObjectName(QStringLiteral("tbl1"));

        vboxLayout->addWidget(tbl1);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        btn4 = new QPushButton(tcFavouriteInfoDialog);
        btn4->setObjectName(QStringLiteral("btn4"));

        hboxLayout1->addWidget(btn4);

        btn5 = new QPushButton(tcFavouriteInfoDialog);
        btn5->setObjectName(QStringLiteral("btn5"));

        hboxLayout1->addWidget(btn5);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem1);


        vboxLayout->addLayout(hboxLayout1);

        buttonBox = new QDialogButtonBox(tcFavouriteInfoDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(tcFavouriteInfoDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), tcFavouriteInfoDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tcFavouriteInfoDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(tcFavouriteInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *tcFavouriteInfoDialog)
    {
        tcFavouriteInfoDialog->setWindowTitle(QApplication::translate("tcFavouriteInfoDialog", "Favourite Info...", 0));
        btn1->setText(QApplication::translate("tcFavouriteInfoDialog", "Add Group", 0));
        btn2->setText(QApplication::translate("tcFavouriteInfoDialog", "Edit Group", 0));
        btn3->setText(QApplication::translate("tcFavouriteInfoDialog", "Remove Group", 0));
        btn4->setText(QApplication::translate("tcFavouriteInfoDialog", "Append Stock", 0));
        btn5->setText(QApplication::translate("tcFavouriteInfoDialog", "Remove Stock", 0));
    } // retranslateUi

};

namespace Ui {
    class tcFavouriteInfoDialog: public Ui_tcFavouriteInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_FAVOURITEINFODLG_H
