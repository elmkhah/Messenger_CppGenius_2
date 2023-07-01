#include "sendmessageuser.h"
#include "ui_sendmessageuser.h"

SendMessageUser::SendMessageUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SendMessageUser)
{
    ui->setupUi(this);
    setFixedHeight(700);
    setFixedWidth(900);
}

SendMessageUser::~SendMessageUser()
{
    delete ui;
}

void SendMessageUser::on_btn_cancel_clicked()
{
//    MainWindow *mainWin=new MainWindow;
    this->hide();
//    mainWin->show();
}


void SendMessageUser::on_btn_send_clicked()
{
    if(ui->line_username->text().isEmpty()||ui->txt_message->toPlainText().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "Username and message can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }

    User _newAcc(ui->line_username->text(),false);
    MyFile _file;
    Date _date("20230101010101");
    User _sender(_file.readUsernamePassword()[0],false,_file.readUsernamePassword()[1]);
    _sender.setToken(_file.getToken());
    Message _message(_sender,_date,ui->txt_message->toPlainText());
    Request req;
    int resCode=req.sendMessageChat("private",_newAcc.getUsername(),_message);


    if(resCode==200){
        //close and go to main window
        this->hide();
//        MainWindow *mainWin=new MainWindow;
//        mainWin->show();
    }
    else if(resCode==204||resCode==401||resCode==404){
        //error baraye peyda nashodan user
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 204", "The username not found!", QMessageBox::Ok);
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


void SendMessageUser::on_btn_login_clicked()
{
    ;
}

