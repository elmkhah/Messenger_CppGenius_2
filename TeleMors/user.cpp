#include "user.h"

User::User(QString _username, bool _determination, QString _password, QString _token)
{
    username=_username;
    determination=_determination;
    password=_password;
    token=_token;
}

QString User::getToken()
{
    return token;
}

QString User::getUsername()
{
    return username;
}

QString User::getPassword()
{
    return password;
}

bool User::getDetermination()
{
    return determination;
}
