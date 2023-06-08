#ifndef DATE_H
#define DATE_H
#include<QString>

class Date
{
public:
    Date()=default;
    Date(QString);
    QString getRowDate()const;
    QString getHourMinute()const;
private:
    QString rowDate;
    QString year;
    QString mounth;
    QString day;
    QString hour;
    QString minute;
    QString second;
};

#endif // DATE_H
