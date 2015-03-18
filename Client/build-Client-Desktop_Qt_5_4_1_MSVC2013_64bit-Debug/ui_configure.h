/********************************************************************************
** Form generated from reading UI file 'configure.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURE_H
#define UI_CONFIGURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Configure
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_port;

    void setupUi(QDialog *Configure)
    {
        if (Configure->objectName().isEmpty())
            Configure->setObjectName(QStringLiteral("Configure"));
        Configure->resize(400, 300);
        buttonBox = new QDialogButtonBox(Configure);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit_ip = new QLineEdit(Configure);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));
        lineEdit_ip->setGeometry(QRect(180, 70, 113, 20));
        lineEdit_port = new QLineEdit(Configure);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(180, 150, 113, 20));

        retranslateUi(Configure);
        QObject::connect(buttonBox, SIGNAL(accepted()), Configure, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Configure, SLOT(reject()));

        QMetaObject::connectSlotsByName(Configure);
    } // setupUi

    void retranslateUi(QDialog *Configure)
    {
        Configure->setWindowTitle(QApplication::translate("Configure", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Configure: public Ui_Configure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURE_H
