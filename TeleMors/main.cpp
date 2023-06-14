#include "mainwindow.h"
#include"user.h"
#include <QApplication>
#include"request.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w=new MainWindow;
    Request c;
    User ali("ali",1,"1382");
    //c.login(ali);
    w->show();
    return a.exec();
}
