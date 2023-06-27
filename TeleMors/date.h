#ifndef DATE_H
#define DATE_H
#include<QString>
#include <QDateTime>
#include<QTimeZone>
class Date
{
public:
    Date()=default;
    Date(QString);
    Date(const Date&)=default;
    QString getRowDate()const;
    QString getHourMinute()const;
    void setRowDate(QString);
    QString getCurrentTime();
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
