/********************************************************************************
** Form generated from reading UI file 'life.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIFE_H
#define UI_LIFE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_life
{
public:
    QLabel *label;

    void setupUi(QWidget *life)
    {
        if (life->objectName().isEmpty())
            life->setObjectName(QString::fromUtf8("life"));
        life->resize(400, 300);
        label = new QLabel(life);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 130, 67, 20));

        retranslateUi(life);

        QMetaObject::connectSlotsByName(life);
    } // setupUi

    void retranslateUi(QWidget *life)
    {
        life->setWindowTitle(QCoreApplication::translate("life", "Form", nullptr));
        label->setText(QCoreApplication::translate("life", "life", nullptr));
    } // retranslateUi

};

namespace Ui {
    class life: public Ui_life {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIFE_H
