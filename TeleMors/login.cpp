#include "login.h"
#include "ui_login.h"
#include "user.h"
#include "request.h"
#include "signup.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setFixedHeight(700);
    setFixedWidth(900);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btn_isHash_clicked()
{
    ui->line_password->echoMode()==QLineEdit::Password?ui->line_password->setEchoMode(QLineEdit::Normal):ui->line_password->setEchoMode(QLineEdit::Password);
}


void Login::on_btn_cancel_clicked()
{
    this->close();

}


void Login::on_btn_login_clicked()
{
    User _newAcc(ui->line_username->text(),false,ui->line_password->text());
    Request req;
    int resCode=req.login(_newAcc);
    switch (resCode) {
    case 200:
        //close and go to main
        break;
    case 401:
        //error to user for qalat bodan

        break;
    case 500:
        //offline error

        break;
    default:
        break;
    }
}


void Login::on_btn_signup_clicked()
{
    this->close();
    Signup *signupBtn=new Signup;
    signupBtn->show();
}

