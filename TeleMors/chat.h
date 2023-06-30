#ifndef CHAT_H
#define CHAT_H
#include<message.h>

class Chat
{
private:
    QString name;
    QString type;
    QString last;
public:
    friend class FetchThread;
    friend class MainWindow;
    Chat(QString,QString);
    QString show();
    void update();
};

#endif // CHAT_H
