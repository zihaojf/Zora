#ifndef PASSWORDADDPAGE_H
#define PASSWORDADDPAGE_H

#include <QWidget>

namespace Ui {
class passwordaddpage;
}

class passwordaddpage : public QWidget
{
    Q_OBJECT

public:
    explicit passwordaddpage(QWidget *parent = nullptr);
    ~passwordaddpage();

private:
    Ui::passwordaddpage *ui;
};

#endif // PASSWORDADDPAGE_H
