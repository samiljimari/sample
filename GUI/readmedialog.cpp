#include "readmedialog.h"
#include "ui_readmedialog.h"
#include "readme.h"


readmeDialog::readmeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readmeDialog)
{
    ui->setupUi(this);
    QString x = Read(":/rec/readme.txt");
    ui->textBrowser->append(x);
}

readmeDialog::~readmeDialog()
{
    delete ui;
}
