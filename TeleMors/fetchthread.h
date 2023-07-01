#ifndef FETCHTHREAD_H
#define FETCHTHREAD_H
#include <QObject>

#include<QDebug>
#include<mainwindow.h>

class FetchThread : public QObject
{
    MainWindow*e;
    Q_OBJECT
public:
    explicit FetchThread(MainWindow*,QObject *parent = nullptr);
public slots:
    void run();
signals:
    void sig_fetch(QString);
};

#endif // FETCHTHREAD_H
