#ifndef PERSON_HPP
#define PERSON_HPP

#include <QString>
#include <QRegularExpression>

struct Person
{
    Person() = default;
    Person(const QString &name, const int &age, const QString &address)
        : name(name), age(age), address(address) { }

    static Person fromCSV(const QString &str);
    QString toCSV() const;

    QString name;
    int age = 0;
    QString address;
};

inline QString escape_commas(QString target)
{
    return target.contains(',') ? (target.prepend('"').append('"')) : target;
}

#endif // PERSON_HPP
