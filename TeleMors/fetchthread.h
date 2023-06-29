#ifndef FETCHTHREAD_H
#define FETCHTHREAD_H
#include<mainwindow.h>
#include <QObject>

class FetchThread : public QObject
{
    MainWindow*e;
    Q_OBJECT
public:
    explicit FetchThread(MainWindow*,QObject *parent = nullptr);
public slots:
    void run();
signals:
    void sig_fetch();
};

#endif // FETCHTHREAD_H
