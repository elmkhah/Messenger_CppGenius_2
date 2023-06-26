#ifndef SENDMESSAGEUSER_H
#define SENDMESSAGEUSER_H

#include <QMainWindow>

namespace Ui {
class SendMessageUser;
}

class SendMessageUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit SendMessageUser(QWidget *parent = nullptr);
    ~SendMessageUser();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_login_clicked();

    void on_btn_send_clicked();

private:
    Ui::SendMessageUser *ui;
};

#endif // SENDMESSAGEUSER_H
