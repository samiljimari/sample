#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QListWidget>
#include <QList>
#include <iostream>

QString listTraversal(QList <QListWidgetItem*> items, QString list)
{
    for(int j=0;j<items.count();j++)
    {
        list = items.at(j)->text();
    }
    return list;
}

#endif // FUNCTIONS_H


