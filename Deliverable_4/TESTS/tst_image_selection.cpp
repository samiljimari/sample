#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class Image_Selection : public QObject
{
    Q_OBJECT

public:
    Image_Selection();
    ~Image_Selection();

private slots:
    void test_case1();

};

Image_Selection::Image_Selection()
{

}

Image_Selection::~Image_Selection()
{

}

void Image_Selection::test_case1()
{
    QStringList StringList;
    QString *model;
    // Linked list declared and assigned 3 images.
    QList<QString> Images = {"C:/Users/Alceu Caterca/Documents/WORK!!!/Software Design and Implemenation/Images/bird","C:/Users/Alceu Caterca/Documents/WORK!!!/Software Design and Implemenation/Images/De sousa","C:/Users/Alceu Caterca/Documents/WORK!!!/Software Design and Implemenation/Images/Palanca Negra"};

   //
    model->setStringList(Images); // fill the model with file paths that user has selected

    ui->ListWidget->addItems(Images); // display users selection


   //Check if
   EXPECT_Q(Images, ListWidget);


}

QTEST_MAIN(Image_Selection)

#include "tst_image_selection.moc"
