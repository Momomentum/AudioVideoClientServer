/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *stackedWidgetPage1;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QLineEdit *lineEdit;
    QPushButton *pushButton_12;
    QWidget *page_2;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QListWidget *listWidget_2;
    QListWidget *listWidget_3;
    QProgressBar *progressBar;
    QProgressBar *progressBar_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_11;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *page_3;
    QDial *dial_13;
    QSlider *horizontalSlider;
    QDial *dial_11;
    QDial *dial_8;
    QDial *dial_3;
    QDial *dial_9;
    QDial *dial_2;
    QDial *dial_6;
    QDial *dial_5;
    QDial *dial_7;
    QDial *dial;
    QSlider *verticalSlider;
    QDial *dial_12;
    QSlider *verticalSlider_2;
    QDial *dial_4;
    QDial *dial_10;
    QPushButton *pushButton_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *page_4;
    QPushButton *pushButton_5;
    QVideoWidget *widget;
    QWidget *page;
    QPushButton *pushButton_6;
    QDial *dial_14;
    QDial *dial_17;
    QDial *dial_18;
    QVideoWidget *widget_2;
    QVideoWidget *widget_3;
    QSlider *horizontalSlider_2;
    QVideoWidget *widget_4;
    QDial *dial_15;
    QDial *dial_19;
    QDial *dial_20;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(569, 400);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, -1, 561, 341));
        stackedWidget->setAutoFillBackground(false);
        stackedWidgetPage1 = new QWidget();
        stackedWidgetPage1->setObjectName(QStringLiteral("stackedWidgetPage1"));
        pushButton_7 = new QPushButton(stackedWidgetPage1);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(30, 70, 192, 108));
        pushButton_7->setIconSize(QSize(16, 9));
        pushButton_8 = new QPushButton(stackedWidgetPage1);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(340, 70, 192, 108));
        pushButton_9 = new QPushButton(stackedWidgetPage1);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(30, 230, 192, 108));
        pushButton_10 = new QPushButton(stackedWidgetPage1);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(340, 230, 192, 108));
        lineEdit = new QLineEdit(stackedWidgetPage1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(230, 10, 113, 20));
        pushButton_12 = new QPushButton(stackedWidgetPage1);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(240, 40, 81, 23));
        stackedWidget->addWidget(stackedWidgetPage1);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        listWidget = new QListWidget(page_2);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 40, 131, 261));
        listWidget->setDragEnabled(true);
        listWidget->setDragDropMode(QAbstractItemView::DragOnly);
        pushButton = new QPushButton(page_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 310, 131, 23));
        pushButton_2 = new QPushButton(page_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 10, 131, 23));
        listWidget_2 = new QListWidget(page_2);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(160, 121, 171, 171));
        listWidget_2->setDragEnabled(true);
        listWidget_2->setDragDropMode(QAbstractItemView::DragDrop);
        listWidget_2->setDefaultDropAction(Qt::MoveAction);
        listWidget_3 = new QListWidget(page_2);
        listWidget_3->setObjectName(QStringLiteral("listWidget_3"));
        listWidget_3->setGeometry(QRect(380, 121, 171, 171));
        listWidget_3->setDragEnabled(true);
        listWidget_3->setDragDropMode(QAbstractItemView::DragDrop);
        listWidget_3->setDefaultDropAction(Qt::MoveAction);
        progressBar = new QProgressBar(page_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(160, 60, 171, 23));
        progressBar->setCursor(QCursor(Qt::PointingHandCursor));
        progressBar->setMouseTracking(true);
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        progressBar_2 = new QProgressBar(page_2);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setGeometry(QRect(380, 60, 171, 23));
        progressBar_2->setCursor(QCursor(Qt::PointingHandCursor));
        progressBar_2->setMouseTracking(true);
        progressBar_2->setValue(24);
        progressBar_2->setTextVisible(false);
        pushButton_3 = new QPushButton(page_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(500, 10, 51, 31));
        pushButton_11 = new QPushButton(page_2);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(280, 310, 151, 23));
        label_5 = new QLabel(page_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(160, 90, 171, 20));
        label_6 = new QLabel(page_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(386, 90, 161, 20));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        dial_13 = new QDial(page_3);
        dial_13->setObjectName(QStringLiteral("dial_13"));
        dial_13->setGeometry(QRect(250, 130, 50, 64));
        dial_13->setMaximum(127);
        horizontalSlider = new QSlider(page_3);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(200, 50, 160, 22));
        horizontalSlider->setMaximum(127);
        horizontalSlider->setValue(63);
        horizontalSlider->setOrientation(Qt::Horizontal);
        dial_11 = new QDial(page_3);
        dial_11->setObjectName(QStringLiteral("dial_11"));
        dial_11->setGeometry(QRect(410, 130, 31, 31));
        dial_11->setMaximum(127);
        dial_8 = new QDial(page_3);
        dial_8->setObjectName(QStringLiteral("dial_8"));
        dial_8->setGeometry(QRect(330, 190, 31, 31));
        dial_8->setMaximum(127);
        dial_3 = new QDial(page_3);
        dial_3->setObjectName(QStringLiteral("dial_3"));
        dial_3->setGeometry(QRect(180, 130, 31, 31));
        dial_3->setMaximum(127);
        dial_9 = new QDial(page_3);
        dial_9->setObjectName(QStringLiteral("dial_9"));
        dial_9->setGeometry(QRect(410, 190, 31, 31));
        dial_9->setMaximum(127);
        dial_2 = new QDial(page_3);
        dial_2->setObjectName(QStringLiteral("dial_2"));
        dial_2->setGeometry(QRect(140, 130, 31, 31));
        dial_2->setMaximum(127);
        dial_6 = new QDial(page_3);
        dial_6->setObjectName(QStringLiteral("dial_6"));
        dial_6->setGeometry(QRect(180, 190, 31, 31));
        dial_6->setMaximum(127);
        dial_5 = new QDial(page_3);
        dial_5->setObjectName(QStringLiteral("dial_5"));
        dial_5->setGeometry(QRect(140, 190, 31, 31));
        dial_5->setMaximum(127);
        dial_7 = new QDial(page_3);
        dial_7->setObjectName(QStringLiteral("dial_7"));
        dial_7->setGeometry(QRect(330, 130, 31, 31));
        dial_7->setMaximum(127);
        dial = new QDial(page_3);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setGeometry(QRect(100, 130, 31, 31));
        dial->setMaximum(127);
        verticalSlider = new QSlider(page_3);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(140, 240, 22, 81));
        verticalSlider->setMaximum(127);
        verticalSlider->setOrientation(Qt::Vertical);
        dial_12 = new QDial(page_3);
        dial_12->setObjectName(QStringLiteral("dial_12"));
        dial_12->setGeometry(QRect(370, 190, 31, 31));
        dial_12->setMaximum(127);
        verticalSlider_2 = new QSlider(page_3);
        verticalSlider_2->setObjectName(QStringLiteral("verticalSlider_2"));
        verticalSlider_2->setGeometry(QRect(380, 240, 22, 81));
        verticalSlider_2->setMaximum(127);
        verticalSlider_2->setOrientation(Qt::Vertical);
        dial_4 = new QDial(page_3);
        dial_4->setObjectName(QStringLiteral("dial_4"));
        dial_4->setGeometry(QRect(100, 190, 31, 31));
        dial_4->setMaximum(127);
        dial_10 = new QDial(page_3);
        dial_10->setObjectName(QStringLiteral("dial_10"));
        dial_10->setGeometry(QRect(370, 130, 31, 31));
        dial_10->setMaximum(127);
        pushButton_4 = new QPushButton(page_3);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(500, 10, 51, 31));
        label = new QLabel(page_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 170, 47, 13));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(page_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(370, 170, 47, 13));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(page_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(106, 110, 101, 20));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(page_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(340, 110, 101, 20));
        label_4->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        pushButton_5 = new QPushButton(page_4);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(500, 10, 51, 31));
        widget = new QVideoWidget(page_4);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 49, 551, 281));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        stackedWidget->addWidget(page_4);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        pushButton_6 = new QPushButton(page);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(500, 10, 51, 31));
        dial_14 = new QDial(page);
        dial_14->setObjectName(QStringLiteral("dial_14"));
        dial_14->setGeometry(QRect(70, 220, 50, 51));
        dial_17 = new QDial(page);
        dial_17->setObjectName(QStringLiteral("dial_17"));
        dial_17->setGeometry(QRect(70, 160, 50, 51));
        dial_18 = new QDial(page);
        dial_18->setObjectName(QStringLiteral("dial_18"));
        dial_18->setGeometry(QRect(70, 280, 50, 51));
        widget_2 = new QVideoWidget(page);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(210, 50, 141, 81));
        widget_3 = new QVideoWidget(page);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(30, 50, 141, 81));
        horizontalSlider_2 = new QSlider(page);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(210, 280, 160, 22));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        widget_4 = new QVideoWidget(page);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setGeometry(QRect(380, 50, 141, 81));
        dial_15 = new QDial(page);
        dial_15->setObjectName(QStringLiteral("dial_15"));
        dial_15->setGeometry(QRect(420, 220, 50, 51));
        dial_19 = new QDial(page);
        dial_19->setObjectName(QStringLiteral("dial_19"));
        dial_19->setGeometry(QRect(420, 280, 50, 51));
        dial_20 = new QDial(page);
        dial_20->setObjectName(QStringLiteral("dial_20"));
        dial_20->setGeometry(QRect(420, 160, 50, 51));
        stackedWidget->addWidget(page);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 569, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        pushButton_10->setText(QString());
        lineEdit->setInputMask(QString());
        lineEdit->setText(QApplication::translate("MainWindow", "serveradress", nullptr));
        pushButton_12->setText(QApplication::translate("MainWindow", "confirm", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "load list", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "add file", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Back", nullptr));
        pushButton_11->setText(QApplication::translate("MainWindow", "Confirm lists", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "Back", nullptr));
        label->setText(QApplication::translate("MainWindow", "Effects", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Effects", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "High     Mid     Low", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "High     Mid     Low", nullptr));
        pushButton_5->setText(QApplication::translate("MainWindow", "Back", nullptr));
        pushButton_6->setText(QApplication::translate("MainWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
