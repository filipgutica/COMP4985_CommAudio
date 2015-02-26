#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include "audioplayer.h"
#include <WinSock2.h>
#pragma comment(lib,"WS2_32")

namespace Ui {
class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();

private slots:
    void on_actionAudio_Stream_triggered();

    void on_actionMulticast_Stream_triggered();

    void on_actionVOIP_triggered();

private:
    Ui::Application *ui;
};

#endif // APPLICATION_H
