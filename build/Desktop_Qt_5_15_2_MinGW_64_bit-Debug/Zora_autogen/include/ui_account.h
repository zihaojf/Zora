/********************************************************************************
** Form generated from reading UI file 'account.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNT_H
#define UI_ACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_account
{
public:
    QLineEdit *account_lineEdit;
    QPushButton *account_inquireButton;
    QPushButton *account_deleteButton;
    QPushButton *account_quitButton;
    QPushButton *account_changeButton;
    QPushButton *account_addButton;
    QTableWidget *account_tableWidget;

    void setupUi(QWidget *account)
    {
        if (account->objectName().isEmpty())
            account->setObjectName(QString::fromUtf8("account"));
        account->resize(800, 600);
        account_lineEdit = new QLineEdit(account);
        account_lineEdit->setObjectName(QString::fromUtf8("account_lineEdit"));
        account_lineEdit->setGeometry(QRect(5, 0, 190, 50));
        account_inquireButton = new QPushButton(account);
        account_inquireButton->setObjectName(QString::fromUtf8("account_inquireButton"));
        account_inquireButton->setGeometry(QRect(200, 0, 120, 50));
        account_deleteButton = new QPushButton(account);
        account_deleteButton->setObjectName(QString::fromUtf8("account_deleteButton"));
        account_deleteButton->setGeometry(QRect(440, 0, 120, 50));
        account_quitButton = new QPushButton(account);
        account_quitButton->setObjectName(QString::fromUtf8("account_quitButton"));
        account_quitButton->setGeometry(QRect(680, 0, 120, 50));
        account_changeButton = new QPushButton(account);
        account_changeButton->setObjectName(QString::fromUtf8("account_changeButton"));
        account_changeButton->setGeometry(QRect(560, 0, 120, 50));
        account_addButton = new QPushButton(account);
        account_addButton->setObjectName(QString::fromUtf8("account_addButton"));
        account_addButton->setGeometry(QRect(320, 0, 120, 50));
        account_tableWidget = new QTableWidget(account);
        account_tableWidget->setObjectName(QString::fromUtf8("account_tableWidget"));
        account_tableWidget->setGeometry(QRect(0, 50, 800, 550));

        retranslateUi(account);

        QMetaObject::connectSlotsByName(account);
    } // setupUi

    void retranslateUi(QWidget *account)
    {
        account->setWindowTitle(QCoreApplication::translate("account", "Form", nullptr));
        account_inquireButton->setText(QCoreApplication::translate("account", "\346\237\245\350\257\242", nullptr));
        account_deleteButton->setText(QCoreApplication::translate("account", "\345\210\240\351\231\244", nullptr));
        account_quitButton->setText(QCoreApplication::translate("account", "\351\200\200\345\207\272", nullptr));
        account_changeButton->setText(QCoreApplication::translate("account", "\344\277\256\346\224\271", nullptr));
        account_addButton->setText(QCoreApplication::translate("account", "\345\242\236\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class account: public Ui_account {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNT_H
