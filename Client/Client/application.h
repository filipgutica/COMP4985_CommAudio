#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include "audioplayer.h"

namespace Ui {
class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    void ConnectTCP();
    void WriteTCP(QByteArray);
    void UpdatePlaylist();
    ~Application();

private slots:
    void on_actionAudio_Stream_triggered();

    void on_actionVOIP_triggered();

    void on_actionRadio_triggered();

    void ReadTCP();

    void on_listMusic_doubleClicked(const QModelIndex &index);

private:
    Ui::Application *ui;
    //QVector<QString> fileList;

    QTcpSocket *msock;
    QByteArray playlist;
    int expectedSize = 0;
    int currentSize = 0;

};

#endif // APPLICATION_H
