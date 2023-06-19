#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User()=default;
    User(QString,bool=0,QString=0,QString=0);
    User(const User&)=default;
    void setToken(QString);
    QString getToken()const;
    QString getUsername()const;
    QString getPassword()const;
    bool getDetermination()const;
private:
    QString token;
    QString username;
    QString password;
    bool determination;
};

#endif // USER_H
