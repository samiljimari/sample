#ifndef README_H
#define README_H
#include <QListWidget>
#include <QList>
#include <iostream>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QDataStream>
#include <QFont>
#include <QGraphicsLineItem>
#include <QPen>

QString Read(QString Filename)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        return "File not found";
    }
    QTextStream in(&mFile);
    QString mText = in.readAll();

    mFile.close();
    return mText;
}


#endif // README_H
