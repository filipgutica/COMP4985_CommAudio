/********************************************************************************
** Form generated from reading UI file 'downloader.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADER_H
#define UI_DOWNLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Downloader
{
public:
    QPushButton *CancelButton;
    QProgressBar *ProgressBar;
    QLabel *DownloadMessage;
    QPushButton *OKButton;

    void setupUi(QDialog *Downloader)
    {
        if (Downloader->objectName().isEmpty())
            Downloader->setObjectName(QStringLiteral("Downloader"));
        Downloader->resize(400, 153);
        CancelButton = new QPushButton(Downloader);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));
        CancelButton->setGeometry(QRect(300, 120, 75, 23));
        ProgressBar = new QProgressBar(Downloader);
        ProgressBar->setObjectName(QStringLiteral("ProgressBar"));
        ProgressBar->setGeometry(QRect(30, 80, 341, 23));
        ProgressBar->setValue(24);
        DownloadMessage = new QLabel(Downloader);
        DownloadMessage->setObjectName(QStringLiteral("DownloadMessage"));
        DownloadMessage->setGeometry(QRect(30, 20, 341, 51));
        OKButton = new QPushButton(Downloader);
        OKButton->setObjectName(QStringLiteral("OKButton"));
        OKButton->setGeometry(QRect(210, 120, 75, 23));

        retranslateUi(Downloader);

        QMetaObject::connectSlotsByName(Downloader);
    } // setupUi

    void retranslateUi(QDialog *Downloader)
    {
        Downloader->setWindowTitle(QApplication::translate("Downloader", "Dialog", 0));
        CancelButton->setText(QApplication::translate("Downloader", "Cancel", 0));
        DownloadMessage->setText(QApplication::translate("Downloader", "Downloading file: ", 0));
        OKButton->setText(QApplication::translate("Downloader", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class Downloader: public Ui_Downloader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADER_H
