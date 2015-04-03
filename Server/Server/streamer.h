#ifndef STREAMER_H
#define STREAMER_H

#include <QAudioDecoder>
#include <QBuffer>
#include <QFile>
#include <QAudioFormat>
#include <QString>
#include <QDebug>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <QVector>
#pragma comment(lib,"WS2_32")

#define TIMECAST_ADDR           "234.5.6.7"
#define TIMECAST_PORT           7575
#define TIMECAST_TTL            2

class Streamer : public QObject
{
Q_OBJECT

public:
    Streamer(QVector<QString>);
    Streamer(QString, SOCKADDR_IN);
    void MulticastMode();
    void StartSingleStream();
    void DecodeAudio();

    ~Streamer();

private slots:
    void onBufferReady();

private:
    QString _fname;
    QVector<QString> _playlist;
    QAudioFormat _fmt;
    QFile* _audBuffer;
    SOCKADDR_IN _destAddr;
    SOCKET MulticastSocket;
    QAudioDecoder* _decoder;

};

#endif // STREAMER_H
