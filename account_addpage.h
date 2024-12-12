#ifndef ACCOUNT_ADDPAGE_H
#define ACCOUNT_ADDPAGE_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <qmessagebox.h>
#include <QDebug>

namespace Ui {
class account_addpage;
}

class account_addpage : public QWidget
{
    Q_OBJECT

public:
    explicit account_addpage(QWidget *parent = nullptr);
    ~account_addpage();


signals:
    void senddata(double money,QString method,QString description,QDateTime datetime);


private slots:
    void on_pushButton_clicked();

private:
    Ui::account_addpage *ui;
};

#endif // ACCOUNT_ADDPAGE_H
