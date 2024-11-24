#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class account;
}

class account : public QWidget
{
    Q_OBJECT

public:
    explicit account(QWidget *parent = nullptr);
    ~account();


private:
    Ui::account *ui;
};

#endif // ACCOUNT_H
