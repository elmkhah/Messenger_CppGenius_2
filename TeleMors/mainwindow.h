#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<signup.h>
#include<QListWidget>
#include<request.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
<<<<<<< HEAD
    void on_pushButton_6_clicked();

    void on_pix_logout_clicked();

    void on_logout_clicked();

    void on_createGroup_clicked();

    void on_pix_createGroup_clicked();

    void on_pix_joinChannel_clicked();

    void on_joinChannel_clicked();

    void on_pix_joinGroup_clicked();

    void on_joinGroup_clicked();

    void on_pix_createChannel_clicked();

    void on_createChannel_clicked();

    void on_pix_sendMessage_clicked();

=======
    void on_list_itemClicked(QListWidgetItem *item);
public slots:
<<<<<<< HEAD
    void get_fetchSignal();
>>>>>>> main
=======
    void get_fetchSignal(QString);
>>>>>>> main
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
