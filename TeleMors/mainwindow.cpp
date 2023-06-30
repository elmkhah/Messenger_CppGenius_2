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

void MainWindow::get_fetchSignal(QString signalType)
{
     MyFile f;
    int i, j;
    if(signalType=="message"){
    QString name,type;
    QFile active(QDir::currentPath()+"/active.txt");
    if(active.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream out(&active);
        out>>name>>type;
        active.close();
    }

    if(name=="")return;
    QVector<Message>message=f.readMessages(type,name);
    ui->listWidget->clear();
    for(i=0;i<message.size();i++){

    ui->listWidget->addItem(message[i].getMessageBody());
    }
    }
    else {
    QVector<QString> group=f.readChats("group");
    QVector<QString>channel=f.readChats("channel");
    QVector<QString>pv=f.readChats("private");
    QVector<Chat>chat;

    for(i=0;i<group.size();i++)
    chat.push_back(Chat("group",group[i]));
    for(i=0;i<channel.size();i++)
    chat.push_back( Chat("channel",channel[i]));
    for(i=0;i<pv.size();i++)
    chat.push_back( Chat("private",pv[i]));

    ui->list->clear();

    for(i=0;i<chat.size();i++){
   chat[i].update();
    }


//    for(i=0;i<chat.size()-1;i++){
//    for(j=i+1;j<chat.size();j++){
//       if (chat[i].last < chat[j].last){
//            /*tempName = chat[i].name;
//        tempType = chat[i].type;
//        tempLast = chat[i].last;
//        chat[i].name = chat[j].name;
//        chat[i].type = chat[j].type;
//        chat[i].last = chat[j].last;
//        chat[j].name = tempName;
//        chat[j].type = tempType;
//        chat[j].last = tempLast;*/
//           Chat temp = chat[i];
//            //chat[i] = chat[j];
//           //chat[j] = temp;
//       }
//    }
//    }

    for(i=0;i<chat.size();i++){
    ui->list->addItem(chat[i].show());
    }
    //chat.empty();
    }
}


