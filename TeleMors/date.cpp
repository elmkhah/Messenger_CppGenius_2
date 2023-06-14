#include "date.h"

Date::Date(QString _rowDate)
{
    rowDate=_rowDate;
    year=rowDate.mid(0,4);
    mounth=rowDate.mid(5,2);
    day=rowDate.mid(8,2);
    hour=rowDate.mid(11,2);
    minute=rowDate.mid(14,2);
    second=rowDate.mid(17,2);
    rowDate+=year+mounth+day+hour+minute+second;
}

QString Date::getRowDate()const
{
    return rowDate;
}
QString Date::getHourMinute()const{
    return hour+":"+minute;
}
