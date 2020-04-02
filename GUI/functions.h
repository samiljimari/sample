#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QListWidget>
#include <QList>
#include <iostream>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>


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

bool compareNamesAscending(const QString& s1,const QString& s2)
{
    // ignore common prefix..
    int i = 0;
    while ((i < s1.length()) && (i < s2.length()) && (s1.at(i).toLower() == s2.at(i).toLower()))
        ++i;
    ++i;
    // something left to compare?
    if ((i < s1.length()) && (i < s2.length()))
    {
        // get number prefix from position i - doesnt matter from which string
        int k = i-1;
        //If not number return native comparator
        if(!s1.at(k).isNumber() || !s2.at(k).isNumber())
        {
            //Two next lines
            //E.g. 1_... < 12_...
            if(s1.at(k).isNumber())
                return false;
            if(s2.at(k).isNumber())
                return true;
            return QString::compare(s1, s2, Qt::CaseSensitive) < 0;
        }
        QString n = "";
        k--;
        while ((k >= 0) && (s1.at(k).isNumber()))
        {
            n = s1.at(k)+n;
            --k;
        }
        // get relevant/signficant number string for s1
        k = i-1;
        QString n1 = "";
        while ((k < s1.length()) && (s1.at(k).isNumber()))
        {
            n1 += s1.at(k);
            ++k;
        }

        // get relevant/signficant number string for s2
        //Decrease by
        k = i-1;
        QString n2 = "";
        while ((k < s2.length()) && (s2.at(k).isNumber()))
        {
            n2 += s2.at(k);
            ++k;
        }

        // got two numbers to compare?
        if (!n1.isEmpty() && !n2.isEmpty())
            return (n+n1).toInt() < (n+n2).toInt();
        else
        {
            // not a number has to win over a number.. number could have ended earlier... same prefix..
            if (!n1.isEmpty())
                return false;
            if (!n2.isEmpty())
                return true;
            return s1.at(i) < s2.at(i);
        }
    }
    else
    {
        // shortest string wins
        return s1.length() < s2.length();
    }
}

#endif // FUNCTIONS_H


