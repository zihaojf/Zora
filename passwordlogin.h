#ifndef PASSWORDLOGIN_H
#define PASSWORDLOGIN_H

#include <QWidget>
#include <QSettings>
#include "password.h"
#include <QMessageBox>

namespace Ui {
class passwordlogin;
}

class passwordlogin : public QWidget
{
    Q_OBJECT

public:
    explicit passwordlogin(QWidget *parent = nullptr);
    ~passwordlogin();

    void loadconfig();
    void loginbtn_push();
    void init();

private:
    Ui::passwordlogin *ui;
    QString password;
    class password *password_window;
};

#endif // PASSWORDLOGIN_H
