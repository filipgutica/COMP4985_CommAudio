#ifndef VOIP_H
#define VOIP_H

#include <QDialog>
#include <QDebug>
#include <QUdpSocket>
#include <QAudioRecorder>
#include <QAudioProbe>
#include <QAudioBuffer>
#include <QByteArray>

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
    void on_acceptCallBtn_clicked();
    void processBuffer(QAudioBuffer buffer);

private:
    Ui::Voip *ui;
    QString ip;
    QString port;
    QAudioRecorder* audioRecorder;
    QAudioProbe* audioProbe;
    QUdpSocket *udpSocket;
};

#endif // VOIP_H
