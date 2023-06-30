#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "request.h"
#include "myfile.h"
#include<chat.h>
#include <QVector>
#include "sendmessageuser.h"
#include "logout.h"
#include "createchannel.h"
#include "creategroup.h"
#include "joinchannel.h"
#include "joingroup.h"
#include <QMessageBox>>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyFile f;
    ui->label->setText(f.readUsernamePassword()[0]);

    ui->listWidget->setStyleSheet("QListWidget::item { max-width: 200px; background-color: rgb(162,162,161); border-radius: 7px } QListWidget{ font: 16pt \"Tw Cen MT\"; background-color: rgb(25, 81, 144);border-radius: 10px;}");
    ui->listWidget->setSpacing(7);

}

MainWindow::~MainWindow()
{
    delete ui;
}


QString procces(QString message){
    int size=message.length();
    QString newStr="";
    int count =size/50;
    for(int i=0;i<=count;i++){
        newStr+=message.mid(i*50,50);
        newStr+="\n";
    }
    return newStr;

}
void MainWindow::on_list_itemClicked(QListWidgetItem *item)
{
    //set kardane moshakhasat contact
    qDebug()<<item->text();
    ui->line_message->clear();
    ui->lbl_contactName->setText(item->text());

    //is channel??
    QString contact=ui->listWidget->currentItem()->text();
    QString _type="";
    QString _name="";
    for(int i=0;i<contact.length();i++){
        if(contact.mid(i,1)==":"){
            _name=contact.mid(i+1,contact.length()-i-1);
            break;
        }
        else{
            _type+=contact.mid(i,1);
        }
    }
//    if(_type=="channel"){
//        //is admin
//        MyFile f;
//        f.
//    }


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
//    ui->ListWidget::item->setMaximumWidth(300);



    //read messages

    for(int i=0;i<message.size();i++){
        QString newStr=procces(message[i].getMessageBody());
        QString txt=message[i].getSender().getUsername()+"\n"+newStr+"\n"+message[i].getSentDate().getHourMinute();
        QString _senderUser=message[i].getSender().getUsername();

        //if sender is you
        if(_senderUser==m.readUsernamePassword()[0]){
            QListWidgetItem* firstItem=new QListWidgetItem;
            firstItem->setText(txt);
            firstItem->setTextAlignment(Qt::AlignRight);
            ui->listWidget->addItem(firstItem);
        }
        //if sender is contact
        else{
        QListWidgetItem* firstItem=new QListWidgetItem;
        firstItem->setText(txt);
        firstItem->setTextAlignment(Qt::AlignLeft);
        ui->listWidget->addItem(firstItem);
        }
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

void MainWindow::on_pix_sendMessage_clicked()
{
    SendMessageUser *_newWin=new SendMessageUser;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_sendMessage_clicked()
{
    SendMessageUser *_newWin=new SendMessageUser;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_pix_joinGroup_clicked()
{
    JoinGroup *_newWin=new JoinGroup;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_joinGroup_clicked()
{
    JoinGroup *_newWin=new JoinGroup;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_pix_joinChannel_clicked()
{
    JoinChannel *_newWin=new JoinChannel;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_joinChannel_clicked()
{
    JoinChannel *_newWin=new JoinChannel;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_pix_createGroup_clicked()
{
    CreateGroup *_newWin=new CreateGroup;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_createGroup_clicked()
{
    CreateGroup *_newWin=new CreateGroup;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_pix_createChannel_clicked()
{
    CreateChannel *_newWin=new CreateChannel;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_createChannel_clicked()
{
    CreateChannel *_newWin=new CreateChannel;
//    this->hide();
    _newWin->show();
}


void MainWindow::on_pix_logout_clicked()
{
    Logout *_newWin=new Logout;
    this->hide();
    _newWin->show();
}


void MainWindow::on_logout_clicked()
{
    Logout *_newWin=new Logout;
    this->hide();
    _newWin->show();
}


void MainWindow::on_btn_send_clicked()
{
    if(ui->line_message->text().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "message can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }
    Request c;
    QString contact=ui->listWidget->currentItem()->text();
    QString _type="";
    QString _name="";
    for(int i=0;i<contact.length();i++){
        if(contact.mid(i,1)==":"){
            _name=contact.mid(i+1,contact.length()-i-1);
            break;
        }
        else{
            _type+=contact.mid(i,1);
        }
    }
    MyFile f;
    User _sender(f.readUsernamePassword()[0],false,f.readUsernamePassword()[1]);
    Date _date("20230101010101");
    Message _msg(_sender,_date,ui->line_message->text());
    c.sendMessageChat(_type,_name,_msg);
    ui->line_message->clear();
}

