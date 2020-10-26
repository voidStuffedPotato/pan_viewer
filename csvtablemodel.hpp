#ifndef CSVTABLEMODEL_HPP
#define CSVTABLEMODEL_HPP

#include <QAbstractTableModel>
#include "person.hpp"
#include <QDebug>

class CSVTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CSVTableModel(QObject *parent = nullptr);

    bool loadFromFile(const QString &filename);

    bool dumpToFile(const QString &filename);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QHash<int, Person> table;
};

#endif // CSVTABLEMODEL_HPP
