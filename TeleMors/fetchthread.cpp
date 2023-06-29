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
    QString lastMessage="";
            QString currentMessage;
    Request c;
            bool signalOutput;
    MyFile c1;

    QFile active(QDir::currentPath()+"/active.txt");
    connect(this,SIGNAL(sig_fetch()),e,SLOT(get_fetchSignal()));
    while(1)
    {


        if(active.open(QIODevice::ReadOnly|QIODevice::Text)){
              QTextStream in(&active);
         in>>name;
             active.close();
          }
           if(name=="")
             continue;
        c.getChatMessages(c1.getToken(),"group",name);
           currentMessage=c1.getTimeLastMessage("group",name);
        signalOutput=(currentMessage!=lastMessage);
           lastMessage=currentMessage;

        if(signalOutput){
         emit sig_fetch();
qDebug()<<6777;
        }
    }
}



//
