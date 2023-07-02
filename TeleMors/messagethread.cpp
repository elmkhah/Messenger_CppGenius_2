#include "messagethread.h"

MessageThread::MessageThread(MainWindow*s,QObject *parent)
    : QObject{parent}
{
    e=s;

}

void MessageThread::run()
{
    QString name;
    int res,res2,res3,res4;
    int currentGroup,currentChannel,currentPv;
    int currentSum;
    int lastSum = 0;

    int lastGroup=0;
    int lastChannel=0;
    int lastPv=0;
    MyFile c1;
    QString lastMessage="";
    QString type;
    QString currentMessage;
    Request c;


    connect(this,SIGNAL(sig_Message(QString)),e,SLOT(get_fetchSignal(QString)));
    QString lo;

    QVector<QString> group;
    QVector<QString> channel;
    QVector<QString> pv;
    QVector<Chat>chat;
    bool invalid;
    int i;
    while(true){
        chat.empty();
        group.empty();
        channel.empty();
        pv.empty();
            group=c1.readChats("group");
            channel=c1.readChats("channel");
            pv=c1.readChats("private");

            for(i=0;i<group.size();i++)
             chat.push_back(Chat("group",group[i]));
            for(i=0;i<channel.size();i++)
             chat.push_back( Chat("channel",channel[i]));
            for(i=0;i<pv.size();i++)
             chat.push_back( Chat("private",pv[i]));


            currentSum=0;
            for(i=0;i<chat.size();i++){

             type = chat[i].type;
             name = chat[i].name;
             if(c1.existChats(type,name)&&c1.readNumberOfMessage(type,name)!=0){
                 res=c.getChatMessages(c1.getToken(),type,name,c1.getTimeLastMessage(type,name));
             }
             else{
                 res=c.getChatMessages(c1.getToken(),type,name);
             }
             if (res!=200)
                 invalid = true;
             currentSum += c1.readNumberOfMessage(type, name);
            }
            if(currentSum!=lastSum)
             emit sig_Message("chat");
            if(!invalid)
             lastSum=currentSum;


    }
}

void MessageThread::getFetch(bool a)
{
    chatSignal=a;
}
