#include "functions.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtTest>
#include <QCoreApplication>
#include <QFileDialog>
#include <QStandardItem>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QtQuick/QQuickPaintedItem>
#include <QList>
#include <QVector>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QListWidget>
#include <QTextStream>
#include <iostream>
#include <QMessageBox>
#include <QStringListModel>
#include <QErrorMessage>
#include <QDebug>
#include <QPainter>
#include <QGraphicsItem>
#include <QBrush>



// add necessary includes here

class Class_Selection : public QObject
{
    Q_OBJECT

public:
    Class_Selection();
    ~Class_Selection();

private slots:
    void test_case1();

private:

    QPixmap image;
    QImage  *imageObject;
    QObject sender;
    QStringList *model;

};

Class_Selection::Class_Selection()
{

}

Class_Selection::~Class_Selection()
{

}

void Class_Selection::test_case1()
{
    QStringList StringList;
    QString *model;

    // Linked list declared and assigned 3 images.
    QList<QString> Class = {"C:/Users/Alceu Caterca/Documents/WORK!!!/Software Design and Implemenation/Classes/Bird"};

   //
    model->setStringList(Class); // fill the model with file paths that user has selected

    ui->ListView->setModel(Class); // Join Model and View Together


   //Check if Selected Class is equal to the one displayed on ListView
   EXPECT_Q(Class, ListView);


}

QTEST_MAIN(Class_Selection)

#include "tst_class_selection.moc"








