#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardItem>
#include <QFileSystemModel>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString sPath = "C:/";


    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);

    filemodel->setRootPath(sPath);

    QStringList filters; //filters to censor unwanted files from Listview
    filters << "*.jpg";
    filters << "*.png";

    filemodel->setNameFilters(filters);
    filemodel->setNameFilterDisables(false);

    scene = new QGraphicsScene(this);
    //scene->addText("Hello, world!");

    QGraphicsView view;
    ui->graphicsView->setBackgroundBrush(QImage("C:/Users/Sami Ljimari/Desktop/image test folder/pic1.jpg"));
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->show();

    //ui->graphicsView->setScene(scene);
   // QString imagePath = "C:/Users/Sami Ljimari/Desktop/image test folder/pic1.jpg";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_activated(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_5_clicked()
{
    QStringList class_ = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            "/home",
                            "Images (*.names)");

    filemodel = new QFileSystemModel(this);
    filemodel->setReadOnly(false);

    QStringListModel *model = new QStringListModel();
    model->setStringList(class_);
    ui->listView->setModel(model);
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_7_clicked()
{
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::Directory);

    QString _OutputFolder = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());

    dirmodel = new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setReadOnly(true);
    ui->treeView->setModel(dirmodel);
    QModelIndex index = dirmodel->index(_OutputFolder);
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(0);

}

void MainWindow::on_listView_2_activated(const QModelIndex &index)
{

}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView_2->setRootIndex(filemodel->setRootPath(sPath));
    ui->listView_2->setModel(filemodel);
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

void MainWindow::on_listView_2_doubleClicked(const QModelIndex &index) // when double clicked displays the image
{
    QString pathOfIndex = absoluteFilePath(index);

    imageObject = new QImage();
    imageObject->load(pathOfIndex);

    image = QPixmap::fromImage(*imageObject);

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->graphicsView->setScene(scene);
}
