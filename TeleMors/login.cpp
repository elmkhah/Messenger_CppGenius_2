#include "login.h"
#include "ui_login.h"


Login::Login(MainWindow *s,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    QString lo;
    MyFile f;
    e=s;
    QFile isLogin(QDir::currentPath()+"/information/isLogin.txt");
    if (isLogin.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&isLogin);
        in>>lo;
        isLogin.close();
    }
    if(lo=="1"){
        this->hide();
    e->show();
    }
    else
    this->show();
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

    if(ui->line_username->text().isEmpty()||ui->line_password->text().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "Username and password can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }

    User _newAcc(ui->line_username->text(),false,ui->line_password->text());
    Request req;
    req.logout(_newAcc);
    int resCode=req.login(_newAcc);
    if(resCode==200){
        this->hide();
        e->show();
    }
    else if(resCode==401){

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


void Login::on_btn_signup_clicked()
{
    this->close();
    Signup *signupBtn=new Signup;
    signupBtn->show();
}

