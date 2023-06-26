#include "joinchannel.h"
#include "ui_joinchannel.h"

JoinChannel::JoinChannel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JoinChannel)
{
    setFixedHeight(700);
    setFixedWidth(900);
    ui->setupUi(this);
}

JoinChannel::~JoinChannel()
{
    delete ui;
}

void JoinChannel::on_btn_join_clicked()
{
    if(ui->line_channelName->text().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "Channel name can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }
    Request req;
    int resCode=req.joinChannel(req.getToken(),ui->line_channelName->text());


    if(resCode==200){
        //close and go to mainwindow
        this->hide();
        MainWindow *mainPage=new MainWindow;
        mainPage->show();
    }
    else if(resCode==404){
        //error to user for
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "The channel name is incorrect!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
    }else if(resCode== 500){
        //offline error
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 500", "Please check your internet connection!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
    }
}


void JoinChannel::on_btn_cancel_clicked()
{
    this->hide();
    MainWindow*window=new MainWindow;
    window->show();
}

