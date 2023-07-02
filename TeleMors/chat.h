#ifndef CHAT_H
#define CHAT_H
#include<message.h>
#include <myfile.h>
class Chat
{
private:
    QString name;
    QString type;
    QString last;
public:
    friend class FetchThread;
    friend class MainWindow;
    friend class MessageThread;
    Chat(QString,QString);
    QString show();
    void update();
};

#endif // CHAT_H
