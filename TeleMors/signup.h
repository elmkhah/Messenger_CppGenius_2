#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>



namespace Ui {
class Signup;
}

class Signup : public QMainWindow
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_pushButton_3_clicked();

    void on_btn_isHash_clicked();

    void on_btn_cancel_clicked();

    void on_btn_createAccount_clicked();

    void on_btn_login_clicked();

private:
    Ui::Signup *ui;
};

#endif // SIGNUP_H
