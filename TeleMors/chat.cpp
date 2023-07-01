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

void Chat::update()
{
    MyFile c1;
    last = c1.getTimeLastMessage(type,name);
}
