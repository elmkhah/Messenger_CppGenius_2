#include "mainwindow.h"
#include <QApplication>
#include<fetchthread.h>
#include <QThread>
#include <QtConcurrent>
#include<login.h>
int main(int argc,char*argv[]){
    QFile active(QDir::currentPath()+"/active.txt");
    if(active.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&active);
        out<<"";
        active.close();
    }


QApplication a(argc, argv);

    MainWindow *mainn=new MainWindow;
QThread thread1;
//QThread thread2;

thread1.setObjectName("thread1");
//thread2.setObjectName("thread2");
FetchThread t(mainn);
//UiThread t2;

t.moveToThread(&thread1);
//t2.moveToThread(&thread2);

QObject::connect(&thread1,&QThread::started,&t,&FetchThread::run);
//QObject::connect(&thread2,&QThread::started,&t2,&UiThread::run);


thread1.start();
Login *m=new Login(mainn);
m->show();

//thread2.start();
//thread1.wait();
//thread2.wait();
return a.exec();
}
