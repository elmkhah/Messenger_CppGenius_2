#include "chat.h"

Chat::Chat(QString _type,QString _name)
{
    name=_name;
    type=_type;
}

QString Chat::show()
{
    return type+":"+name;
}
