#include "functions.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qt>
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

//^ libraries,classes,and header files

class RectResizer : public SizeGripItem::Resizer // resize class for rectagle
    {
        public:
            virtual void operator()(QGraphicsItem* item, const QRectF& rect)
            {
                QGraphicsRectItem* rectItem =
                    dynamic_cast<QGraphicsRectItem*>(item);

                if (rectItem)
                {
                    rectItem->setRect(rect);
                }
            }
    };

    class EllipseResizer : public SizeGripItem::Resizer //resize class for ellipse
    {
        public:
            virtual void operator()(QGraphicsItem* item, const QRectF& rect)
            {
                QGraphicsEllipseItem* ellipseItem =
                    dynamic_cast<QGraphicsEllipseItem*>(item);

                if (ellipseItem)
                {
                    ellipseItem->setRect(rect);
                }
            }
    };



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui ->graphicsView->setScene(scene);
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
        QMessageBox::information(0,"Error",textFile.errorString()); // if selecting file is interrupted or read-onl throw errory
    }


    QTextStream textStream(&textFile);

    while (true)  // textstream to read from file
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            stringList.append(line); // populate the stringlist
    }


    classFileError(stringList);

    model->setStringList(stringList);  // Populate the model

    ui->listView->setModel(model);  // Glue model and view together

}

void MainWindow::on_pushButton_7_clicked() // image browse button
{
    QStringList images = QFileDialog::getOpenFileNames(   //open up file browser with QFileDialog
                                this,                     //and assign selected file paths to a QStringList of images variable
                                "Select one or more files to open",
                                "/home",     // default directory
                                "JPG (*.jpg *.jpeg);;PNG (*.png);;ALL (*.jpg *.jpeg *.png)"); //filetypes elligible to be selected by user


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
}

void MainWindow::populateScene() // adding rectangle to the image
{

}

void MainWindow::on_pushButton_11_clicked()  // rectangle shape creator
{
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(0, 0, 320, 240));
    QColor brush_color(Qt::blue); //fill color
    brush_color.setAlpha(50); // alpha index makes brush color more opaque
    QPen blackpen(Qt::black); //border color
    blackpen.setWidth(2); // border width
    rectItem->setBrush(brush_color); // using brush color
    rectItem->setPen(blackpen);
    rectItem->setFlag(QGraphicsItem::ItemIsMovable); // making the object draggable across graphics view
    scene->addItem(rectItem);

    SizeGripItem* rectSizeGripItem =
            new SizeGripItem(new RectResizer, rectItem); //assigning the new coordinate values to the object

}

void MainWindow::on_pushButton_clicked() // Save COCO button
{

}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_10_clicked() //ellipse shape creator
{
    QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(QRectF(0, 0, 200, 200));
    QColor brush_color(Qt::red); //fill color
    brush_color.setAlpha(50); // alpha index makes brush color more opaque
    QPen blackpen(Qt::black); //border color
    blackpen.setWidth(2); // border width
    ellipseItem->setBrush(brush_color);
    ellipseItem->setPen(blackpen);
    ellipseItem->setFlag(QGraphicsItem::ItemIsMovable); // making the object draggable across graphics view
    scene->addItem(ellipseItem);

    SizeGripItem* ellipseSizeGripItem =
        new SizeGripItem(new EllipseResizer, ellipseItem); //assigning the new coordinate values to the object
}

void MainWindow::on_pushButton_13_clicked()   //sort ascending button
{
    QStringList itemsMedium; //string list to hold all items from listwidget in plain text

    for(int i = 0; i < ui->listWidget->count(); ++i) // for loop to iterate through all listwidget items
    {
        QListWidgetItem* item = ui->listWidget->item(i); //getting each item one by one from list widget
        itemsMedium << item->text(); // transforming the item into plain text and adding it to our string list
    }

    std::sort(itemsMedium.begin(), itemsMedium.end(),compareNamesAscending); //sorting the string list from beggining to the end in ascending order

    ui->listWidget->clear(); // clearing the old order of items in list widget

    QStringListModel *model = new QStringListModel(); // create a string list model which will store selected image file paths

    model->setStringList(itemsMedium); // fill the model with file paths
    ui->listWidget->addItems(itemsMedium); // display updated order selection

}

void MainWindow::on_pushButton_14_clicked()
{
    //sort descending button
    QStringList itemsMedium; //string list to hold all items from listwidget in plain text

    for(int i = 0; i < ui->listWidget->count(); ++i) // for loop to iterate through all listwidget items
    {
        QListWidgetItem* item = ui->listWidget->item(i); //getting each item one by one from list widget
        itemsMedium << item->text(); // transforming the item into plain text and addin it to our string list
    }

    std::sort(itemsMedium.begin(), itemsMedium.end(),compareNamesAscending); //sorting the string list from beggining to the end in ascending order
    std::reverse(itemsMedium.begin(),itemsMedium.end()); // IMPORTANT this reverses strings into descending order, only change from above code

    ui->listWidget->clear(); // clearing the old order of items in list widget

    QStringListModel *model = new QStringListModel(); // create a string list model which will store selected image file paths

    model->setStringList(itemsMedium); // fill the model with file paths
    ui->listWidget->addItems(itemsMedium); // display updated order selection
}

void MainWindow::on_pushButton_15_clicked()
{
    //clear button for image listwidget
    ui->listWidget->clear();
}

void MainWindow::on_pushButton_16_clicked()
{
    //Sort ascending by file creation date
    QStringList itemsMedium; //string list to hold all items from listwidget in plain text

    for(int i = 0; i < ui->listWidget->count(); i++) // for loop to iterate through all listwidget items
    {
        QListWidgetItem* item = ui->listWidget->item(i); //getting each item one by one from list widget
        itemsMedium << item->text(); // transforming the item into plain text and addin it to our string list
    }
    QStringList itemsLastModifiedMedium;
    for(int i = 0; i < itemsMedium.count();i++)
    {
        const QFileInfo info(itemsMedium[i]); //select the file we want info about
        const QDateTime lastModified = info.lastModified(); // get the last modified date and time of the selected file
        QString as = lastModified.toString("yyyy-MM-dd HH:mm:ss"); // convert data from QFileInfo and QDateTime to string with above format
        itemsLastModifiedMedium << as; // add our converted data to a list where are file data will be stored
    }

    QList<QStringList> combinedList; // will hold values of both lists in a combined list made up of filepaths and file dates

    for(int i = 0; i < itemsMedium.count(); i++) //loop to separate values into couples and add them to combined list
    {
        QStringList adder; //list used to store values between iterations
        QString x = itemsLastModifiedMedium[i]; //find date value at point i
        QString y = itemsMedium[i]; //find the file of which the date is
        adder << x; //add value to list
        adder << y; //add value to list
        combinedList << adder; // add the loop list into our combined list
        adder.clear(); // clear the list so that its clear for the next iteration
    }

    std::sort(combinedList.begin(), combinedList.end(),[](const QList<QString>& left,const QList<QString>& right)->bool{
        if(left.empty() && right.empty())
            return false;
        if(left.empty())
            return true;
        if(right.empty())
            return false;
        return left.first()<right.first();
    });
    //qDebug() << combinedList;

    QStringList orderedOutput;

    for(int i = 0; i < itemsMedium.count(); i++) // fill in orderedOutput list with just filepaths or the 2nd value of each list
    {
        QStringList adder; //QStringList to hold loop values
        adder << combinedList[i]; //assigning a sorted pair
        orderedOutput << adder[1];
        adder.clear();
    }

    ui->listWidget->clear(); // clearing the old order of items in list widget

    QStringListModel *model = new QStringListModel(); // create a string list model which will store selected image file paths

    model->setStringList(orderedOutput); // fill the model with file paths
    ui->listWidget->addItems(orderedOutput); // display updated order selection
}

void MainWindow::on_pushButton_17_clicked()
{
    //Sort descending by file creation date
    QStringList itemsMedium; //string list to hold all items from listwidget in plain text

    for(int i = 0; i < ui->listWidget->count(); i++) // for loop to iterate through all listwidget items
    {
        QListWidgetItem* item = ui->listWidget->item(i); //getting each item one by one from list widget
        itemsMedium << item->text(); // transforming the item into plain text and addin it to our string list
    }
    QStringList itemsLastModifiedMedium;
    for(int i = 0; i < itemsMedium.count();i++)
    {
        const QFileInfo info(itemsMedium[i]); //select the file we want info about
        const QDateTime lastModified = info.lastModified(); // get the last modified date and time of the selected file
        QString as = lastModified.toString("yyyy-MM-dd HH:mm:ss"); // convert data from QFileInfo and QDateTime to string with above format
        itemsLastModifiedMedium << as; // add our converted data to a list where are file data will be stored
    }

    QList<QStringList> combinedList; // will hold values of both lists in a combined list made up of filepaths and file dates

    for(int i = 0; i < itemsMedium.count(); i++) //loop to separate values into couples and add them to combined list
    {
        QStringList adder; //list used to store values between iterations
        QString x = itemsLastModifiedMedium[i]; //find date value at point i
        QString y = itemsMedium[i]; //find the file of which the date is
        adder << x; //add value to list
        adder << y; //add value to list
        combinedList << adder; // add the loop list into our combined list
        adder.clear(); // clear the list so that its clear for the next iteration
    }

    std::sort(combinedList.begin(), combinedList.end(),[](const QList<QString>& left,const QList<QString>& right)->bool{
        if(left.empty() && right.empty())
            return false;
        if(left.empty())
            return true;
        if(right.empty())
            return false;
        return left.first()<right.first();
    });



    QStringList orderedOutput;

    for(int i = 0; i < itemsMedium.count(); i++) // fill in orderedOutput list with just filepaths or the 2nd value of each list
    {
        QStringList adder; //QStringList to hold loop values
        adder << combinedList[i]; //assigning a sorted pair
        orderedOutput << adder[1];
        adder.clear();
    }

    std::reverse(orderedOutput.begin(),orderedOutput.end()); //AGAIN only change from ascending is reversing the order in the end

    ui->listWidget->clear(); // clearing the old order of items in list widget

    QStringListModel *model = new QStringListModel(); // create a string list model which will store selected image file paths

    model->setStringList(orderedOutput); // fill the model with file paths
    ui->listWidget->addItems(orderedOutput); // display updated order selection

}
