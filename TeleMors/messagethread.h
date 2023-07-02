#ifndef MESSAGETHREAD_H
#define MESSAGETHREAD_H

#include <QObject>
#include<mainwindow.h>
class MessageThread : public QObject
{
    Q_OBJECT
private:
    MainWindow*e;
    bool chatSignal;
public:
    explicit MessageThread(MainWindow*,QObject *parent = nullptr);
     void run();
public slots:
     void getFetch(bool);
signals:
    void sig_Message(QString);
};

#endif // MESSAGETHREAD_H
