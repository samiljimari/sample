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

void MainWindow::on_pushButton_5_clicked()
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
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers); //To disable editing
    QStringListModel *model = new QStringListModel();
    model->setStringList(images);
    ui->listView_2->setModel(model);

    //filemodel = new QFileSystemModel(this);
    //filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    //filemodel->setReadOnly(true);


}

void MainWindow::on_listView_2_activated(const QModelIndex &index) // image file display pane
{

}

void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

void MainWindow::on_pushButton_clicked() // image use button
{
    QString defaultPath("C:/Users/Sami Ljimari/Desktop/image test folder");

    QString imagePath = QFileDialog::getOpenFileName(0, "Open File", defaultPath, tr("JPG (*.jpg *.jpeg);;PNG (*.png)"));

    imageObject = new QImage();
    imageObject->load(imagePath);

    image = QPixmap::fromImage(*imageObject);

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->graphicsView->setScene(scene);

}

void MainWindow::on_pushButton_8_clicked() //image save button
{

}

void MainWindow::on_listView_2_clicked(const QModelIndex &index) //display image when clicked on listview image pane
{
    QList<QString> path_list;
    QString filePath;
    QModelIndex parentIndex = filemodel->index(filePath);
    int numRows = filemodel->rowCount(parentIndex);

    for (int row = 0; row < numRows; ++row) //populating index values with listview items
    {
        QModelIndex childIndex = filemodel->index(row, 0, parentIndex);
        QString path = filemodel->data(childIndex).toString();
        path_list.append(path);
    }
    QString imagePath;

    for(qint32 i = 0; i < path_list.size(); i++) //traversing through list to find index path
       {
        if(path_list.at(i) == index.data())
        {
            imagePath = path_list.at(i);
        }
       }
    QString defaultPath("C:/Users/Sami Ljimari/Desktop/image test folder/pic1.jpg");

    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(fetch()));

    imageObject = new QImage();

    imageObject->load(imagePath);

    image = QPixmap::fromImage(*imageObject);

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());

    ui->label_5->setText(imagePath); //if it's an existing one

}
