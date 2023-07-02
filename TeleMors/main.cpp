#include "mainwindow.h"
#include <QApplication>
#include<fetchthread.h>
#include <QThread>
#include <QtConcurrent>
#include<login.h>
#include<messagethread.h>
int main(int argc,char*argv[]){

    MyFile m1;
m1.activeEmpty();
QApplication a(argc, argv);

        MainWindow *mainn=new MainWindow();
QThread thread1;
QThread thread2;

thread1.setObjectName("thread1");
thread2.setObjectName("thread2");
FetchThread t(mainn);
MessageThread t2(mainn);

t.moveToThread(&thread1);
t2.moveToThread(&thread2);

QObject::connect(&thread1,&QThread::started,&t,&FetchThread::run);
QObject::connect(&thread2,&QThread::started,&t2,&MessageThread::run);


thread1.start();
thread2.start();
Login *m=new Login(mainn);


//thread2.start();
//thread1.wait();
//thread2.wait();
return a.exec();
}
