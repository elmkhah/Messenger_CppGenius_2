#include "createchannel.h"
#include "ui_createchannel.h"
#include "mainwindow.h"
#include "request.h"
#include <QMessageBox>
#include "myfile.h"

CreateChannel::CreateChannel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateChannel)
{
    ui->setupUi(this);
    setFixedHeight(700);
    setFixedWidth(900);
}

CreateChannel::~CreateChannel()
{
    delete ui;
}

void CreateChannel::on_btn_create_clicked()
{
    if(ui->line_channelName->text().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "Channel name and title can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }
    Request req;
    MyFile _file;
    int resCode=req.createChat(_file.getToken(),"channel",ui->line_channelName->text());

    if(resCode==200){
        //close and go to mainwindow
        this->hide();
//        MainWindow *mainPage=new MainWindow;
//        mainPage->show();
    }
    else if(resCode==204){
        //error to user for tekrari bodan
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 204", "The channel name that entered is already in use!", QMessageBox::Ok);
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


void CreateChannel::on_btn_cancel_clicked()
{
//    MainWindow *mainWin=new MainWindow;
    this->hide();
//    mainWin->show();
}

