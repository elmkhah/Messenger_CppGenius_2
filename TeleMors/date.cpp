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

QString Date::getRowDate()const
{
    return rowDate;
}
QString Date::getHourMinute()const{
    return hour+":"+minute;
}
