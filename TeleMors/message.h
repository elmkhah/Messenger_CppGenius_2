#ifndef MESSAGE_H
#define MESSAGE_H
#include<QString>
#include "date.h"
#include "user.h"

class Message
{
public:
    Message(const User&,const Date&,QString);
    QString getMessageBody()const;
    User getSender()const;
    Date getSentDate()const;
private:
    QString messageBody;
    User sender;
    Date sentDate;
};

#endif // MESSAGE_H
