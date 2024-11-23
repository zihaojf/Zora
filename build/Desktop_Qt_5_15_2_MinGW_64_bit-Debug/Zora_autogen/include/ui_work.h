/********************************************************************************
** Form generated from reading UI file 'work.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORK_H
#define UI_WORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_work
{
public:

    void setupUi(QWidget *work)
    {
        if (work->objectName().isEmpty())
            work->setObjectName(QString::fromUtf8("work"));
        work->resize(400, 300);

        retranslateUi(work);

        QMetaObject::connectSlotsByName(work);
    } // setupUi

    void retranslateUi(QWidget *work)
    {
        work->setWindowTitle(QCoreApplication::translate("work", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class work: public Ui_work {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORK_H
