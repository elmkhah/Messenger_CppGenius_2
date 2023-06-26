#ifndef JOINCHANNEL_H
#define JOINCHANNEL_H

#include <QMainWindow>
#include<mainwindow.h>
#include<QMessageBox>
#include<request.h>
namespace Ui {
class JoinChannel;
}

class JoinChannel : public QMainWindow
{
    Q_OBJECT

public:
    explicit JoinChannel(QWidget *parent = nullptr);
    ~JoinChannel();

private slots:
    void on_btn_join_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::JoinChannel *ui;
};

#endif // JOINCHANNEL_H
