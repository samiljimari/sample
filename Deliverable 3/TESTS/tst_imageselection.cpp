#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class ImageSelection : public QObject
{
    Q_OBJECT

public:
    ImageSelection();
    ~ImageSelection();

private slots:
    void test_case1();

};

ImageSelection::ImageSelection()
{

}

ImageSelection::~ImageSelection()
{

}

void ImageSelection::test_case1()
{

}

QTEST_MAIN(ImageSelection)

#include "tst_imageselection.moc"
