#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardItem>
#include <QFileSystemModel>

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


