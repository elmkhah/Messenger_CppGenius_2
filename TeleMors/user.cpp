#include "user.h"

User::User(QString _username, bool _determination, QString _password, QString _token)
{
    username=_username;
    determination=_determination;
    password=_password;
    token=_token;
}

QString User::getToken()const
{
    return token;
}

QString User::getUsername()const
{
    return username;
}

QString User::getPassword()const
{
    return password;
}

bool User::getDetermination()const
{
    return determination;
}
