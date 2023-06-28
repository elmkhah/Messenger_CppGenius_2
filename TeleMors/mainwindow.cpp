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
    int number=f.readNumberOfChats("group");
    QVector<QString> vec=f.readChats("group");
    for(int i=0;i<number;i++){
        ui->list->addItem(vec[i]);
    }
    auto it=f.readUsernamePassword().begin();
    ui->label->setText(*it);
}

MainWindow::~MainWindow()
{
    delete ui;
}

