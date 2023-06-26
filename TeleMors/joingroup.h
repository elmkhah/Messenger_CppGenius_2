#ifndef JOINGROUP_H
#define JOINGROUP_H

#include <QMainWindow>
#include<mainwindow.h>
#include<QMessageBox>
#include<request.h>
namespace Ui {
class JoinGroup;
}

class JoinGroup : public QMainWindow
{
    Q_OBJECT

public:
    explicit JoinGroup(QWidget *parent = nullptr);
    ~JoinGroup();

private slots:
    void on_btn_join_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::JoinGroup *ui;
};

#endif // JOINGROUP_H
