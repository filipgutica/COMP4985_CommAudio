/********************************************************************************
** Form generated from reading UI file 'configure.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Configure
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Configure)
    {
        if (Configure->objectName().isEmpty())
            Configure->setObjectName(QStringLiteral("Configure"));
        Configure->resize(322, 126);
        gridLayout = new QGridLayout(Configure);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(Configure);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(Configure);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(Configure);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 2);


        retranslateUi(Configure);
        QObject::connect(buttonBox, SIGNAL(accepted()), Configure, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Configure, SLOT(reject()));

        QMetaObject::connectSlotsByName(Configure);
    } // setupUi

    void retranslateUi(QDialog *Configure)
    {
        Configure->setWindowTitle(QApplication::translate("Configure", "Dialog", 0));
        label->setText(QApplication::translate("Configure", "Port:", 0));
    } // retranslateUi

};

namespace Ui {
    class Configure: public Ui_Configure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURE_H
