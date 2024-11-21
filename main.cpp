#include "zora.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Zora w;
    w.show();
    return a.exec();
}
