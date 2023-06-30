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
    void on_list_itemClicked(QListWidgetItem *item);
public slots:
    void get_fetchSignal(QString);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
