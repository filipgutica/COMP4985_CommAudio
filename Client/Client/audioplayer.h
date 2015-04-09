#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QDialog>
#include <QtNetwork>
#include <QHostAddress>
#include <QAudioFormat>
#include <QAudioInput>
#include <QDataStream>
#include <QTimer>
#include "audiothread.h"
#include "globals.h"


namespace Ui {
class AudioPlayer;
}

class AudioPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit AudioPlayer(QWidget *parent = 0);
    //AudioPlayer(QString ga,QWidget *parent = 0);
    AudioPlayer(QUdpSocket* udpSocket, QWidget *parent = 0);
    AudioPlayer(QString ga,  bool voipFlag = false, QWidget *parent = 0);
    ~AudioPlayer();
    void setMaxByte(int x);
    void clearBuffers();
    void startAudioThread();

private slots:

    void on_sliderVolume_sliderMoved(float position);

    void processPendingDatagrams();

    void playData(QByteArray d);

    void audioStateChanged(QAudio::State state);

signals:
    void audioReady(QByteArray d);

private:
    Ui::AudioPlayer *ui;
    QUdpSocket *udpSocket;
    QHostAddress groupAddress;
    QAudioFormat format;
    QIODevice *outputDevice;
    QString str;
    QBuffer *buff;
    QByteArray *data;
    QByteArray readyBytes;
    AudioThread *thrd;
    int bytecount;
    int nBytes;
    QTimer *timer;
    int buf_pos;

};

#endif // AUDIOPLAYER_H
