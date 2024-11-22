/********************************************************************************
** Form generated from reading UI file 'zora.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZORA_H
#define UI_ZORA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Zora
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Zora)
    {
        if (Zora->objectName().isEmpty())
            Zora->setObjectName(QString::fromUtf8("Zora"));
        Zora->resize(800, 600);
        centralwidget = new QWidget(Zora);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Zora->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Zora);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        Zora->setMenuBar(menubar);
        statusbar = new QStatusBar(Zora);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Zora->setStatusBar(statusbar);

        retranslateUi(Zora);

        QMetaObject::connectSlotsByName(Zora);
    } // setupUi

    void retranslateUi(QMainWindow *Zora)
    {
        Zora->setWindowTitle(QCoreApplication::translate("Zora", "Zora", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Zora: public Ui_Zora {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZORA_H
