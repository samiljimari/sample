 #include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class test1 : public QObject
{
    Q_OBJECT

public:
    test1();
    ~test1();

private slots:
    void test_case1();

private:

    QPixmap image;
    QImage  *imageObject;
    QObject sender;
    QStringList *model;

};




test1::test1()
{

}

test1::~test1()
{

}

class test2: public QObject
{
    Q_OBJECT

public:
    test2();
    ~test2();
};

//SEARCH TEST

void test1::test_case1()
{
    QStringList stringList;
    QString *model;
    // Linked list declared and assigned 3 images.
    QList<QString> Images = {"C:/Users/Alceu Caterca/Documents/WORK!!!/Software Design and Implemenation/Images/bird","C:/Users/Alceu Caterca/Documents/WORK!!!/Software Design and Implemenation/Images/De sousa","C:/Users/Alceu Caterca/Documents/WORK!!!/Software Design and Implemenation/Images/Palanca Negra"};

   //
    model->setStringList(Images); // fill the model with file paths that user has selected

    ui->ListWidget->addItems(Images); // display users selection


   //Check if
   EXPECT_Q(Images, ListWidget);



}

// TESTING LINKED LIST

void test2::test_case2()
{

// MAKE A LINKED List
    QStringListModel *model = new QstringListModel()


    QList<QString> list = {"C:/Users/Alceu Caterca/Pictures/Kante","C:/Users/Alceu Caterca/Pictures/Palanca Negra","C:/Users/Alceu Caterca/Pictures/De sousa"};
    model->setstringlist(list)
   // ADD ITEMS TO Linked QList

    EXPECT_Q(3, model.size())
    // Check if number of items in the linked list is equal to 3.


}

// SORT TEST



// CLASS SELECTOR TEST
void test3::test_case3()
{
    QStringList StringList;
    QString *model;

    // Linked list declared and assigned 3 images.
    QList<QString> Class = {"C:/Users/Alceu Caterca/Documents/WORK!!!/Software Design and Implemenation/Classes/Bird"};

   //
    model->setStringList(Class); // fill the model with file paths that user has selected

    ui->ListView->setModel(Class); // Join Model and View Together


   //Check if Selected Class is equal to the one displayed on ListView
   EXPECT_Q(Class, ListView);



}



// ADD AND REMOVE CLASS


//SHAPE SELECTION




QTEST_MAIN(test1)

#include "tst_test1.moc"
