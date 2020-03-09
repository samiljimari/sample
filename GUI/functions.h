#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QListWidget>
#include <QList>
#include <iostream>
#include <QTextStream>
#include <QMessageBox>


QString listTraversal(QList <QListWidgetItem*> items, QString list)
{
    for(int j=0;j<items.count();j++)
    {
        list = items.at(j)->text();
    }
    return list;
}

void errorMessage(QFile textFile) // displays error if class file selection is aborted
{
    if(!textFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"Error",textFile.errorString());
    }
}

QStringList populateList(QStringList stringList, QTextStream textStream) // function to populate a list of class file contents
{
    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            stringList.append(line); // populate the stringlist
    }
    return stringList;
}

void classFileError(QStringList stringList)
{
    if (stringList.size() == 0) // error message to prompt user if a empty class file is selcted
    {
        QMessageBox::warning(0,("class file explorer"),("This file is empty, select a different one"));
    }
}

#endif // FUNCTIONS_H


