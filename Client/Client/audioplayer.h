#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#define AUDIO_BUFFSIZE 60000

#include <QDialog>
#include <QtNetwork>
#include <QHostAddress>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QAudioInput>
#include <QDataStream>


namespace Ui {
class AudioPlayer;
}

class AudioPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit AudioPlayer(QWidget *parent = 0);
    ~AudioPlayer();
    void setAudio(QString);

private slots:
    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_sliderProgress_sliderMoved(int position);

    void on_sliderVolume_sliderMoved(int position);

    void on_positionChanged(qint64 position);

    void on_durationChanged(qint64 position);

    void on_btnResume_clicked();

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
    QAudioOutput *audioOutput;
    QIODevice *outputDevice;
    QString str;
    QBuffer *buff;
    QByteArray data;
    int bytecount;

};

#endif // AUDIOPLAYER_H
