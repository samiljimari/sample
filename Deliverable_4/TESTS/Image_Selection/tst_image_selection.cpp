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

class Image_Selection : public QObject
{
    Q_OBJECT

public:
    Image_Selection();
    ~Image_Selection();

private slots:
    void test_case1();
private:

    QPixmap image;
    QImage  *imageObject;
    QObject sender;
    QStringList *model;


};

Image_Selection::Image_Selection()
{

}

Image_Selection::~Image_Selection()
{

}

void Image_Selection::test_case1()
{

}

QTEST_MAIN(Image_Selection)

#include "tst_image_selection.moc"
