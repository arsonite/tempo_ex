#include "fileparser.h"

#include <QDir>
#include <QDebug>
#include <QApplication>

FileParser::FileParser()
{

}

QString FileParser::readFile()
{
    QDir dir(QDir::currentPath());
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();

    QString filename = dir.relativeFilePath("/TempoEX/config.xml");
    QFile file(filename);
    QString fileContent = "";

    QTextStream in(&file);
    if(file.open(QIODevice::ReadWrite)) {
        while(!in.atEnd()) {
            QString line = in.readLine();
            fileContent += line;
        }
    }
    qDebug() << fileContent;

    /*if(file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "<config>" << endl << "</config>" << endl;
    }*/
}
