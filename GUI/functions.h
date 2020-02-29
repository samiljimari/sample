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

void errorMessage(QFile textFile)
{
    if(!textFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"Error",textFile.errorString());
    }
}

QStringList populateList(QStringList stringList, QTextStream textStream)
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

#endif // FUNCTIONS_H


