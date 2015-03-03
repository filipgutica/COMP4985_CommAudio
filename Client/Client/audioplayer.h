#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#define AUDIO_BUFFSIZE 4096

#include <QDialog>
#include <QtMultimedia/QMediaPlayer>
#include <QtNetwork>
#include <QHostAddress>
#include <QAudioFormat>
#include <QAudioOutput>

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

private:
    Ui::AudioPlayer *ui;
    QMediaPlayer *player;
    QString filePath;

    QUdpSocket *udpSocket;
    QHostAddress groupAddress;
    QAudioFormat format;
    QAudioOutput *audio;
    QIODevice *ioDevice;
    QByteArray data;

    void writeData(QByteArray data);
};

#endif // AUDIOPLAYER_H
