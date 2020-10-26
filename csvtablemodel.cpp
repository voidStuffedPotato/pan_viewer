#include <QFile>
#include "csvtablemodel.hpp"

CSVTableModel::CSVTableModel(QObject *parent)
    : QAbstractTableModel(parent) { }

QVariant CSVTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QStringLiteral("Name");
        case 1:
            return QStringLiteral("Age");
        case 2:
            return QStringLiteral("Address");
        default:
            return QVariant();
        }
    } else return QStringLiteral("Row %1").arg(section);

}

bool CSVTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    return false;
}


int CSVTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return table.size();
}

int CSVTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant CSVTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > rowCount() || index.column() > columnCount())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {

        auto &row = table[index.row()];

        switch (index.column()) {
        case 0:
            return row.name;
        case 1:
            return QStringLiteral("%1").arg(row.age);
        case 2:
            return row.address;
        }
    }
    return QVariant();
}

bool CSVTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() > table.size() || index.column() > 3)
        return false;

    if (data(index, role) != value) {
        auto &row = table[index.row()];
        bool ok;
        int val;

        switch (index.column()) {
        case 0:
            row.name = value.toString();
            break;
        case 1:
            val = value.toInt(&ok);
            if (ok)
                row.age = val;
            break;
        case 2:
            row.address = value.toString();
            break;
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CSVTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (index.row() < rowCount() && index.column() < columnCount())
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    return Qt::ItemIsEditable;
}

bool CSVTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    if (row != rowCount()) {
        endInsertRows();
        return false;
    }
    for (int i = 0; i < count; ++i)
        table[row + i] = Person{};
    endInsertRows();
    return true;
}

bool CSVTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    /*
     * This is very slow.
     * I'd use QLinkedList for
     * constant-time random additions and deletions.
     */
    auto copy = table;
    for (int i = row; i != table.size(); ++i)
        copy.remove(i);

    qDebug() << QString("table size before:%1").arg(table.size());
    qDebug() << "I am here";

    for (int i = row + count, j = row; i < table.size(); ++i, ++j) {
        copy[j] = table[i];
    }
    table = copy;

    qDebug() << QString("table size before:%1").arg(table.size());

    endRemoveRows();
    return true;
}

bool CSVTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    return false;
}

bool CSVTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    return false;
}

bool CSVTableModel::loadFromFile(const QString &filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    table.clear();

    QTextStream in(&file);
    for (int i = 0; !in.atEnd(); ++i) {
        QString line = in.readLine();
        table[i] = Person::fromCSV(line);
    }
    emit layoutAboutToBeChanged();
    emit layoutChanged();
    return true;
}

bool CSVTableModel::dumpToFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&file);

    QHashIterator<int, Person> it(table);
    while (it.hasNext()) {
        it.next();
        out << it.value().toCSV() << '\n';
    }
    return true;
}
