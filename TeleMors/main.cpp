#include "mainwindow.h"
#include"user.h"
#include <QApplication>
#include"requset.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w=new MainWindow;
    Requset c;
    User ali("ali",1,"1382");
    c.login(ali);
    w->show();
    return a.exec();
}
