#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->listWidget->setStyleSheet("QListWidget::item { max-width: 200px; background-color: rgb(162,162,161); border-radius: 7px } QListWidget{ font: 16pt \"Tw Cen MT\"; background-color: rgb(25, 81, 144);border-radius: 10px;}");
    ui->listWidget->setSpacing(7);

}

MainWindow::~MainWindow()
{
    delete ui;
}


QString procces(QString message){
    int i;
    qDebug()<<"mainwindow 35";;
    int size=message.length();
    QString newStr="";
    int count =size/50;
    for(i=0;i<=count;i++){
        newStr+=message.mid(i*50,50);
        newStr+="\n";
    }
    return newStr;

}
void MainWindow::on_list_itemClicked(QListWidgetItem *item)
{
       ui->label->setText(f.readUsernamePassword()[0]);

    //set kardane moshakhasat contact
    qDebug()<<item->text();
    ui->line_message->clear();
    ui->lbl_contactName->setText(item->text());
qDebug()<<"mainwindow 52";;
    //is channel??

int deteminate;
  QString name,type;
    int index=item->text().indexOf(':');
    type=item->text().mid(0,index);
    name=item->text().mid(index+1,item->text().size());
    if(type=="channel"){
        QFile admin(QDir::currentPath()+"/channelChats/chats/"+name+"isAdmin.txt");
        if(admin.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream in(&admin);
            in>>deteminate;
             admin.close();
            qDebug()<<deteminate;
            if(!deteminate){
                ui->btn_send->setEnabled(false);
            }
            else{
                ui->btn_send->setEnabled(true);
            }

        }
    }
        else  ui->btn_send->setEnabled(true);


    QFile active(QDir::currentPath()+"/active.txt");
    if(active.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&active);
        out<<name;
        out<<"\n"<<type;
        active.close();

    QVector<Message>message=f.readMessages(type,name);
    qDebug()<<message.size();
    ui->listWidget->clear();
//    ui->ListWidget::item->setMaximumWidth(300);



    //read messages
qDebug()<<"mainwindow 94";;
    for( i=0;i<message.size();i++){
        QString newStr=procces(message[i].getMessageBody());
        QString txt=message[i].getSender().getUsername()+"\n"+newStr+"\n"+message[i].getSentDate().getHourMinute();
        QString _senderUser=message[i].getSender().getUsername();

        qDebug()<<"mainwindow 102";;
        //if sender is you
        if(_senderUser==f.readUsernamePassword()[0]){
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
}
void MainWindow::get_fetchSignal(QString signalType)
{


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
            ui->list->addItem(chat[i].show());
        }
        chat.empty();
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

    qDebug()<<"mainwindow 287";;

    if(ui->line_message->text().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "message can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }

    qDebug()<<"mainwindow 297";;


    QFile active(QDir::currentPath()+"/active.txt");
    if(active.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream out(&active);
        out>>_name;
        out>>_type;
        active.close();
    }

    User _sender(f.readUsernamePassword()[0],false,f.readUsernamePassword()[1],f.getToken());
    Date _date("20230101010101");
    Message _msg(_sender,_date,ui->line_message->text());
    c.sendMessageChat(_type,_name,_msg);
    ui->line_message->clear();
}

