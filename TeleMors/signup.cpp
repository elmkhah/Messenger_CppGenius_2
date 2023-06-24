#include "signup.h"
#include "ui_signup.h"
#include <QIcon>
#include "request.h"
#include "login.h"

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
    User _newAcc(ui->line_username->text(),false,ui->line_password->text());
    Request req;
    int resCode=req.signup(_newAcc);
    switch (resCode) {
    case 200:
        //close and go to login page
        break;
    case 204:
        //error to user for tekrari bodan

        break;
    case 500:
        //offline error

        break;
    default:
        break;
    }
}


void Signup::on_btn_login_clicked()
{
    Login *_loginBtn=new Login;
    this->hide();
    _loginBtn->show();
}

