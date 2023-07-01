#include "fetchthread.h"
#include<QDebug>
#include<request.h>
#include<mainwindow.h>
#include<chat.h>
#include<QCoreApplication>
FetchThread::FetchThread(MainWindow* s,QObject *parent)
    : QObject{parent}
{
    e=s;
}

void FetchThread::run()
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


    QFile active(QDir::currentPath()+"/active.txt");
    connect(this,SIGNAL(sig_fetch(QString)),e,SLOT(get_fetchSignal(QString)));
    QString lo;

    QVector<QString> group;
    QVector<QString> channel;
    QVector<QString> pv;
    QVector<Chat>chat;
    bool invalid;
    int i;

    while(1)
    {
        group.empty();
        channel.empty();
        pv.empty();
        chat.empty();

           QFile isLogin(QDir::currentPath()+"/information/isLogin.txt");
           if (isLogin.open(QIODevice::ReadOnly | QIODevice::Text)){
             QTextStream in(&isLogin);
             in>>lo;
             isLogin.close();
           }
           if (lo=="0")
             continue;



           res2=c.getChatList(c1.getToken(),"group");

           res3=c.getChatList(c1.getToken(),"channel");

           res4=c.getChatList(c1.getToken(),"private");




           currentGroup=c1.readNumberOfChats("group");
           currentChannel=c1.readNumberOfChats("channel");
           currentPv=c1.readNumberOfChats("private");

           bool chatSignal = false;

        if(currentGroup!=lastGroup){
           emit sig_fetch("chat");
             chatSignal = true;
        }
        else if(currentChannel!=lastChannel) {
         emit sig_fetch("chat");
             chatSignal = true;
        }
        else if(currentPv!=lastPv){
           emit sig_fetch("chat");
             chatSignal = true;
        }

        if(res2==200)
         lastGroup=currentGroup;
        if(res3==200)
         lastChannel=currentChannel;
        if(res4==200)
         lastPv=currentPv;
///////////////////////////////////////////////////////////////////////////////////
        if(active.open(QIODevice::ReadOnly|QIODevice::Text)){
           QTextStream in(&active);
           in>>name>>type;

           active.close();
        }

        if (name=="")
           continue;

        if(c1.existChats(type,name)){
         qDebug()<<"time";
         res=c.getChatMessages(c1.getToken(),type,name,c1.getTimeLastMessage(type,name));
        }
        else{
         qDebug()<<"All";
         res=c.getChatMessages(c1.getToken(),type,name);
        }
        currentMessage=c1.getTimeLastMessage(type,name);
        if(currentMessage!=lastMessage)
         emit sig_fetch("message");
        if(res==200)
         lastMessage=currentMessage;

///////////////////////////////////////////////////////////////////////////////////


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
         if(c1.existChats(type,name)){
             res=c.getChatMessages(c1.getToken(),type,name,c1.getTimeLastMessage(type,name));
         }
         else{
             res=c.getChatMessages(c1.getToken(),type,name);
         }
         if (res!=200)
             invalid = true;
         currentSum += c1.readNumberOfMessage(type, name);
        }
        if(currentSum!=lastSum && !chatSignal)
         emit sig_fetch("chat");
        if(!invalid)
         lastSum=currentSum;

    }
}
