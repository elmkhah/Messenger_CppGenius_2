#include "joingroup.h"
#include "ui_joingroup.h"

JoinGroup::JoinGroup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JoinGroup)
{
    ui->setupUi(this);
}

JoinGroup::~JoinGroup()
{
    delete ui;
}

void JoinGroup::on_btn_join_clicked()
{

    if(ui->line_groupName->text().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "Group name can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }
    Request req;
    int resCode=req.joinGroup(req.getToken(),ui->line_groupName->text());


    if(resCode==200){
        //close and go to mainwindow
        this->hide();
        MainWindow *mainPage=new MainWindow;
        mainPage->show();
    }
    else if(resCode==404){
        //error to user for
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "The group name is incorrect!", QMessageBox::Ok);
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


void JoinGroup::on_btn_cancel_clicked()
{
    this->hide();
    MainWindow*mainPage=new MainWindow;
    mainPage->show();
}

