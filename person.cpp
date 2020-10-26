#include "person.hpp"

Person Person::fromCSV(const QString &str)
{
    QRegularExpression re;
    re.setPattern("(?:^|,)(?=[^\"]|(\")?)\"?((?(1)[^\"]*|[^,\"]*))\"?(?=,|$)");
    auto iter = re.globalMatch(str);

    QStringList words;
    while (iter.hasNext()) {
        auto match = iter.next();
        QString word = match.captured(2);
        words << word;
    }

    if (words.size() > 2)
        return { words[0], words[1].toInt(), words[2] };
    else
        return {};
}

QString Person::toCSV() const
{
    return QString("%1,%2,%3").arg(escape_commas(name)).arg(age).arg(escape_commas(address));
}
