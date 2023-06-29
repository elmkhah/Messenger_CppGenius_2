#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "request.h"
#include "myfile.h"
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Request c;

    MyFile f;
    c.getChatList(f.getToken(),"group");
    qDebug()<<"mainwindow 16";
    QVector<QString> group=f.readChats("group");
    QVector<QString>channel=f.readChats("channel");
    QVector<QString>pv=f.readChats("private");
    for(int i=0;i<vec.size();i++){
        ui->list->addItem(vec[i]);
    }
    QString it=f.readUsernamePassword()[0];
    ui->label->setText(it);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_list_itemClicked(QListWidgetItem *item)
{
    qDebug()<<item->text();
    Request c;


    QFile active(QDir::currentPath()+"/active.txt");
    if(active.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&active);
        out<<item->text();
        active.close();
    }
MyFile m;
    QVector<Message>message=m.readMessages("group",item->text());
    qDebug()<<message.size();
    ui->listWidget->clear();
    for(int i=0;i<message.size();i++){

        ui->listWidget->addItem(message[i].getMessageBody());
    }

}

void MainWindow::get_fetchSignal()
{

    QString name;
    QFile active(QDir::currentPath()+"/active.txt");
    if(active.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream out(&active);
        out>>name;
        active.close();
    }
     MyFile m;
    if(name=="")return;
    qDebug()<<43;
    QVector<Message>message=m.readMessages("group",name);
    qDebug()<<message.size();
    ui->listWidget->clear();
    for(int i=0;i<message.size();i++){

    ui->listWidget->addItem(message[i].getMessageBody());
    }
}


