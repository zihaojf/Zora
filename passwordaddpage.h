#ifndef PASSWORDADDPAGE_H
#define PASSWORDADDPAGE_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class passwordaddpage;
}

class passwordaddpage : public QWidget
{
    Q_OBJECT

public:
    explicit passwordaddpage(QWidget *parent = nullptr);
    ~passwordaddpage();

private slots:
    void on_pushButton_clicked();

signals:
    void senddata(QString webappname,QString username,QString password,QString description);

private:
    Ui::passwordaddpage *ui;
};

#endif // PASSWORDADDPAGE_H
