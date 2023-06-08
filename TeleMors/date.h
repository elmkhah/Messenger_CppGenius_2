#ifndef DATE_H
#define DATE_H
#include<QString>

class Date
{
public:
    Date(QString);
    QString getRowDate();
    QString getHourMinute();
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
