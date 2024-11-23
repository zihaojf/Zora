/********************************************************************************
** Form generated from reading UI file 'music.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSIC_H
#define UI_MUSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_music
{
public:
    QLabel *label;

    void setupUi(QWidget *music)
    {
        if (music->objectName().isEmpty())
            music->setObjectName(QString::fromUtf8("music"));
        music->resize(400, 300);
        label = new QLabel(music);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 130, 67, 20));

        retranslateUi(music);

        QMetaObject::connectSlotsByName(music);
    } // setupUi

    void retranslateUi(QWidget *music)
    {
        music->setWindowTitle(QCoreApplication::translate("music", "Form", nullptr));
        label->setText(QCoreApplication::translate("music", "music", nullptr));
    } // retranslateUi

};

namespace Ui {
    class music: public Ui_music {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSIC_H
