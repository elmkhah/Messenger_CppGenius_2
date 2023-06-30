#include "signup.h"
#include "ui_signup.h"
#include <QIcon>
#include "request.h"
#include "login.h"
#include <QMessageBox>


Signup::Signup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    setFixedHeight(700);
    setFixedWidth(900);
}

Signup::~Signup()
{
    delete ui;
}



void Signup::on_btn_isHash_clicked()
{
    ui->line_password->echoMode()==QLineEdit::Password?ui->line_password->setEchoMode(QLineEdit::Normal):ui->line_password->setEchoMode(QLineEdit::Password);
}


void Signup::on_btn_cancel_clicked()
{
    this->hide();
}


void Signup::on_btn_createAccount_clicked()
{
    if(ui->line_username->text().isEmpty()||ui->line_password->text().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "Username and password can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
    return;
    }

    User _newAcc(ui->line_username->text(),false,ui->line_password->text());
    Request req;
    int resCode=req.signup(_newAcc);


    if(resCode==200){
        //close and go to login page
        this->hide();
//        Login *loginPage=new Login;
//        loginPage->show();
    }
    else if(resCode==204){
        //error to user for tekrari bodan
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 204", "The username entered is already in use!", QMessageBox::Ok);
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


void Signup::on_btn_login_clicked()
{
//    Login *_loginBtn=new Login;
//    this->hide();
//    _loginBtn->show();
}


void Signup::on_pushButton_3_clicked()
{
    ;
}

