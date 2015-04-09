#ifndef VOIP_H
#define VOIP_H

#include <QDialog>
#include <QDebug>
#include <QUdpSocket>
#include <QAudioInput>
#include <QAudioBuffer>
#include <QByteArray>
#include <QBuffer>

namespace Ui {
class Voip;
}

class Voip : public QDialog
{
    Q_OBJECT

public:
    explicit Voip(QWidget *parent = 0);
    ~Voip();
    void recordAudio(QUdpSocket *udpSocket);

private slots:
    void on_makeCallBtn_clicked();
    void processBuffer();

private:
    Ui::Voip *ui;
    QString ip;
    QString port;
    QAudioInput* audioInput;
    QUdpSocket *udpSocket;
    QAudioFormat format;
    QBuffer *voice_buffer;
};

#endif // VOIP_H
