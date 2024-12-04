#ifndef ACCOUNT_YEARCHART_H
#define ACCOUNT_YEARCHART_H

#include <QWidget>

namespace Ui {
class account_yearchart;
}

class account_yearchart : public QWidget
{
    Q_OBJECT

public:
    explicit account_yearchart(QWidget *parent = nullptr);
    ~account_yearchart();

private:
    Ui::account_yearchart *ui;
};

#endif // ACCOUNT_YEARCHART_H
