/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <vector>

#include <QString>

class FileParser
{
public:
    static std::vector<QString> readFile(QString filePath);
    static void writeFile(std::vector<QString> content);
};

#endif // FILEPARSER_H
