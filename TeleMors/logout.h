#ifndef LOGOUT_H
#define LOGOUT_H

#include <QMainWindow>

namespace Ui {
class Logout;
}

class Logout : public QMainWindow
{
    Q_OBJECT

public:
    explicit Logout(QWidget *parent = nullptr);
    ~Logout();

private slots:
    void on_btn_isHash_clicked();

    void on_btn_cancel_clicked();

    void on_btn_login_clicked();

private:
    Ui::Logout *ui;
};

#endif // LOGOUT_H
