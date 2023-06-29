#ifndef CHAT_H
#define CHAT_H
#include<message.h>

class Chat
{
private:
    QString name;
    QString type;
public:
    Chat(QString,QString);
    QString show();
};

#endif // CHAT_H
