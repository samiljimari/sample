#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class Linked_List_Test : public QObject
{
    Q_OBJECT

public:
    Linked_List_Test();
    ~Linked_List_Test();

private slots:
    void test_case1();

};

Linked_List_Test::Linked_List_Test()
{

}

Linked_List_Test::~Linked_List_Test()
{

}

void Linked_List_Test::test_case1()
{
    // MAKE A LINKED List
        QStringListModel *model = new QstringListModel()


        QList<QString> list = {"C:/Users/Alceu Caterca/Pictures/Kante","C:/Users/Alceu Caterca/Pictures/Palanca Negra","C:/Users/Alceu Caterca/Pictures/De sousa"};
        model->setstringlist(list)
       // ADD ITEMS TO Linked QList

        EXPECT_Q(3, model.size())
        // Check if number of items in the linked list is equal to 3.


}

QTEST_MAIN(Linked_List_Test)

#include "tst_linked_list_test.moc"
