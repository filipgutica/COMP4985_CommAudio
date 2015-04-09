/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		voip.cpp -   Provides functions for client to client voice chat
--
--	PROGRAM:			Client.exe
--
--	FUNCTIONS:			Voip(QWidget *parent)
--						~Voip()
--						on_makeCallBtn_clicked()
--						recordAudio(QUdpSocket *udpSocket)
--                      processBuffer()
--
--
--	DATE:				March 22 2015
--
--	DESIGNERS:			Alex Lam & Sebastian Pelka
--
--	PROGRAMMERS:		Alex Lam & Sebastian Pelka
--
--	NOTES:
--	Creates and instantiates the server gui. Has functions for loading songs into the playlist
--  and interactions with the UI
---------------------------------------------------------------------------------------*/
#include "voip.h"
#include "ui_voip.h"
#include "configure.h"
#include "audioplayer.h"

/*------------------------------------------------------------------------------
--	FUNCTION:       Voip(QWidget *parent)
--
--	PURPOSE:        Constructor for a voice chat UI dialog
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
Voip::Voip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Voip)
{
    ui->setupUi(this);
}

/*------------------------------------------------------------------------------
--	FUNCTION:       ~Voip()
--
--	PURPOSE:        Destructor for a voice chat UI dialog
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
Voip::~Voip()
{
    delete ui;
}

/*------------------------------------------------------------------------------
--	FUNCTION:       on_makeCallBtn_clicked()
--
--	PURPOSE:        Creates a dialog to accept user input IP and port
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
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

    QHostAddress testAddress = QHostAddress(ip);

    qDebug() << "bind ip: " << testAddress;
    qDebug() << "plain ip: " << ip;

    AudioPlayer* ap = new AudioPlayer(ip, true);
    ap->show();

    ui->makeCallBtn->setText("Call in progress");

    recordAudio(udpSocket);
}

/*------------------------------------------------------------------------------
--	FUNCTION:       recordAudio(QUdpSocket *udpSocket)
--
--	PURPOSE:        Initializes an IO device to record audio given a socket
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Voip::recordAudio(QUdpSocket *udpSocket)
{

    voice_buffer = new QBuffer();
    qDebug() << "probe and recorder made";

    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = info.nearestFormat(format);
    }

    //audioInput->setEncodingSettings(settings, QVideoEncoderSettings(), NULL);
    audioInput = new QAudioInput(format, this);


    voice_buffer->open(QIODevice::ReadWrite);
    audioInput->start(voice_buffer);
    connect(voice_buffer, SIGNAL(readyRead()), SLOT (processBuffer()));


    qDebug() << "after start called";

    //read data into a QByteArray

    //shove the contents of the QByteArray into the UDP socket

    //profit
}

/*------------------------------------------------------------------------------
--	FUNCTION:       processBuffer()
--
--	PURPOSE:        reads data from a buffer and writes it to a UDP socket
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Voip::processBuffer()
{
 //   voice_buffer->seek(0);

    QByteArray audioByteArray;

    audioByteArray = voice_buffer->buffer();

    //qDebug() << "audio byte array " << audioByteArray;

    //qDebug() << "Audio data" <<  audioByteArray.data();
    //qDebug() << "IP: " << QHostAddress(ip);
    //qDebug() << "Port: " << (quint16)(port.toInt());
    udpSocket->writeDatagram((const QByteArray&)voice_buffer->data(), QHostAddress(ip), (quint16)(port.toInt()));
    voice_buffer->seek(0);
}
