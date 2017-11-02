/********************************************************************************
** Form generated from reading UI file 'ui_stocklistwgt.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_STOCKLISTWGT_H
#define UI_UI_STOCKLISTWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcStockListWidget
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QComboBox *cbo1;
    QPushButton *btn1;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout1;
    QLabel *lbl1;
    QLabel *lbl2;
    QVBoxLayout *vboxLayout2;
    QLineEdit *edt1;
    QLineEdit *edt2;
    QTableWidget *tbl1;

    void setupUi(QWidget *tcStockListWidget)
    {
        if (tcStockListWidget->objectName().isEmpty())
            tcStockListWidget->setObjectName(QStringLiteral("tcStockListWidget"));
        tcStockListWidget->resize(269, 300);
        vboxLayout = new QVBoxLayout(tcStockListWidget);
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
        cbo1 = new QComboBox(tcStockListWidget);
        cbo1->setObjectName(QStringLiteral("cbo1"));

        hboxLayout->addWidget(cbo1);

        btn1 = new QPushButton(tcStockListWidget);
        btn1->setObjectName(QStringLiteral("btn1"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(4), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn1->sizePolicy().hasHeightForWidth());
        btn1->setSizePolicy(sizePolicy);

        hboxLayout->addWidget(btn1);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        vboxLayout1 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
#endif
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        lbl1 = new QLabel(tcStockListWidget);
        lbl1->setObjectName(QStringLiteral("lbl1"));

        vboxLayout1->addWidget(lbl1);

        lbl2 = new QLabel(tcStockListWidget);
        lbl2->setObjectName(QStringLiteral("lbl2"));

        vboxLayout1->addWidget(lbl2);


        hboxLayout1->addLayout(vboxLayout1);

        vboxLayout2 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        edt1 = new QLineEdit(tcStockListWidget);
        edt1->setObjectName(QStringLiteral("edt1"));

        vboxLayout2->addWidget(edt1);

        edt2 = new QLineEdit(tcStockListWidget);
        edt2->setObjectName(QStringLiteral("edt2"));

        vboxLayout2->addWidget(edt2);


        hboxLayout1->addLayout(vboxLayout2);


        vboxLayout->addLayout(hboxLayout1);

        tbl1 = new QTableWidget(tcStockListWidget);
        tbl1->setObjectName(QStringLiteral("tbl1"));

        vboxLayout->addWidget(tbl1);


        retranslateUi(tcStockListWidget);

        QMetaObject::connectSlotsByName(tcStockListWidget);
    } // setupUi

    void retranslateUi(QWidget *tcStockListWidget)
    {
        tcStockListWidget->setWindowTitle(QApplication::translate("tcStockListWidget", "Stock List...", 0));
        btn1->setText(QApplication::translate("tcStockListWidget", "Favourite", 0));
        lbl1->setText(QApplication::translate("tcStockListWidget", "Stock Code:", 0));
        lbl2->setText(QApplication::translate("tcStockListWidget", "Stock Name:", 0));
    } // retranslateUi

};

namespace Ui {
    class tcStockListWidget: public Ui_tcStockListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_STOCKLISTWGT_H
