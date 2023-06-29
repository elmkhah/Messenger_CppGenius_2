#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "request.h"
#include "myfile.h"
#include<chat.h>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Request c;

    MyFile f;
    c.getChatList(f.getToken(),"group");
    c.getChatList(f.getToken(),"channel");
    c.getChatList(f.getToken(),"private");
    qDebug()<<"mainwindow 16";
    QVector<QString> group=f.readChats("group");
    QVector<QString>channel=f.readChats("channel");
    QVector<QString>pv=f.readChats("private");
    QVector<Chat>chat;
    for(int i=0;i<group.size();i++){
        c.getChatMessages(f.getToken(),"group",group[i]);
        qDebug()<<group.size();
    }
    for(int i=0;i<channel.size();i++)
         c.getChatMessages(f.getToken(),"channel",channel[i]);
    for(int i=0;i<pv.size();i++)
        c.getChatMessages(f.getToken(),"private",pv[i]);

    for(int i=0;i<group.size();i++)
        chat.push_back(Chat("group",group[i]));
    for(int i=0;i<channel.size();i++)
        chat.push_back( Chat("channel",channel[i]));
    for(int i=0;i<pv.size();i++)
        chat.push_back( Chat("private",pv[i]));

        for(int i=0;i<chat.size();i++){
        ui->list->addItem(chat[i].show());
    }
    QString it=f.readUsernamePassword()[0];
    ui->label->setText(it);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_list_itemClicked(QListWidgetItem *item)
{
    qDebug()<<item->text();
    Request c;
    QString name,type;
    int index=item->text().indexOf(':');
    type=item->text().mid(0,index);
    name=item->text().mid(index+1,item->text().size());
    QFile active(QDir::currentPath()+"/active.txt");
    if(active.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&active);
        out<<name;
        out<<"\n"<<type;
        active.close();
    }
MyFile m;
    QVector<Message>message=m.readMessages(type,name);
    qDebug()<<message.size();
    ui->listWidget->clear();
    for(int i=0;i<message.size();i++){

        ui->listWidget->addItem(message[i].getMessageBody());
    }

}

void MainWindow::get_fetchSignal()
{

    QString name,type;
    QFile active(QDir::currentPath()+"/active.txt");
    if(active.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream out(&active);
        out>>name>>type;
        active.close();
    }
     MyFile m;
    if(name=="")return;
    qDebug()<<43;
    QVector<Message>message=m.readMessages(type,name);
    qDebug()<<message.size();
    ui->listWidget->clear();
    for(int i=0;i<message.size();i++){

    ui->listWidget->addItem(message[i].getMessageBody());
    }
}


