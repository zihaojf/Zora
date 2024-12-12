#ifndef PASSWORDSETTINGS_H
#define PASSWORDSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class passwordsettings;
}

class passwordsettings : public QWidget
{
    Q_OBJECT

public:
    explicit passwordsettings(QWidget *parent = nullptr);
    ~passwordsettings();

private slots:
    void on_confirmbtn_clicked();

private:
    Ui::passwordsettings *ui;
};

#endif // PASSWORDSETTINGS_H
