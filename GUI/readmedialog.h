#ifndef READMEDIALOG_H
#define READMEDIALOG_H

#include <QDialog>

namespace Ui {
class readmeDialog;
}

class readmeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit readmeDialog(QWidget *parent = nullptr);
    ~readmeDialog();

private:
    Ui::readmeDialog *ui;
};

#endif // READMEDIALOG_H
