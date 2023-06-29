#include "fetchthread.h"
#include<QDebug>
#include<request.h>
#include<mainwindow.h>
FetchThread::FetchThread(MainWindow* s,QObject *parent)
    : QObject{parent}
{
    e=s;
}

void FetchThread::run()
{
            QString name;
    int res;
                MyFile c1;
    QString lastMessage="";
                  QString type;
            QString currentMessage;
    Request c;

            bool signalOutput;


    QFile active(QDir::currentPath()+"/active.txt");
    connect(this,SIGNAL(sig_fetch()),e,SLOT(get_fetchSignal()));
    while(1)
    {

        if(active.open(QIODevice::ReadOnly|QIODevice::Text)){
              QTextStream in(&active);
            in>>name>>type;

             active.close();
          }
           if(name=="")
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
        signalOutput=(currentMessage!=lastMessage);
           if(res==200)
           lastMessage=currentMessage;

        if(signalOutput){
             qDebug()<<name<<" "<<type;
         emit sig_fetch();

        }
    }
}




