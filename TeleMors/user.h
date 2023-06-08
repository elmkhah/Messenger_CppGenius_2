#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User(QString,bool,QString=0,QString=0);
    QString getToken();
    QString getUsername();
    QString getPassword();
    bool getDetermination();
private:
    QString token;
    QString username;
    QString password;
    bool determination;
};

#endif // USER_H
