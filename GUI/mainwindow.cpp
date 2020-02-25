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

    model = new QFileSystemModel(this);
    model->setReadOnly(false);

    ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QStringList image_ = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            "/home",
                            "Images (*.png *.xpm *.jpg)");
}

void MainWindow::on_treeView_activated(const QModelIndex &index)
{
    model->setRootPath("C:/Users/Sami Ljimari/Desktop/SDI_test_folder");
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index("C:/Users/Sami Ljimari/Desktop/SDI_test_folder"));
}

void MainWindow::on_pushButton_5_clicked()
{
    QStringList class_ = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            "/home",
                            "Images (*.txt)");
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{

}
