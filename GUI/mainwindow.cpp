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
#include <QtWidgets>
#include <global.h>

//^ libraries and header files

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

    class PolygonResizer : public SizeGripItem::Resizer // resize class for polygon
        {
            public:
                virtual void operator()(QGraphicsItem* item, const QRectF& rect)
                {
                    QGraphicsPolygonItem* polygonItem =
                        dynamic_cast<QGraphicsPolygonItem*>(item);

                    QRectF itemBoundingRect = item->boundingRect();
                    float sx = float( rect.width() ) / float( itemBoundingRect.width() );
                    float sy = float( rect.height() ) / float( itemBoundingRect.height() );

                    QTransform transform;
                    transform.scale( sx, sy );

                    transform.translate(0,0);

                    QPolygonF  oldPolygon = polygonItem->polygon();
                    QPolygonF newPolygon = oldPolygon * transform;

                    if (polygonItem)
                    {
                        polygonItem->setPolygon( newPolygon );
                    }
                }
        };

QString txtFileStorage = "";

struct node {
    int data;
    node* next;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui ->graphicsView->setScene(scene);
    ui->pushButton_4->setEnabled(false);

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
                            "Classes (*.names);;TXT Files(*.txt);;ALL (*.names *.txt *.rtf)"); //filetypes elligible to be selected by user

    QStringList stringList; //stringlist for class file data
    QStringListModel *model; // model to store data in

    // Create model
    model = new QStringListModel(this);

    txtFileStorage = class_;

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
            ui->pushButton_4->setEnabled(true);
    }
    //qDebug() << stringList;
    classFileError(stringList);

    model->setStringList(stringList);  // Populate the model

    ui->listView->setModel(model);  // Glue model and view together
}

void MainWindow::on_pushButton_7_clicked() // image browse button
{
    QStringList images = QFileDialog::getOpenFileNames(   //open up file browser with QFileDialog
                                this,                     //and assign selected file paths to a QStringList of images variable
                                "Select one or more files to open",
                                "/Desktop",
                                "JPG (*.jpg *.jpeg);;PNG (*.png);;ALL (*.jpg *.jpeg *.png)"); //filetypes elligible to be selected by user


    filemodel = new QFileSystemModel(this); //create a new filemodel

    filemodel->setReadOnly(true); //Filter to disable editing

    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs); //remove unwanted directory paths

    ui->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //To disable editing of file names

    QStringListModel *model = new QStringListModel(); // create a string list model which will store selected image file paths

    model->setStringList(images); // fill the model with file paths that user has selected

    ui->listWidget->addItems(images); // display users selection
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

void MainWindow::on_pushButton_11_clicked()  // rectangle shape creator
{
    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QPainter painter;

    QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(0, 0, 320, 240));
    QColor brush_color(Qt::blue); //fill color
    brush_color.setAlpha(50); // alpha index makes brush color more opaque
    QPen blackpen(Qt::black); //border color
    blackpen.setWidth(2); // border width
    rectItem->setBrush(brush_color); // using brush color
    rectItem->setPen(blackpen);
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);
    rectItem->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(rectItem);

    QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, rectItem); //assigning class name to rectangle

    SizeGripItem* rectSizeGripItem = new SizeGripItem(new RectResizer, rectItem); //assigning the new coordinate values to the object
    rectSizeGripItem->boundingRect();

}

void MainWindow::on_pushButton_10_clicked() //ellipse shape creator
{
    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(QRectF(0, 0, 200, 200));
    QColor brush_color(Qt::red); //fill color
    brush_color.setAlpha(50); // alpha index makes brush color more opaque
    QPen blackpen(Qt::black); //border color
    blackpen.setWidth(2); // border width
    ellipseItem->setBrush(brush_color);
    ellipseItem->setPen(blackpen);
    ellipseItem->setFlag(QGraphicsItem::ItemIsMovable); // making the object draggable across graphics view
    ellipseItem->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(ellipseItem);

    QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, ellipseItem); //assigning class name to rectange

    SizeGripItem* ellipseSizeGripItem = new SizeGripItem(new EllipseResizer, ellipseItem); //assigning the new coordinate values to the object
}

void MainWindow::on_pushButton_13_clicked()   //sort images ascending button
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
    //sort images descending button
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
    //Sort images ascending by file creation date
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
    qDebug() << combinedList;

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
    //Sort images descending by file creation date
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

void MainWindow::on_pushButton_18_clicked()
{
    //Add Triangle

    QPolygonF Triangle;
    Triangle.append(QPointF(-200.,0));
    Triangle.append(QPointF(0.,-200));
    Triangle.append(QPointF(200.,0));

    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QGraphicsPolygonItem* triangleItem = new QGraphicsPolygonItem(Triangle);
    QColor brush_color(Qt::green); //fill color
    brush_color.setAlpha(50); // alpha index makes brush color more opaque
    QPen blackpen(Qt::black); //border color
    blackpen.setWidth(2); // border width
    triangleItem->setBrush(brush_color); // using brush color
    triangleItem->setPen(blackpen);
    triangleItem->setFlag(QGraphicsItem::ItemIsMovable); // making the object draggable across graphics view
    triangleItem->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(triangleItem);

    QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, triangleItem); //assigning class name to rectange

    SizeGripItem* triangleSizeGripItem = new SizeGripItem(new PolygonResizer, triangleItem);
    //qDebug() << triangleItem->boundingRect();


}

void MainWindow::on_pushButton_12_clicked()
{
    //Add pentagon
    QPolygonF Pentagon;
    Pentagon.append(QPointF(0.,-150));
    Pentagon.append(QPointF(-143.,-46));
    Pentagon.append(QPointF(-88.,121));
    Pentagon.append(QPointF(88.,121));
    Pentagon.append(QPointF(143.,-46));
    //start 0,0 radius 150


    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QGraphicsPolygonItem* pentagonItem = new QGraphicsPolygonItem(Pentagon);
    QColor brush_color(Qt::magenta); //fill color
    brush_color.setAlpha(50); // alpha index makes brush color more opaque
    QPen blackpen(Qt::black); //border color
    blackpen.setWidth(2); // border width
    pentagonItem->setBrush(brush_color); // using brush color
    pentagonItem->setPen(blackpen);
    pentagonItem->setFlag(QGraphicsItem::ItemIsMovable); // making the object draggable across graphics view
    pentagonItem->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(pentagonItem);

    QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, pentagonItem); //assigning class name to rectange

    SizeGripItem* pentagonSizeGripItem = new SizeGripItem(new PolygonResizer, pentagonItem); //assigning the new coordinate values to the object
    //qDebug() << pentagonItem->boundingRect();
}

void MainWindow::on_pushButton_19_clicked()
{
    //Add Hexagon

    QPolygonF Hexagon;
    Hexagon.append(QPointF(75.,-130));
    Hexagon.append(QPointF(-75.,-130));
    Hexagon.append(QPointF(-150.,0));
    Hexagon.append(QPointF(-75.,130));
    Hexagon.append(QPointF(75.,130));
    Hexagon.append(QPointF(150.,0));
    //start 0,0 radius 150


    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QGraphicsPolygonItem* hexagonItem = new QGraphicsPolygonItem(Hexagon);
    QColor brush_color(Qt::cyan); //fill color
    brush_color.setAlpha(50); // alpha index makes brush color more opaque
    QPen blackpen(Qt::black); //border color
    blackpen.setWidth(2); // border width
    hexagonItem->setBrush(brush_color); // using brush color
    hexagonItem->setPen(blackpen);
    hexagonItem->setFlag(QGraphicsItem::ItemIsMovable); // making the object draggable across graphics view
    hexagonItem->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(hexagonItem);

    QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, hexagonItem); //assigning class name to rectange

    SizeGripItem* hexagonSizeGripItem = new SizeGripItem(new PolygonResizer, hexagonItem); //assigning the new coordinate values to the object
}

void MainWindow::on_pushButton_20_clicked()
{
    //Add Heptagon

    QPolygonF Heptagon;
    Heptagon.append(QPointF(0.,-150));
    Heptagon.append(QPointF(-117.,-94));
    Heptagon.append(QPointF(-146.,33));
    Heptagon.append(QPointF(-65.,135));
    Heptagon.append(QPointF(65.,135));
    Heptagon.append(QPointF(146.,33));
    Heptagon.append(QPointF(117.,-94));
    //start 0,0 radius 150


    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QGraphicsPolygonItem* heptagonItem = new QGraphicsPolygonItem(Heptagon);
    QColor brush_color(Qt::yellow); //fill color
    brush_color.setAlpha(50); // alpha index makes brush color more opaque
    QPen blackpen(Qt::black); //border color
    blackpen.setWidth(2); // border width
    heptagonItem->setBrush(brush_color); // using brush color
    heptagonItem->setPen(blackpen);
    heptagonItem->setFlag(QGraphicsItem::ItemIsMovable); // making the object draggable across graphics view
    heptagonItem->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(heptagonItem);

    QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, heptagonItem); //assigning class name to rectange

    SizeGripItem* heptagonSizeGripItem = new SizeGripItem(new PolygonResizer, heptagonItem); //assigning the new coordinate values to the object
}

void MainWindow::on_pushButton_21_clicked()
{
    //Add Octagon

    QPolygonF Octagon;
    Octagon.append(QPointF(57.,-139));
    Octagon.append(QPointF(-57.,-139));
    Octagon.append(QPointF(-139.,-57));
    Octagon.append(QPointF(-139.,57));
    Octagon.append(QPointF(-57.,139));
    Octagon.append(QPointF(57.,139));
    Octagon.append(QPointF(139.,57));
    Octagon.append(QPointF(139.,-57));
    //start 0,0 radius 150


    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QGraphicsPolygonItem* octagonItem = new QGraphicsPolygonItem(Octagon);
    QColor brush_color(Qt::black); //fill color
    brush_color.setAlpha(50); // alpha index makes brush color more opaque
    QPen blackpen(Qt::black); //border color
    blackpen.setWidth(2); // border width
    octagonItem->setBrush(brush_color); // using brush color
    octagonItem->setPen(blackpen);
    octagonItem->setFlag(QGraphicsItem::ItemIsMovable); // making the object draggable across graphics view
    octagonItem->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(octagonItem);

    QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, octagonItem); //assigning class name to rectange

    SizeGripItem* octagonSizeGripItem = new SizeGripItem(new PolygonResizer, octagonItem); //assigning the new coordinate values to the object
}

void MainWindow::on_pushButton_4_clicked()
{
    //Add class to class file

    bool ok;
       QString text = QInputDialog::getText(this, tr("Add class"),
                                            tr("Desired class name:"), QLineEdit::Normal,"",&ok);
       QString value;

       if (ok && !text.isEmpty())
           value = text;


       QFile file(txtFileStorage);
           if (file.open(QIODevice::Append | QIODevice::Text))
           {
                QTextStream in(&file);

                    if (in.atEnd())
                    {
                        in << endl << value;
                    }
            }

           QStringList stringList; //stringlist for class file data
           QStringListModel *model; // model to store data in

           // Create model
           model = new QStringListModel(this);

           QFile textFile(txtFileStorage);

           if(!textFile.open(QIODevice::ReadOnly))
           {
               QMessageBox::information(0,"Error",textFile.errorString()); // if selecting file is interrupted or read-onl throw error
           }


           QTextStream textStream(&textFile);

           while (true)  // textstream to read from file
           {
               QString line = textStream.readLine();

               if (line.isNull())
                   break;
               else
                   stringList.append(line); // populate the stringlist
                   ui->pushButton_4->setEnabled(true);
           }


           classFileError(stringList);

           model->setStringList(stringList);  // Populate the model

           ui->listView->setModel(model);  // Glue model and view together

        //qDebug() << stringList;


}

void MainWindow::on_pushButton_22_clicked()
{
    //Remove class from class file


    QStringList stringList; //stringlist for class file data
    QStringListModel *model; // model to store data in

    // Create model
    model = new QStringListModel(this);

    QFile textFile(txtFileStorage);

    if(!textFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"Error selecting class, try again!",textFile.errorString()); // if interrupted or read-only throw error
    }


    QTextStream textStream(&textFile);

    while (true)  // textstream to read from file
    {
        QString line = textStream.readLine();

        if (line.isNull())
            break;
        else
            stringList.append(line); // populate the stringlist
            ui->pushButton_4->setEnabled(true);
    }

    QModelIndex index = ui->listView->currentIndex();
    int itemid = index.row();

    //qDebug() << itemid;
    //qDebug() << stringList;

    stringList.removeAt(itemid);

    //qDebug() << stringList;

    QFile file(txtFileStorage);
        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            file.resize(0);
            QTextStream in(&file);

                 if (in.atEnd())
                 {
                     for(int i = 0; i < stringList.count(); ++i)
                     {
                         in << stringList[i] << endl;
                     }
                 }
         }

    classFileError(stringList);

    model->setStringList(stringList);  // Populate the model

    ui->listView->setModel(model);  // Glue model and view together
}

void MainWindow::on_pushButton_23_clicked()
{
    //Sort classes Ascending

    QStringListModel *model; // model to store data in

    // Create model
    model = new QStringListModel(this);

    QStringList stringList;
    QFile textFile(txtFileStorage);

    if(!textFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"Error",textFile.errorString()); // if selecting file is interrupted or read-onl throw error
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

    std::sort(stringList.begin(), stringList.end(),compareNamesAscending); //sorting the string list from beggining to the end in ascending order

    classFileError(stringList);

    model->setStringList(stringList);  // Populate the model

    ui->listView->setModel(model);  // Glue model and view together


}

void MainWindow::on_pushButton_24_clicked()
{
    //Sort classes Descending

    QStringListModel *model; // model to store data in

    // Create model
    model = new QStringListModel(this);

    QStringList stringList;
    QFile textFile(txtFileStorage);

    if(!textFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"Error",textFile.errorString()); // if selecting file is interrupted or read-onl throw error
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

    std::sort(stringList.begin(), stringList.end(),compareNamesAscending); //sorting the string list from beggining to the end in ascending order
    std::reverse(stringList.begin(),stringList.end()); // IMPORTANT this reverses strings into descending order, only change from above code

    classFileError(stringList);

    model->setStringList(stringList);  // Populate the model

    ui->listView->setModel(model);  // Glue model and view together

}

void MainWindow::on_pushButton_clicked()
{
    // Open and load annotation file
    QString annotation = QFileDialog::getOpenFileName(  //open up file browser with QFileDialog
                            this,                         //and assign selected file paths to a QStringList of annotation variable
                            "Select one or more files to open",
                            "/home",                      // default directory
                            "Annotations (*.annotations);;TXT Files(*.txt);;ALL (*.annotations *.txt *.rtf)"); //filetypes elligible

    QFileInfo fi(annotation);
    qDebug() << fi.fileName() << endl; // shows only file name

    ui->label_4->setText(fi.fileName()); // chnaging qlabel to name of annotation file

    qDebug()<< "reading ...";
           QFile fileIn(annotation);
           if(fileIn.open(QIODevice::ReadOnly)){
               QDataStream in(&fileIn);
               QList<QGraphicsItem *> items = readItems(in);
               std::reverse(items.begin(),items.end());
               for(QGraphicsItem *item : items){
                   scene->addItem(item);

//                   QGraphicsEllipseItem* elitem = dynamic_cast<QGraphicsEllipseItem*>(item);
//                     if (elitem) {  // if its not NULL it means it was a QGraphicsEllipseItem.

//                         SizeGripItem* ellipseSizeGripItem = new SizeGripItem(new EllipseResizer, item);

//                     }
//                   QGraphicsRectItem* rectitem = dynamic_cast<QGraphicsRectItem*>(item);
//                       if (rectitem) {  // if its not NULL it means it was a QGraphicsEllipseItem.

//                           SizeGripItem* rectSizeGripItem = new SizeGripItem(new RectResizer, item);

//                       }
//                   QGraphicsPolygonItem* polygonitem = dynamic_cast<QGraphicsPolygonItem*>(item);
//                        if (polygonitem) {  // if its not NULL it means it was a QGraphicsEllipseItem.

//                            QPolygonF thesize = polygonitem->polygon();
//                            QPen pen = polygonitem->pen();
//                            QBrush brush = polygonitem->brush();
//                            QGraphicsPolygonItem* item3 = new QGraphicsPolygonItem(QPolygonF(thesize));
//                            item3->setBrush(brush); // using brush color
//                            item3->setPen(pen);
//                            item3->setPolygon(thesize);

//                           SizeGripItem* polygonSizeGripItem = new SizeGripItem(new PolygonResizer, item);

//                       }

               }
           }


}

void MainWindow::on_pushButton_3_clicked()
{
    //Change name of annotation file

    QString annotation = QFileDialog::getOpenFileName(  //open up file browser with QFileDialog
                            this,                         //and assign selected file paths to a QStringList of annotation variable
                            "Select a file to rename",
                            "/home",                      // default directory
                            "Annotations (*.annotations);;TXT Files(*.txt);;ALL (*.annotations *.txt *.rtf)"); //filetypes elligible



    bool ok;
    QString newAnnotationFileName = QInputDialog::getText(this, tr("Name your annotation file"),
                                         tr("Desired annotation file name(include file type, eg. .annotations, .txt):"), QLineEdit::Normal,"",&ok);

    QString isCorrectName;

    if (ok && !newAnnotationFileName.isEmpty())
    {
       isCorrectName = newAnnotationFileName;
    }



    QFileInfo fi(annotation); // turn filepath string into usable filo info type
    QString path = fi.absolutePath(); //get path without file name
    //qDebug() << path;
    QFile::copy(annotation,path + "/" + isCorrectName ); //copy initial file into new file

    QFile file (annotation); //select and delete old file after copy is finished
    file.remove();

}

void MainWindow::on_pushButton_2_clicked()
{
    //Save annotation file

   bool ok;
   QString annotationFileName = QInputDialog::getText(this, tr("Name your annotation file"),
                                        tr("Desired annotation file name(include file type, eg. .annotations, .txt):"), QLineEdit::Normal,"",&ok);
   QString isCorrectName;

   if (ok && !annotationFileName.isEmpty())
   {
      isCorrectName = annotationFileName;
   }


   qDebug()<< "writing ...";
   QFile fileOut(isCorrectName);

   QString changeName;

   if(fileOut.exists())
   {
       changeName = QInputDialog::getText(this, tr("File name exists, overwrite?"),
                                            tr("File name already exists, do you wish to overwrite it with new data? (y/n)"), QLineEdit::Normal,"",&ok);
   }

   if(changeName == "" || changeName  == "y" || changeName  == "Y")
   {
       qDebug() << "alrighty";
   }

   if(changeName == "n" || changeName  == "N" )
   {
       QMessageBox msgBox;
       msgBox.setText("Info");
       msgBox.setInformativeText("Operation has been aborted, your file has not been saved, please attempt to save the file under different name");
       msgBox.exec();
       return;
   }



   if(fileOut.open(QIODevice::WriteOnly))
   {
        QDataStream out(&fileOut);
        saveItems(scene->items(), out);
        fileOut.close();
        qDebug()<<"items saved";
   }


}

void MainWindow::on_pushButton_6_clicked()
{
    //Copy and paste most reccent shape
    QList <QGraphicsItem* >listCopiedItems =  scene->selectedItems();
    qDebug() << listCopiedItems;

    if (listCopiedItems.size() == 0 ) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","You have not selected a shape! Please click on a shape to select it");
        messageBox.setFixedSize(500,200);
        return;
      }

      QGraphicsItem* item = listCopiedItems.first();

      QGraphicsEllipseItem* elitem = dynamic_cast<QGraphicsEllipseItem*>(item);
        if (elitem) {  // if its not NULL it means it was a QGraphicsEllipseItem.
            QModelIndex index = ui->listView->currentIndex();
            QString itemText = index.data(Qt::DisplayRole).toString();


            QRectF thesize = elitem->rect();
            QPen pen = elitem->pen();
            QBrush brush = elitem->brush();
            QGraphicsEllipseItem* item1 = new QGraphicsEllipseItem(QRectF(thesize));
            item1->setBrush(brush); // using brush color
            item1->setPen(pen);
            item1->setRect(thesize);
            item1->setFlag(QGraphicsItem::ItemIsMovable);
            item1->setFlag(QGraphicsItem::ItemIsSelectable);

            scene->addItem(item1);

            QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, item1); //assigning class name to rectangle

            SizeGripItem* rect2SizeGripItem = new SizeGripItem(new EllipseResizer, item1);
          return; // leave
        }

        QGraphicsRectItem* rectitem = dynamic_cast<QGraphicsRectItem*>(item);
        if (rectitem) {  // if its not NULL it means it was a QGraphicsRectItem.
            QModelIndex index = ui->listView->currentIndex();
            QString itemText = index.data(Qt::DisplayRole).toString();


            QRectF thesize = rectitem->rect();
            QPen pen = rectitem->pen();
            QBrush brush = rectitem->brush();
            QGraphicsRectItem* item2 = new QGraphicsRectItem(QRectF(thesize));
            item2->setBrush(brush); // using brush color
            item2->setPen(pen);
            item2->setRect(thesize);
            item2->setFlag(QGraphicsItem::ItemIsMovable);
            item2->setFlag(QGraphicsItem::ItemIsSelectable);

            scene->addItem(item2);

            QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, item2); //assigning class name to rectangle

            SizeGripItem* rect2SizeGripItem = new SizeGripItem(new RectResizer, item2);
          return;
        }

        QGraphicsPolygonItem* polyitem = dynamic_cast<QGraphicsPolygonItem*>(item);
        if (polyitem) {  // if its not NULL it means it was a QGraphicsRectItem.
            QModelIndex index = ui->listView->currentIndex();
            QString itemText = index.data(Qt::DisplayRole).toString();

            QPolygonF thesize = polyitem->polygon();
            QPen pen = polyitem->pen();
            QBrush brush = polyitem->brush();
            QGraphicsPolygonItem* item3 = new QGraphicsPolygonItem(QPolygonF(thesize));
            item3->setBrush(brush); // using brush color
            item3->setPen(pen);
            item3->setPolygon(thesize);
            item3->setFlag(QGraphicsItem::ItemIsMovable);
            item3->setFlag(QGraphicsItem::ItemIsSelectable);

            scene->addItem(item3);

            QGraphicsTextItem *RectText = new QGraphicsTextItem(itemText, item3); //assigning class name to rectangle

            SizeGripItem* polySizeGripItem = new SizeGripItem(new PolygonResizer, item3);
          return;
        }

}

void MainWindow::on_pushButton_9_clicked()
{
    //clear scene button
    scene->clear();
}

void MainWindow::on_pushButton_8_clicked()
{
    //Delete shape button

    //Copy and paste most reccent shape
    QList <QGraphicsItem* >listCopiedItems =  scene->selectedItems();
    qDebug() << listCopiedItems;

    if (listCopiedItems.size() == 0 ) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","You have not selected a shape! Please click on a shape to select it");
        messageBox.setFixedSize(500,200);
        return;
      }

    QGraphicsItem* item = listCopiedItems.first();

    scene->removeItem(item);
}

void MainWindow::on_pushButton_25_clicked()
{
    QList <QGraphicsItem* >listCopiedItems =  scene->selectedItems();
    qDebug() << listCopiedItems;

    if (listCopiedItems.size() == 0 ) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","You have not selected a shape! Please click on a shape to select it");
        messageBox.setFixedSize(500,200);
        return;
      }

    QGraphicsItem* item = listCopiedItems.first();

    QSpinBox spinBox;

    int deg = ui->spinBox->value();

    item->setRotation(item->rotation() + deg);
}
