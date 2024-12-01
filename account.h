#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QProcess>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QtSql/QsqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>


namespace Ui {
class account;
}

class account : public QWidget
{
    Q_OBJECT

public:
    explicit account(QWidget *parent = nullptr);
    ~account();
    QTableWidget *account_tableWidget;
    QSqlDatabase account_db;
    QSqlQuery sql_query;
    int temp_account_id;
    QString temp_account_money;
    QString temp_account_text;
    QDate temp_account_day;




    void setaccount_tableWidget();
    void renewaccount_database();





private slots:
    void on_account_addButton_clicked();

private:
    Ui::account *ui;



};

#endif // ACCOUNT_H
