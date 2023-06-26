#ifndef CREATECHANNEL_H
#define CREATECHANNEL_H

#include <QMainWindow>

namespace Ui {
class CreateChannel;
}

class CreateChannel : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateChannel(QWidget *parent = nullptr);
    ~CreateChannel();

private slots:
    void on_btn_create_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::CreateChannel *ui;
};

#endif // CREATECHANNEL_H
