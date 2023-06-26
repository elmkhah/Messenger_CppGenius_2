#include "mainwindow.h"
#include"user.h"
#include <QApplication>
#include"request.h"
#include "signup.h"
#include<joinchannel.h>
#include<joingroup.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w=new MainWindow;
    Request c;
    User ali("ali",1,"1382");
    JoinGroup*j=new JoinGroup;
    j->show();
//    c.getGroupList(g);
//    w->show();
    return a.exec();
}
