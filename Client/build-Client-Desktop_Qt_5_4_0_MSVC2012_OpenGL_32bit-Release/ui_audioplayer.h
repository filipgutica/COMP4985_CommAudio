/********************************************************************************
** Form generated from reading UI file 'audioplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOPLAYER_H
#define UI_AUDIOPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioPlayer
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_2;
    QSlider *sliderVolume;

    void setupUi(QWidget *AudioPlayer)
    {
        if (AudioPlayer->objectName().isEmpty())
            AudioPlayer->setObjectName(QStringLiteral("AudioPlayer"));
        AudioPlayer->resize(359, 54);
        formLayoutWidget = new QWidget(AudioPlayer);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(30, 20, 311, 61));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        sliderVolume = new QSlider(formLayoutWidget);
        sliderVolume->setObjectName(QStringLiteral("sliderVolume"));
        sliderVolume->setValue(99);
        sliderVolume->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, sliderVolume);


        retranslateUi(AudioPlayer);

        QMetaObject::connectSlotsByName(AudioPlayer);
    } // setupUi

    void retranslateUi(QWidget *AudioPlayer)
    {
        AudioPlayer->setWindowTitle(QApplication::translate("AudioPlayer", "Audio Player", 0));
        label_2->setText(QApplication::translate("AudioPlayer", "Volume", 0));
    } // retranslateUi

};

namespace Ui {
    class AudioPlayer: public Ui_AudioPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOPLAYER_H
