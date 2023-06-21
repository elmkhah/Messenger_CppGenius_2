#include "mainwindow.h"
#include"user.h"
#include <QApplication>
#include"request.h"
#include "signup.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w=new MainWindow;
    Request c;
    User ali("ali",1,"1382");
    c.logout(ali);
//c.login(ali);
//    c.getUserList(ali.getToken());
//    c.getUserChats(ali.getToken(),"sara");
    Signup *a2=new Signup;
    a2->show();

//    c.getGroupList(g);
//    w->show();
    return a.exec();
}
