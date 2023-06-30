#include "date.h"

Date::Date(QString _rowDate)
{
    year=_rowDate.mid(0,4);
    mounth=_rowDate.mid(5,2);
    day=_rowDate.mid(8,2);
    hour=_rowDate.mid(11,2);
    minute=_rowDate.mid(14,2);
    second=_rowDate.mid(17,2);
    rowDate+=year+mounth+day+hour+minute+second;
}

Date::Date(int size, QString _rowDate)
{
    year=_rowDate.mid(0,4);
    mounth=_rowDate.mid(4,2);
    day=_rowDate.mid(6,2);
    hour=_rowDate.mid(8,2);
    minute=_rowDate.mid(10,2);
    second=_rowDate.mid(12,2);
    rowDate+=year+mounth+day+hour+minute+second;
}

QString Date::getRowDate()const
{
    return rowDate;
}
QString Date::getHourMinute()const{
    QString _hour=rowDate.mid(8,2);
    QString _minute=rowDate.mid(10,2);
    QString resualt=_hour+ ":" + _minute;
    return resualt;
}

void Date::setRowDate(QString _rowDate)
{
    rowDate=_rowDate;
}

QString Date::getCurrentTime()
{
    QDateTime localDateTime = QDateTime::currentDateTime();
    QDateTime utcDateTime = localDateTime.toUTC();
    QString utcDateTimeString = utcDateTime.toString("yyyy-MM-dd hh:mm:ss");
    return utcDateTimeString;
}
