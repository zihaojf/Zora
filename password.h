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
    void delete_password();

private slots:
    void showContextMenu(const QPoint &pos);

private:
    Ui::password *ui;
    const int columncount = 5;//表格列数
};

#endif // PASSWORD_H
