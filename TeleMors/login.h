#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btn_isHash_clicked();

    void on_btn_cancel_clicked();

    void on_btn_login_clicked();

    void on_btn_signup_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
