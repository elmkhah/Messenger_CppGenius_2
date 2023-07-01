#include "creategroup.h"
#include "ui_creategroup.h"

CreateGroup::CreateGroup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateGroup)
{
    ui->setupUi(this);
    setFixedHeight(700);
    setFixedWidth(900);
}

CreateGroup::~CreateGroup()
{
    delete ui;
}

void CreateGroup::on_btn_cancel_clicked()
{
//    QMainWindow *mainWin=new MainWindow;
    this->hide();
//    mainWin->show();
}


void CreateGroup::on_btn_create_clicked()
{
    if(ui->line_groupName->text().isEmpty()){
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 404", "group name and title can't be empty!", QMessageBox::Ok);
        msgBox->setStyleSheet("QPushButton{; padding-left: 25px;}");
        msgBox->setStyleSheet("QPushButton { text-align: center; }");
        msgBox->show();
        return;
    }
    Request req;
    MyFile _file;
    int resCode=req.createChat(_file.getToken(),"group",ui->line_groupName->text());

    if(resCode==200){
        //close and go to mainwindow
        this->hide();
//        MainWindow *mainPage=new MainWindow;
//        mainPage->show();
    }
    else if(resCode==204){
        //error to user for tekrari bodan
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning, "error 204", "The group name that entered is already in use!", QMessageBox::Ok);
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

