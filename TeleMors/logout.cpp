#include "logout.h"
#include<QCoreApplication>
#include "ui_logout.h"



Logout::Logout(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Logout)
{
    ui->setupUi(this);
    setFixedHeight(700);
    setFixedWidth(900);
}

Logout::~Logout()
{
    delete ui;
}

void Logout::on_btn_isHash_clicked()
{
    ui->line_password->echoMode()==QLineEdit::Password?ui->line_password->setEchoMode(QLineEdit::Normal):ui->line_password->setEchoMode(QLineEdit::Password);
}


void Logout::on_btn_cancel_clicked()
{
//    MainWindow *mainWin=new MainWindow;
//    this->hide();
//    mainWin->show();
}


void Logout::on_btn_login_clicked()
{
    if(ui->line_username->text().isEmpty()||ui->line_password->text().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "Username and password can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }
    MyFile _file;
    if(!(ui->line_username->text()==_file.readUsernamePassword()[0]&&ui->line_password->text()==_file.readUsernamePassword()[1])){
        //error to user for qalat bodan
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 401", "The selected username does not match the password!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }

    User _newAcc(ui->line_username->text(),false,ui->line_password->text());
    Request req;
    int resCode=req.logout(_newAcc);
    if(resCode==200){
//        Login* loginWin=new Login(MainWindow);
        QCoreApplication::quit();
//        loginWin->show();
    }
    else if(resCode==401||resCode==404){

        //error to user for qalat bodan
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 401", "The selected username does not match the password!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
    }
    else if(resCode==500){

        //offline error
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 500", "Please check your internet connection!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
    }
}

