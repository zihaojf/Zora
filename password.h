#ifndef PASSWORD_H
#define PASSWORD_H

#include <QWidget>
#include <QProcess>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QMessageBox>
#include <QtSql/QsqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include "passwordaddpage.h"
#include "passwordsettings.h"

namespace Ui {
class password;
}

class password : public QWidget
{
    Q_OBJECT

public:
    explicit password(QWidget *parent = nullptr);
    ~password();
    bool creat_database_connection();//设置数据库链接
    void initbutton();
    void inittable();
    void show_alltable();
    void initpage();
    void searchbtn_push();
    void addbtn_push();
    void setbtn_push();
    void delete_password(const QPoint &pos);
    void insertdata(QString webappname,QString username,QString password,QString description);

private slots:
    void showContextMenu(const QPoint &pos);
    void receive_data(QString webappname,QString username,QString password,QString description);

    void on_setbtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::password *ui;
    const int columncount = 5;//表格列数
    passwordaddpage *passwordaddpage_window;
    passwordsettings *pwdsetting_window;
};

#endif // PASSWORD_H
