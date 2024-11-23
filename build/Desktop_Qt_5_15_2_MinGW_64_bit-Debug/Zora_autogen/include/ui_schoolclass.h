/********************************************************************************
** Form generated from reading UI file 'schoolclass.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHOOLCLASS_H
#define UI_SCHOOLCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_schoolclass
{
public:

    void setupUi(QWidget *schoolclass)
    {
        if (schoolclass->objectName().isEmpty())
            schoolclass->setObjectName(QString::fromUtf8("schoolclass"));
        schoolclass->resize(400, 300);

        retranslateUi(schoolclass);

        QMetaObject::connectSlotsByName(schoolclass);
    } // setupUi

    void retranslateUi(QWidget *schoolclass)
    {
        schoolclass->setWindowTitle(QCoreApplication::translate("schoolclass", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class schoolclass: public Ui_schoolclass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHOOLCLASS_H
