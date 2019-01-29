/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#include "fileparser.h"

#include <QDir>
#include <QDebug>
#include <QApplication>

std::vector<QString> FileParser::readFile(QString filePath)
{
    QFile file(filePath);
    QString fileContent = "";

    QTextStream in(&file);
    // TODO: Umwandeln in map
    std::vector<QString> arr;
    arr.reserve(3);
    if(file.open(QIODevice::ReadOnly)) {
        while(!in.atEnd()) {
            QString content = in.readLine();
            content = content.remove(QRegExp("^.*:\\s+")).remove(";");
            arr.push_back(content);
        }
    }
    return arr;

    /*if(file.open(QIODevice::ReadWrite)) {
        while(!in.atEnd()) {
            QString line = in.readLine();
            fileContent += line;
        }
    }
    qDebug() << fileContent;

    if(file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "<config>" << endl << "</config>" << endl;
    }*/
}

void FileParser::writeFile(std::vector<QString> content)
{

}
