  /*---------------------------------------------------------------------------------------
--	SOURCE FILE:		audiplayer.cpp -   Audio player class for playing audio.
--
--	PROGRAM:			Server.exe
--
--	FUNCTIONS:			AudioPlayer
--                      AudioPlayer
--						~AudioPlayer
--						setMaxByte()
--                      setAudio
--						on_actionConfigure_triggered()
--						appendToLog
--						updatePlaylist
--
--	DATE:				Febuary 19 2015
--
--	DESIGNERS:			Filip Gutica & Auto-generated
--
--	PROGRAMMERS:		Filip Gutica & Auto-generated
--
--	NOTES:
---------------------------------------------------------------------------------------*/
#include "audioplayer.h"
#include "ui_audioplayer.h"
#include "globals.h"

QAudioOutput *audioOutput;
QIODevice *ioOutput;
QBuffer *buffer;

int bytesWritten = 0;
int totalBytesWritten = 0;

/*------------------------------------------------------------------------------
--	FUNCTION: AudioPlayer()
--
--	PURPOSE:		Constructor, initializes the Ui object containing al ui elemnets
--
--	DESIGNERS:	    Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
AudioPlayer::AudioPlayer(QWidget *parent) : QDialog(parent), ui(new Ui::AudioPlayer)
{
    ui->setupUi(this);

    //buff = new QBuffer();
    data = new QByteArray(AUDIO_BUFFSIZE, '\0');
    buffer = new QBuffer(data);

    // Hardcoded multicast address
    groupAddress = QHostAddress("234.5.6.7");

    // Setup the muticast socket
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, MULTICAST_PORT);
    udpSocket->joinMulticastGroup(groupAddress);
    udpSocket->setReadBufferSize(AUDIO_BUFFSIZE);

    // Set the audio format
    format.setChannelCount(2);
    format.setSampleRate(44100);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    // Setup the audioOuput address with the desired format
    audioOutput = new QAudioOutput(format, this);
    audioOutput->setBufferSize(AUDIO_BUFFSIZE);

    bytecount = 0;
    nBytes = 0;

    // Connect the udp readyReady signal with the processPendingDatagrams slot
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

    // Connect our custom audioReady signal with the playData slot
    connect(this, SIGNAL(audioReady(QByteArray)), this, SLOT(playData(QByteArray)));

    // Connect audioOutput object's stateChanged signal with our audioStateChanged SLOT to handle state changes in the player
    connect(audioOutput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioStateChanged(QAudio::State)));

    //For reading directly from the socket... no buferring
    ioOutput = audioOutput->start();

    thrd = new AudioThread(this);

    thrd->start();
}

/*------------------------------------------------------------------------------
--	FUNCTION: AudioPlayer(QHostAddress ga)
--
--	PURPOSE:		Second Constructor, initializes the Ui object containing al ui elemnets
--
--	DESIGNERS:		Alex Lam
--
--	PROGRAMMER:		Alex Lam
/*-----------------------------------------------------------------------------*/
AudioPlayer::AudioPlayer(QString ga, bool voipFlag, QWidget *parent) : QDialog(parent), ui(new Ui::AudioPlayer)
{
    ui->setupUi(this);

    //buff = new QBuffer();
    data = new QByteArray(AUDIO_BUFFSIZE, '\0');
    buffer = new QBuffer(data);

    // Hardcoded multicast address
    //groupAddress = QHostAddress("234.5.6.7");
    groupAddress = QHostAddress(ga);

    // Setup the muticast socket
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 7000);
    udpSocket->setReadBufferSize(AUDIO_BUFFSIZE);

    // Set the audio format
    format.setChannelCount(2);
    format.setSampleRate(44100);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    // Setup the audioOuput address with the desired format
    audioOutput = new QAudioOutput(format, this);
    audioOutput->setBufferSize(AUDIO_BUFFSIZE);

    bytecount = 0;
    nBytes = 0;

    // Connect the udp readyReady signal with the processPendingDatagrams slot
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

    // Connect our custom audioReady signal with the playData slot
    connect(this, SIGNAL(audioReady(QByteArray)), this, SLOT(playData(QByteArray)));

    // Connect audioOutput object's stateChanged signal with our audioStateChanged SLOT to handle state changes in the player
    connect(audioOutput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioStateChanged(QAudio::State)));

    //For reading directly from the socket... no buferring
    ioOutput = audioOutput->start();

    thrd = new AudioThread(this);

    if(voipFlag)
    {
        thrd->setType(VOIP);
    }
    else
    {
        thrd->setType(STREAM);
    }

    thrd->start();
}

/*------------------------------------------------------------------------------
--	FUNCTION: AudioPlayer(QUdpSocket gudp)
--
--	PURPOSE:		Constructor, initializes the Ui object containing al ui elemnets
--
--	DESIGNERS:		Alex Lam, Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam, Sebastian Pelka
/*-----------------------------------------------------------------------------*/
AudioPlayer::AudioPlayer(QUdpSocket* udpSocket, QWidget *parent) : QDialog(parent), ui(new Ui::AudioPlayer)
{
    ui->setupUi(this);

    //buff = new QBuffer();
    data = new QByteArray(AUDIO_BUFFSIZE, '\0');
    buffer = new QBuffer(data);

    udpSocket->setReadBufferSize(AUDIO_BUFFSIZE);

    // Set the audio format
    format.setChannelCount(2);
    format.setSampleRate(44100);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    // Setup the audioOuput address with the desired format
    audioOutput = new QAudioOutput(format, this);
    audioOutput->setBufferSize(AUDIO_BUFFSIZE);

    bytecount = 0;
    nBytes = 0;

    // Connect the udp readyReady signal with the processPendingDatagrams slot
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

    // Connect our custom audioReady signal with the playData slot
    connect(this, SIGNAL(audioReady(QByteArray)), this, SLOT(playData(QByteArray)));

    // Connect audioOutput object's stateChanged signal with our audioStateChanged SLOT to handle state changes in the player
    connect(audioOutput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioStateChanged(QAudio::State)));

    //For reading directly from the socket... no buferring
    ioOutput = audioOutput->start();

    thrd = new AudioThread(this);

    thrd->start();
}

/*------------------------------------------------------------------------------
--	FUNCTION:       ~Application()
--
--	PURPOSE:		Destructor, cleans up the ui. Deletes the ui object
--
--	DESIGNERS:		Auto-generated
--
--	PROGRAMMER:		Auto-generated
/*-----------------------------------------------------------------------------*/
AudioPlayer::~AudioPlayer()
{
    delete ui;
}

/*------------------------------------------------------------------------------
--	FUNCTION: on_sliderProgress_sliderMoved()
--
--	PURPOSE:		set the volume of the player
--
--	PARAMETERS:
--		int position    Position of the slider
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::on_sliderVolume_sliderMoved(int position)
{
    audioOutput->setVolume(position);
}


/*------------------------------------------------------------------------------
--	FUNCTION: processPendingDatagrams()
--
--	PURPOSE:		read incomming UDP datagrams from the socket
--
--	PARAMETERS:
--		void
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::processPendingDatagrams()
{
    QByteArray datagram;

    if (udpSocket->hasPendingDatagrams())
    {
        bytecount += udpSocket->pendingDatagramSize();
        //qDebug() << "Bytes: " << bytecount;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
    }


    emit audioReady(datagram);

}

/*------------------------------------------------------------------------------
--	FUNCTION: playData(QByteArray)
--
--	PURPOSE:		write the received bytes to the audio device buffer
--
--	PARAMETERS:
--		QByteArray d    - Bytes to be written
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::playData(QByteArray d)
{
    buffer->open(QIODevice::ReadWrite);
    buffer->seek(bytesWritten);
    buffer->write(d.data(), d.size());
    buffer->waitForBytesWritten(10);
    //qDebug() << "Socket position " << buffer->pos();

    if (bytecount >= AUDIO_BUFFSIZE)
        bytecount = 0;
    bytesWritten = bytecount;
    totalBytesWritten += d.size();
}

/*------------------------------------------------------------------------------
--	FUNCTION: audioStateChanged(QAudio::State)
--
--	PURPOSE:		Handle QAudioOutput state changes
--
--	PARAMETERS:
--		QAudio::State   - current state
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::audioStateChanged(QAudio::State state)
{
    qDebug() << "AudioDevice State changed state: " << state;

}

/*------------------------------------------------------------------------------
--	FUNCTION: clearBuffers()
--
--	PURPOSE:		Clear the audio buffers
--
--	PARAMETERS:
--		void
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::clearBuffers()
{
   QByteArray data;
   buffer->setData(NULL);
   totalNBytes = 0;
   bytesWritten = 0;
   nBytes = 0;
   thrd->setRunning(false);
}

/*------------------------------------------------------------------------------
--	FUNCTION: startAudioThread()
--
--	PURPOSE:		Restart the audio thread
--
--	PARAMETERS:
--		void
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::startAudioThread()
{
   thrd->setRunning(true);
   if (!thrd->isRunning())
    thrd->start();
}
