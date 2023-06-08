#include "message.h"


Message::Message(const User & _sender, const Date & _sentDate, QString _messageBody)
{
    sender=_sender;
    sentDate=_sentDate;
    messageBody=_messageBody;
}

QString Message::getMessageBody() const
{
    return messageBody;
}

User Message::getSender() const
{
    return sender;
}

Date Message::getSentDate() const
{
    return sentDate;
}
