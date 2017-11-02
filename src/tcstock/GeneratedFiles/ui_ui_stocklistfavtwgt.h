/********************************************************************************
** Form generated from reading UI file 'ui_stocklistfavtwgt.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_STOCKLISTFAVTWGT_H
#define UI_UI_STOCKLISTFAVTWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcStockListFavouriteWidget
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QComboBox *cbo1;
    QToolButton *btn1;
    QTableWidget *tbl1;

    void setupUi(QWidget *tcStockListFavouriteWidget)
    {
        if (tcStockListFavouriteWidget->objectName().isEmpty())
            tcStockListFavouriteWidget->setObjectName(QStringLiteral("tcStockListFavouriteWidget"));
        tcStockListFavouriteWidget->resize(185, 300);
        vboxLayout = new QVBoxLayout(tcStockListFavouriteWidget);
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
        cbo1 = new QComboBox(tcStockListFavouriteWidget);
        cbo1->setObjectName(QStringLiteral("cbo1"));

        hboxLayout->addWidget(cbo1);

        btn1 = new QToolButton(tcStockListFavouriteWidget);
        btn1->setObjectName(QStringLiteral("btn1"));

        hboxLayout->addWidget(btn1);


        vboxLayout->addLayout(hboxLayout);

        tbl1 = new QTableWidget(tcStockListFavouriteWidget);
        tbl1->setObjectName(QStringLiteral("tbl1"));

        vboxLayout->addWidget(tbl1);


        retranslateUi(tcStockListFavouriteWidget);

        QMetaObject::connectSlotsByName(tcStockListFavouriteWidget);
    } // setupUi

    void retranslateUi(QWidget *tcStockListFavouriteWidget)
    {
        tcStockListFavouriteWidget->setWindowTitle(QApplication::translate("tcStockListFavouriteWidget", "Favourite Stocks", 0));
        btn1->setText(QApplication::translate("tcStockListFavouriteWidget", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class tcStockListFavouriteWidget: public Ui_tcStockListFavouriteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_STOCKLISTFAVTWGT_H
