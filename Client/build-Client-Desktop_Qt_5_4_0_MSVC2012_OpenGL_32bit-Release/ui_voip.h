/********************************************************************************
** Form generated from reading UI file 'voip.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOIP_H
#define UI_VOIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Voip
{
public:
    QPushButton *makeCallBtn;
    QPushButton *acceptCallBtn;

    void setupUi(QDialog *Voip)
    {
        if (Voip->objectName().isEmpty())
            Voip->setObjectName(QStringLiteral("Voip"));
        Voip->resize(400, 60);
        makeCallBtn = new QPushButton(Voip);
        makeCallBtn->setObjectName(QStringLiteral("makeCallBtn"));
        makeCallBtn->setGeometry(QRect(60, 20, 75, 23));
        acceptCallBtn = new QPushButton(Voip);
        acceptCallBtn->setObjectName(QStringLiteral("acceptCallBtn"));
        acceptCallBtn->setGeometry(QRect(270, 20, 75, 23));

        retranslateUi(Voip);

        QMetaObject::connectSlotsByName(Voip);
    } // setupUi

    void retranslateUi(QDialog *Voip)
    {
        Voip->setWindowTitle(QApplication::translate("Voip", "Dialog", 0));
        makeCallBtn->setText(QApplication::translate("Voip", "Make Call", 0));
        acceptCallBtn->setText(QApplication::translate("Voip", "Accept Call", 0));
    } // retranslateUi

};

namespace Ui {
    class Voip: public Ui_Voip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOIP_H
