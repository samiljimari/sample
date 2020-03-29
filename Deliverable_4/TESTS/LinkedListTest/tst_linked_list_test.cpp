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

class Linked_List_Test : public QObject
{
    Q_OBJECT

public:
    Linked_List_Test();
    ~Linked_List_Test();

private slots:
    void test_case1();
private:

    QPixmap image;
    QImage  *imageObject;
    QObject sender;
    QStringList *model;


};

Linked_List_Test::Linked_List_Test()
{

}

Linked_List_Test::~Linked_List_Test()
{

}

void Linked_List_Test::test_case1()
{

}

QTEST_MAIN(Linked_List_Test)

#include "tst_linked_list_test.moc"
