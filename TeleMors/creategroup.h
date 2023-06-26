#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QMainWindow>

namespace Ui {
class CreateGroup;
}

class CreateGroup : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateGroup(QWidget *parent = nullptr);
    ~CreateGroup();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_create_clicked();

private:
    Ui::CreateGroup *ui;
};

#endif // CREATEGROUP_H
