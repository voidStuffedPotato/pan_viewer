#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include "person.hpp"
#include "tablereader.hpp"

TableReader::TableReader(const QString &filename, QObject *parent)
    : QObject(parent) , _filename(filename) {}

bool TableReader::read(QHash<int, Person> &target)
{
    QFile file(_filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    target.clear();

    QTextStream in(&file);
    qDebug() << "here" << '\n';
    for (int i = 0; !in.atEnd(); ++i) {
        QString line = in.readLine();
        target[i] = Person::fromCSV(line);
        qDebug() << target[i].toCSV() << '\n';
    }

    return true;
}
