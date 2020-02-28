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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_5_clicked() // class select / browse button
{
    QStringList class_ = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            "/home",
                            "Classes (*.names)");

    filemodel = new QFileSystemModel(this);
    filemodel->setReadOnly(false);

    QStringListModel *model = new QStringListModel();
    model->setStringList(class_);
    ui->listView->setModel(model);
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_7_clicked() // image browse / select button
{
    QStringList images = QFileDialog::getOpenFileNames(
                                this,
                                "Select one or more files to open",
                                "/home",
                                "Images (*.jpg *.jpeg);;PNG (*.png)");

    filemodel = new QFileSystemModel(this);
    filemodel->setReadOnly(true);
    ui->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //To disable editing
    QStringListModel *model = new QStringListModel();
    model->setStringList(images);
    ui->listWidget->addItems(images);

    //filemodel = new QFileSystemModel(this);
    //filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    //filemodel->setReadOnly(true);


}

void MainWindow::on_listView_2_activated(const QModelIndex &index) // image display pane
{

}

void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

void MainWindow::on_pushButton_8_clicked() //image save button
{

}



void MainWindow::on_listWidget_clicked(const QModelIndex &index) // list widget / image file pane
{
    QList <QListWidgetItem*> items=ui->listWidget->selectedItems();
    for(int j=0;j<items.count();j++)
    {
        QString list= items.at(j)->text();
        ui->listWidget->insertItem(j,list);
    }
    //add external function to perform the image loop
    QString list;
    scene = new QGraphicsScene(this);
    scene->addPixmap(list);
    scene->setSceneRect(image.rect());
    ui->graphicsView->setScene(scene);
}
