#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createchannel.h"
#include"creategroup.h"
#include"joinchannel.h"
#include"joingroup.h"
#include"sendmessageuser.h"
#include"logout.h"
#include "request.h"
#include "myfile.h"
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Request c;
    MyFile f;
    int number=f.readNumberOfChats("group");
    QVector<QString> vec=f.readChats("group");
    for(int i=0;i<number;i++){
        ui->list->addItem(vec[i]);
    }
    QString it=f.readUsernamePassword()[0];
    ui->label->setText(it);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pix_logout_clicked()
{
    Logout *_logout=new Logout;
    this->hide();
    _logout->show();
}


void MainWindow::on_logout_clicked()
{
    Logout *_logout=new Logout;
    this->hide();
    _logout->show();
}


void MainWindow::on_createGroup_clicked()
{
    CreateGroup *_createGroup=new CreateGroup;
    this->hide();
    _createGroup->show();
}


void MainWindow::on_pix_createGroup_clicked()
{
    CreateGroup *_createGroup=new CreateGroup;
    this->hide();
    _createGroup->show();
}


void MainWindow::on_pix_joinChannel_clicked()
{
    JoinChannel *_joinChannel=new JoinChannel;
    this->hide();
    _joinChannel->show();
}


void MainWindow::on_joinChannel_clicked()
{
    JoinChannel *_joinChannel=new JoinChannel;
    this->hide();
    _joinChannel->show();
}


void MainWindow::on_pix_joinGroup_clicked()
{
    JoinGroup *_joinGroup=new JoinGroup;
    this->hide();
    _joinGroup->show();
}


void MainWindow::on_joinGroup_clicked()
{
    JoinGroup *_joinGroup=new JoinGroup;
    this->hide();
    _joinGroup->show();
}


void MainWindow::on_pix_createChannel_clicked()
{
    CreateChannel *_createChannel=new CreateChannel;
    this->hide();
    _createChannel->show();
}


void MainWindow::on_createChannel_clicked()
{
    CreateChannel *_createChannel=new CreateChannel;
    this->hide();
    _createChannel->show();
}


void MainWindow::on_pix_sendMessage_clicked()
{
    SendMessageUser *_sendMessage=new SendMessageUser;
    this->hide();
    _sendMessage->show();
}

