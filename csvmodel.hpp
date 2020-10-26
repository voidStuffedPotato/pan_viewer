#ifndef CSVMODEL_HPP
#define CSVMODEL_HPP

#include <QObject>

class CsvModel : public QObject
{
    Q_OBJECT
public:
    explicit CsvModel(QString &filename, QObject *parent = nullptr);

signals:

private:
    QString _filename;

};

#endif // CSVMODEL_HPP
