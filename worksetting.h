#ifndef WORKSETTING_H
#define WORKSETTING_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class worksetting;
}

class worksetting : public QWidget
{
    Q_OBJECT

public:
    explicit worksetting(QWidget *parent = nullptr);
    ~worksetting();

signals:
    void sendata(int worktime,int relaxtime);


private slots:
    void on_comfirmbtn_clicked();

private:
    Ui::worksetting *ui;
};

#endif // WORKSETTING_H
