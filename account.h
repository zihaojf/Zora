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
    void creat_database();







private:
    Ui::account *ui;

    QSqlDatabase account_db;
    QSqlQuery sql_query;



};

#endif // ACCOUNT_H
