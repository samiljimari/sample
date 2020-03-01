#include "functions.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
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

//^ libraries,classes,and header files


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow() //ui termiantion
{
    delete ui;
}

void MainWindow::on_pushButton_5_clicked() // class select / browse button
{
    QString class_ = QFileDialog::getOpenFileName(  //open up file browser with QFileDialog
                            this,                         //and assign selected file paths to a QStringList of images variable
                            "Select one or more files to open",
                            "/home",                      // default directory
                            "Classes (*.names);;TXT Files(*.txt)"); //filetypes elligible to be selected by user

    QStringList stringList; //stringlist for class file data
    QStringListModel *model; // model to store data in

    // Create model
    model = new QStringListModel(this);

    // open the file
    QFile textFile(class_);
    if(!textFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"Error",textFile.errorString()); // if file is empty prompt the user with error
    }

    QTextStream textStream(&textFile);
    while (true)  // teststream to read from file
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            stringList.append(line); // populate the stringlist
    }

    model->setStringList(stringList);  // Populate the model

    ui->listView->setModel(model);  // Glue model and view together

}

void MainWindow::on_pushButton_7_clicked() // image browse / select button
{
    QStringList images = QFileDialog::getOpenFileNames(   //open up file browser with QFileDialog
                                this,                     //and assign selected file paths to a QStringList of images variable
                                "Select one or more files to open",
                                "/home",     // default directory
                                "Images (*.jpg *.jpeg);;PNG (*.png)"); //filetypes elligible to be selected by user

    filemodel = new QFileSystemModel(this); //create a new filemodel
    filemodel->setReadOnly(true); //Filter to disable editing
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs); //remove unwanted directory paths
    ui->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //To disable editing of file names
    QStringListModel *model = new QStringListModel(); // create a string list model which will store selected image file paths
    model->setStringList(images); // fill the model with file paths that user has selected
    ui->listWidget->addItems(images); // display users selection
}

void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

void MainWindow::on_pushButton_8_clicked() //image save button
{

}



void MainWindow::on_listWidget_clicked(const QModelIndex &index) // list widget / image file pane
{
    QList <QListWidgetItem*> items=ui->listWidget->selectedItems(); //input file paths from list widget to QList

    QString imagePath = listTraversal(items,"0"); // Use traversal function on selected item from list widget

    scene = new QGraphicsScene(this); // create new graphics scene

    scene->addPixmap(imagePath); // convert imagepath text into a pixmap scene

    scene->setSceneRect(image.rect()); // create a rectangle on graphics view for the image

    ui->graphicsView->setScene(scene); // fill graphics view with the image

    QGraphicsScene scene;
    scene.addRect(QRectF(-10, -10, 20, 20));

    QGraphicsView view(&scene);
    view.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view.show();
}

void MainWindow::on_pushButton_11_clicked()  // rectangle shape creator
{

}

void MainWindow::on_pushButton_clicked() // Save COCO button
{

}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{

}

MyGraphicsScene::MyGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{
    cursor = new QGraphicsTextItem("0, 0", 0, this); //Fixed at 0, 0
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QString string = QString("%1, %2")
                        .arg(event->scenePos().x())
                        .arg(event->scenePos().y()); //Update the cursor potion text

    cursor->setPlainText(string);
