#include "voip.h"
#include "ui_voip.h"
#include "configure.h"
#include "audioplayer.h"

Voip::Voip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Voip)
{
    ui->setupUi(this);
}

Voip::~Voip()
{
    delete ui;
}

void Voip::on_makeCallBtn_clicked()
{
    Configure conf;
    conf.setModal(true);

    if(conf.exec() == QDialog::Accepted)
    {
        port = conf.getPort();
        ip = conf.getIP();

    }
    qDebug() << "IP" + ip + "\nPORT" + port;

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress(ip), port.toInt());

    AudioPlayer* ap = new AudioPlayer(udpSocket);
    ap->show();
}

void Voip::recordAudio(QUdpSocket *udpSocket)
{
    audioRecorder = new QAudioRecorder(this);
    audioProbe = new QAudioProbe();

    connect(audioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));

    QAudioEncoderSettings settings;

    settings.setSampleRate(44100);
    settings.setChannelCount(2);
    settings.setBitRate(16);
    settings.setCodec("audio/pcm");
    //settings.setByteOrder(QAudioFormat::LittleEndian);
    //settings.setSampleType(QAudioFormat::UnSignedInt);

    audioRecorder->setEncodingSettings(settings, QVideoEncoderSettings(), NULL);
    audioRecorder->record();

    //read data into a QByteArray



    //shove the contents of the QByteArray into the UDP socket

    //profit
}

void Voip::on_acceptCallBtn_clicked()
{
    qDebug() << "Call Received";
}

void Voip::processBuffer(QAudioBuffer buffer)
{
    QByteArray *audioByteArray;
    *audioByteArray = audioByteArray->fromRawData((char*) buffer.data(), buffer.byteCount());

    udpSocket->writeDatagram((const QByteArray&)audioByteArray, (const QHostAddress&)(ip), (quint16)(port.toInt()));
}
