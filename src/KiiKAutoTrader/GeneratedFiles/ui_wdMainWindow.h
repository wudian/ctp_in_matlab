/********************************************************************************
** Form generated from reading UI file 'wdMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WDMAINWINDOW_H
#define UI_WDMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_insts;
    QLabel *label_4;
    QLineEdit *lineEdit_periods;
    QPushButton *pushButton_sub;
    QPushButton *pushButton_unsub;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_isHistory;
    QLabel *label;
    QLineEdit *lineEdit_beginTime;
    QLabel *label_2;
    QLineEdit *lineEdit_endTime;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *tableWidget_tick;
    QTableWidget *tableWidget_kline;
    QTabWidget *tabWidget_2;
    QWidget *Order;
    QTableWidget *tableWidget_Order;
    QWidget *Account;
    QWidget *Instrument;
    QTableWidget *tableWidget_inst;
    QGroupBox *groupBox;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QLabel *label_6;
    QComboBox *comboBox;
    QLabel *label_7;
    QComboBox *comboBox_2;
    QLabel *label_8;
    QSpinBox *spinBox;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_10;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_5;
    QTextBrowser *textBrowser;
    QLabel *label_11;
    QTableWidget *tableWidget_position;
    QTableWidget *tableWidget_trade;
    QLabel *label_12;
    QLabel *label_13;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1463, 882);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 661, 261));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEdit_insts = new QLineEdit(verticalLayoutWidget_3);
        lineEdit_insts->setObjectName(QStringLiteral("lineEdit_insts"));

        horizontalLayout_2->addWidget(lineEdit_insts);

        label_4 = new QLabel(verticalLayoutWidget_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_periods = new QLineEdit(verticalLayoutWidget_3);
        lineEdit_periods->setObjectName(QStringLiteral("lineEdit_periods"));

        horizontalLayout_2->addWidget(lineEdit_periods);

        pushButton_sub = new QPushButton(verticalLayoutWidget_3);
        pushButton_sub->setObjectName(QStringLiteral("pushButton_sub"));

        horizontalLayout_2->addWidget(pushButton_sub);

        pushButton_unsub = new QPushButton(verticalLayoutWidget_3);
        pushButton_unsub->setObjectName(QStringLiteral("pushButton_unsub"));

        horizontalLayout_2->addWidget(pushButton_unsub);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox_isHistory = new QCheckBox(verticalLayoutWidget_3);
        checkBox_isHistory->setObjectName(QStringLiteral("checkBox_isHistory"));
        checkBox_isHistory->setCheckable(true);
        checkBox_isHistory->setChecked(false);
        checkBox_isHistory->setAutoRepeat(true);

        horizontalLayout->addWidget(checkBox_isHistory);

        label = new QLabel(verticalLayoutWidget_3);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_beginTime = new QLineEdit(verticalLayoutWidget_3);
        lineEdit_beginTime->setObjectName(QStringLiteral("lineEdit_beginTime"));

        horizontalLayout->addWidget(lineEdit_beginTime);

        label_2 = new QLabel(verticalLayoutWidget_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_endTime = new QLineEdit(verticalLayoutWidget_3);
        lineEdit_endTime->setObjectName(QStringLiteral("lineEdit_endTime"));

        horizontalLayout->addWidget(lineEdit_endTime);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        tableWidget_tick = new QTableWidget(verticalLayoutWidget_3);
        if (tableWidget_tick->columnCount() < 3)
            tableWidget_tick->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_tick->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_tick->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_tick->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_tick->setObjectName(QStringLiteral("tableWidget_tick"));

        horizontalLayout_3->addWidget(tableWidget_tick);

        tableWidget_kline = new QTableWidget(verticalLayoutWidget_3);
        if (tableWidget_kline->columnCount() < 6)
            tableWidget_kline->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_kline->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_kline->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_kline->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_kline->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_kline->setHorizontalHeaderItem(4, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_kline->setHorizontalHeaderItem(5, __qtablewidgetitem8);
        tableWidget_kline->setObjectName(QStringLiteral("tableWidget_kline"));
        tableWidget_kline->horizontalHeader()->setDefaultSectionSize(50);

        horizontalLayout_3->addWidget(tableWidget_kline);


        verticalLayout_3->addLayout(horizontalLayout_3);

        tabWidget_2 = new QTabWidget(centralwidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(20, 460, 1381, 361));
        tabWidget_2->setLayoutDirection(Qt::LeftToRight);
        Order = new QWidget();
        Order->setObjectName(QStringLiteral("Order"));
        tableWidget_Order = new QTableWidget(Order);
        if (tableWidget_Order->columnCount() < 13)
            tableWidget_Order->setColumnCount(13);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(6, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(7, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(8, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(9, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(10, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(11, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_Order->setHorizontalHeaderItem(12, __qtablewidgetitem21);
        tableWidget_Order->setObjectName(QStringLiteral("tableWidget_Order"));
        tableWidget_Order->setGeometry(QRect(30, 20, 1341, 301));
        tableWidget_Order->setMinimumSize(QSize(1341, 0));
        tableWidget_Order->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_Order->setAlternatingRowColors(true);
        tableWidget_Order->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidget_Order->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_Order->setColumnCount(13);
        tableWidget_Order->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget_Order->horizontalHeader()->setDefaultSectionSize(90);
        tableWidget_Order->horizontalHeader()->setMinimumSectionSize(20);
        tableWidget_Order->horizontalHeader()->setStretchLastSection(true);
        tableWidget_Order->verticalHeader()->setVisible(false);
        tableWidget_Order->verticalHeader()->setStretchLastSection(false);
        tabWidget_2->addTab(Order, QString());
        Account = new QWidget();
        Account->setObjectName(QStringLiteral("Account"));
        tabWidget_2->addTab(Account, QString());
        Instrument = new QWidget();
        Instrument->setObjectName(QStringLiteral("Instrument"));
        tableWidget_inst = new QTableWidget(Instrument);
        if (tableWidget_inst->columnCount() < 11)
            tableWidget_inst->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(4, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(5, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(6, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(7, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(8, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(9, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_inst->setHorizontalHeaderItem(10, __qtablewidgetitem32);
        tableWidget_inst->setObjectName(QStringLiteral("tableWidget_inst"));
        tableWidget_inst->setGeometry(QRect(10, 10, 1171, 291));
        tableWidget_inst->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_inst->setAlternatingRowColors(true);
        tableWidget_inst->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_inst->setColumnCount(11);
        tableWidget_inst->verticalHeader()->setVisible(false);
        tabWidget_2->addTab(Instrument, QString());
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(680, 80, 781, 91));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 20, 54, 12));
        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(20, 50, 113, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(180, 20, 54, 12));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(160, 50, 69, 22));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(280, 20, 54, 12));
        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(260, 50, 69, 22));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(380, 20, 54, 12));
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(380, 50, 42, 22));
        spinBox->setMinimum(1);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(480, 20, 54, 12));
        doubleSpinBox = new QDoubleSpinBox(groupBox);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(461, 50, 81, 22));
        doubleSpinBox->setMaximum(1e+08);
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(600, 20, 54, 12));
        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(590, 50, 71, 20));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(680, 20, 91, 51));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(810, 0, 491, 81));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(730, 30, 81, 16));
        tableWidget_position = new QTableWidget(centralwidget);
        if (tableWidget_position->columnCount() < 5)
            tableWidget_position->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_position->setHorizontalHeaderItem(0, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_position->setHorizontalHeaderItem(1, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_position->setHorizontalHeaderItem(2, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_position->setHorizontalHeaderItem(3, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_position->setHorizontalHeaderItem(4, __qtablewidgetitem37);
        tableWidget_position->setObjectName(QStringLiteral("tableWidget_position"));
        tableWidget_position->setGeometry(QRect(840, 180, 551, 101));
        tableWidget_position->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_position->setAlternatingRowColors(true);
        tableWidget_trade = new QTableWidget(centralwidget);
        if (tableWidget_trade->columnCount() < 11)
            tableWidget_trade->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(0, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(1, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(2, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(3, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(4, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(5, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(6, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(7, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(8, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(9, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget_trade->setHorizontalHeaderItem(10, __qtablewidgetitem48);
        tableWidget_trade->setObjectName(QStringLiteral("tableWidget_trade"));
        tableWidget_trade->setGeometry(QRect(240, 290, 1141, 181));
        tableWidget_trade->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_trade->setAlternatingRowColors(true);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(740, 200, 81, 16));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(190, 310, 41, 21));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 290, 75, 51));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(20, 370, 75, 51));
        MainWindow->setCentralWidget(centralwidget);
        verticalLayoutWidget_3->raise();
        tabWidget_2->raise();
        groupBox->raise();
        textBrowser->raise();
        label_11->raise();
        tableWidget_position->raise();
        tableWidget_trade->raise();
        label_12->raise();
        label_13->raise();
        tableWidget_Order->raise();
        pushButton_3->raise();
        pushButton_4->raise();
        pushButton_4->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1463, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_3->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246\344\273\243\347\240\201\357\274\232", 0));
        label_4->setText(QApplication::translate("MainWindow", "\345\221\250\346\234\237\357\274\232", 0));
        pushButton_sub->setText(QApplication::translate("MainWindow", "\350\256\242\351\230\205\350\241\214\346\203\205", 0));
        pushButton_unsub->setText(QApplication::translate("MainWindow", "\351\200\200\350\256\242\350\241\214\346\203\205", 0));
        checkBox_isHistory->setText(QApplication::translate("MainWindow", "\345\216\206\345\217\262", 0));
        label->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\227\266\351\227\264\357\274\232", 0));
        label_2->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_tick->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_tick->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\345\221\250\346\234\237", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_tick->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\346\234\200\346\226\260\344\273\267", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_kline->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_kline->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\345\221\250\346\234\237", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_kline->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\345\274\200", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_kline->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "\351\253\230", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_kline->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "\344\275\216", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_kline->horizontalHeaderItem(5);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "\346\224\266", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_Order->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "\346\212\245\345\215\225\347\274\226\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_Order->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "\346\212\245\345\215\225\347\261\273\345\236\213", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_Order->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_Order->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "\344\271\260\345\215\226", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_Order->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "\345\274\200\345\271\263", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_Order->horizontalHeaderItem(5);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_Order->horizontalHeaderItem(6);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "\345\247\224\346\211\230\344\273\267", 0));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_Order->horizontalHeaderItem(7);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "\345\247\224\346\211\230\351\207\217", 0));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_Order->horizontalHeaderItem(8);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "\345\217\257\346\222\244\351\207\217", 0));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_Order->horizontalHeaderItem(9);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "\345\267\262\346\210\220\344\272\244\351\207\217", 0));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_Order->horizontalHeaderItem(10);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264", 0));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_Order->horizontalHeaderItem(11);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "\344\272\244\346\230\223\346\211\200", 0));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_Order->horizontalHeaderItem(12);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "\350\257\246\346\203\205\344\277\241\346\201\257", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(Order), QApplication::translate("MainWindow", "\345\247\224\346\211\230", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(Account), QApplication::translate("MainWindow", "\350\264\246\346\210\267", 0));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_inst->horizontalHeaderItem(0);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "\345\223\201\347\247\215\344\273\243\347\240\201", 0));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_inst->horizontalHeaderItem(1);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246", 0));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_inst->horizontalHeaderItem(2);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "\344\272\244\346\230\223\346\211\200", 0));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_inst->horizontalHeaderItem(3);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246\344\271\230\346\225\260", 0));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_inst->horizontalHeaderItem(4);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "\346\234\200\345\260\217\345\217\230\345\212\250\344\273\267\344\275\215", 0));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_inst->horizontalHeaderItem(5);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246\344\272\244\346\230\223\347\212\266\346\200\201", 0));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_inst->horizontalHeaderItem(6);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "\345\244\232\345\244\264\344\277\235\350\257\201\351\207\221\347\216\207", 0));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_inst->horizontalHeaderItem(7);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "\347\251\272\345\244\264\344\277\235\350\257\201\351\207\221\347\216\207", 0));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_inst->horizontalHeaderItem(8);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "\345\274\200\344\273\223\346\211\213\347\273\255\350\264\271\347\216\207", 0));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_inst->horizontalHeaderItem(9);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "\345\271\263\344\273\223\346\211\213\347\273\255\350\264\271\347\216\207", 0));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_inst->horizontalHeaderItem(10);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "\345\271\263\344\273\212\346\211\213\347\273\255\350\264\271\347\216\207", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(Instrument), QApplication::translate("MainWindow", "\345\220\210\347\272\246", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\344\270\213\345\215\225", 0));
        label_5->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246", 0));
        label_6->setText(QApplication::translate("MainWindow", "\344\271\260\345\215\226", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\344\271\260\345\205\245", 0)
         << QApplication::translate("MainWindow", "\345\215\226\345\207\272", 0)
        );
        label_7->setText(QApplication::translate("MainWindow", "\345\274\200\345\271\263", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\274\200\344\273\223", 0)
         << QApplication::translate("MainWindow", "\345\271\263\344\273\223", 0)
         << QApplication::translate("MainWindow", "\345\271\263\344\273\212", 0)
        );
        label_8->setText(QApplication::translate("MainWindow", "\346\211\213\346\225\260", 0));
        label_9->setText(QApplication::translate("MainWindow", "\346\214\207\345\256\232\344\273\267", 0));
        label_10->setText(QApplication::translate("MainWindow", "\346\225\260\351\207\217\345\200\215\347\216\207", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "\344\270\213\345\215\225", 0));
        label_11->setText(QApplication::translate("MainWindow", "\351\224\231\350\257\257\344\277\241\346\201\257\357\274\232", 0));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_position->horizontalHeaderItem(0);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246", 0));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_position->horizontalHeaderItem(1);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "\345\244\232\347\251\272\346\226\271\345\220\221", 0));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_position->horizontalHeaderItem(2);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "\346\200\273\344\273\223", 0));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_position->horizontalHeaderItem(3);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "\345\217\257\347\224\250\344\273\223", 0));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_position->horizontalHeaderItem(4);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "\345\274\200\344\273\223\345\235\207\344\273\267", 0));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_trade->horizontalHeaderItem(0);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "\346\210\220\344\272\244\347\274\226\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget_trade->horizontalHeaderItem(1);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "\346\212\245\345\215\225\347\274\226\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget_trade->horizontalHeaderItem(2);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246\344\273\243\347\240\201", 0));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget_trade->horizontalHeaderItem(3);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "\344\271\260\345\215\226", 0));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget_trade->horizontalHeaderItem(4);
        ___qtablewidgetitem42->setText(QApplication::translate("MainWindow", "\345\274\200\345\271\263", 0));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget_trade->horizontalHeaderItem(5);
        ___qtablewidgetitem43->setText(QApplication::translate("MainWindow", "\346\210\220\344\272\244\345\235\207\344\273\267", 0));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget_trade->horizontalHeaderItem(6);
        ___qtablewidgetitem44->setText(QApplication::translate("MainWindow", "\346\210\220\344\272\244\351\207\217", 0));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget_trade->horizontalHeaderItem(7);
        ___qtablewidgetitem45->setText(QApplication::translate("MainWindow", "\346\210\220\344\272\244\347\261\273\345\236\213", 0));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget_trade->horizontalHeaderItem(8);
        ___qtablewidgetitem46->setText(QApplication::translate("MainWindow", "\346\210\220\344\272\244\346\227\266\351\227\264", 0));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget_trade->horizontalHeaderItem(9);
        ___qtablewidgetitem47->setText(QApplication::translate("MainWindow", "\344\272\244\346\230\223\346\211\200", 0));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget_trade->horizontalHeaderItem(10);
        ___qtablewidgetitem48->setText(QApplication::translate("MainWindow", "\346\212\225\346\234\272\345\245\227\344\277\235\346\240\207\345\277\227", 0));
        label_12->setText(QApplication::translate("MainWindow", "\346\214\201\344\273\223\357\274\232", 0));
        label_13->setText(QApplication::translate("MainWindow", "\346\210\220\344\272\244\357\274\232", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\350\241\214\346\203\205", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\344\272\244\346\230\223", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\347\263\273\347\273\237", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WDMAINWINDOW_H
