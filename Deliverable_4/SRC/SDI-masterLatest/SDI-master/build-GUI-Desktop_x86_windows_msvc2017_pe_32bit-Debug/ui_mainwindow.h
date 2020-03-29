/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionread_me;
    QAction *actionabout;
    QAction *actionread_me_2;
    QAction *actionabout_2;
    QWidget *centralWidget;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_5;
    QLabel *label_4;
    QPushButton *pushButton_6;
    QLabel *label_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_9;
    QListView *listView;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuEXIT;
    QMenu *menuinfo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1539, 891);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/imgs/honklhonk.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon);
        actionread_me = new QAction(MainWindow);
        actionread_me->setObjectName(QString::fromUtf8("actionread_me"));
        actionabout = new QAction(MainWindow);
        actionabout->setObjectName(QString::fromUtf8("actionabout"));
        actionread_me_2 = new QAction(MainWindow);
        actionread_me_2->setObjectName(QString::fromUtf8("actionread_me_2"));
        actionabout_2 = new QAction(MainWindow);
        actionabout_2->setObjectName(QString::fromUtf8("actionabout_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(330, 710, 111, 31));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(450, 710, 111, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 41, 21));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(1100, 740, 111, 51));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(130, 60, 431, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 121, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 360, 47, 13));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(60, 350, 81, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 710, 61, 31));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(60, 710, 101, 41));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(580, 20, 91, 16));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(60, 10, 191, 41));
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(440, 10, 121, 41));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 110, 551, 231));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(330, 750, 111, 31));
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(450, 750, 111, 31));
        listView = new QListView(centralWidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(10, 400, 551, 301));
        listView->setAlternatingRowColors(true);
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(570, 740, 91, 41));
        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(670, 740, 91, 41));
        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(770, 740, 101, 41));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(570, 50, 951, 681));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1539, 21));
        menuEXIT = new QMenu(menuBar);
        menuEXIT->setObjectName(QString::fromUtf8("menuEXIT"));
        menuinfo = new QMenu(menuBar);
        menuinfo->setObjectName(QString::fromUtf8("menuinfo"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuEXIT->menuAction());
        menuBar->addAction(menuinfo->menuAction());
        menuEXIT->addAction(actionExit);
        menuinfo->addAction(actionread_me_2);
        menuinfo->addAction(actionabout_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionread_me->setText(QCoreApplication::translate("MainWindow", "read me", nullptr));
        actionabout->setText(QCoreApplication::translate("MainWindow", "about", nullptr));
        actionread_me_2->setText(QCoreApplication::translate("MainWindow", "read me", nullptr));
        actionabout_2->setText(QCoreApplication::translate("MainWindow", "about", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Save YOLO", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "restore", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Images:", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Crop & Save", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Search images in folder:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Classes:", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Bboxes:", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Choose files", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "IMAGE PANE:", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Browse and choose files", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Crop & Save", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Save COCO", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Save VOC", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Add Ellipse", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Add Rectangle", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Add Pentagon", nullptr));
        menuEXIT->setTitle(QCoreApplication::translate("MainWindow", "options", nullptr));
        menuinfo->setTitle(QCoreApplication::translate("MainWindow", "info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
