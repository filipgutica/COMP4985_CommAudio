/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		audiplayer.cpp -   Audi player window for controlling audio.
--
--	PROGRAM:			Server.exe
--
--	FUNCTIONS:			Application
--						~Application
--						on_pushButton_clicked()
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

QSemaphore sem1(100);
QSemaphore sem2(0);

/*------------------------------------------------------------------------------
--	FUNCTION: AudioPlayer()
--
--	PURPOSE:		Constructor, initializes the Ui object containing al ui elemnets
--
--	DESIGNERS:		Auto-generated
--
--	PROGRAMMER:		Auto-generated
/*-----------------------------------------------------------------------------*/
AudioPlayer::AudioPlayer(QWidget *parent) : QDialog(parent), ui(new Ui::AudioPlayer)
{

    ui->setupUi(this);

    //buff = new QBuffer();
    buffer = new QBuffer();


    // Hardcoded multicast address
    groupAddress = QHostAddress("234.5.6.7");

    // Setup the muticast socket
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 7575);
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

    /*timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerEvent()));

    timer->setInterval(15 * 9);//*/

    //For reading directly from the socket... no buferring
    ioOutput = audioOutput->start();

   // writeMoreData();

    thrd = new AudioThread(this);

    thrd->start();
}

/*------------------------------------------------------------------------------
--	FUNCTION: ~Application()
--
--	PURPOSE:		Destructor, cleans up the ui. Deletes the ui object
--
--	DESIGNERS:		Auto-generated
--
--	PROGRAMMER:		Auto-generated
/*-----------------------------------------------------------------------------*/
AudioPlayer::~AudioPlayer()
{
    // Close the socket
    buffer->close();
    udpSocket->close();
    thrd->terminate();
    delete ui;
}

/*------------------------------------------------------------------------------
--	FUNCTION: on_btnPlay_clicked()
--
--	PURPOSE:		When play button is played. Sets the media to the current song,
--                  sets the volume, then plays the media.
--
--	PARAMETERS:
--		void
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::on_btnPlay_clicked()
{
    /* No more mediaplayer
    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(100);
    player->play();
    */
}

/*------------------------------------------------------------------------------
--	FUNCTION: on_btnPause_clicked()
--
--	PURPOSE:		Pauses the media player when pause button pressed
--
--	PARAMETERS:
--		void
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::on_btnPause_clicked()
{
    //player->pause();
}

/*------------------------------------------------------------------------------
--	FUNCTION: on_btnPause_clicked()
--
--	PURPOSE:		resumes the media player when resume button pressed
--
--	PARAMETERS:
--		void
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::on_btnResume_clicked()
{
    //player->play();
}

/*------------------------------------------------------------------------------
--	FUNCTION: on_sliderProgress_sliderMoved()
--
--	PURPOSE:		sets the position of the player based on the slider position
--
--	PARAMETERS:
--		int position    Position of the slider
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::on_sliderProgress_sliderMoved(int position)
{
    //player->setPosition(position);
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
    //player->setVolume(position);
}

/*------------------------------------------------------------------------------
--	FUNCTION: setAudio(QString)
--
--	PURPOSE:		Set the audio file
--
--	PARAMETERS:
--		QString file    Path to the audio file to be played
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::setAudio(QString file)
{
    //filePath = file;
    //this->setWindowTitle(filePath);
}

/*------------------------------------------------------------------------------
--	FUNCTION: on_positionChanged(qint64)
--
--	PURPOSE:		update the position of the slider as the audio progresses
--
--	PARAMETERS:
--		qint64 position    position that the audio player is in the current song
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
}

/*------------------------------------------------------------------------------
--	FUNCTION: on_durationChanged(qint64)
--
--	PURPOSE:		update the position of the slider as the audio progresses
--
--	PARAMETERS:
--		qint64 position    position that the audio player is in the current song
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioPlayer::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
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

    //Signal that there is audio ready to be played.
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
    // buffering component... work in progress


    /*if (buf_pos <= 50)
    {
        qDebug() << "Socket side: " << buf_pos;
        data.append(data.data());
        buf_pos++;
    }
    else
    {
        timer->start();
        data.clear();
        buf_pos = 0;
    }*/

    // sem1.acquire();
    buffer->open(QIODevice::ReadWrite);
    buffer->seek(bytecount);
    buffer->write(d.data(), d.size());
    buffer->waitForBytesWritten(10);
    //qDebug() << "Socket side: " << bytecount;

    if (bytecount >= AUDIO_BUFFSIZE)
    {
        bytecount = 0;
        //buffer->seek(0);
        //timer->start();
    }//*/
    // sem2.release();

    // For now, play bytes as they come in.. works for localhost or very fast networks
    // ioOutput->write(d.data(), d.size());

}

// Called when 50ms is ready
void AudioPlayer::onTimerEvent()
{
    if (buffer->size() > 0)
    {
        buffer->open(QIODevice::ReadOnly);

        nBytes += ioOutput->write(buffer->data().constData(), 512);
        qDebug() << "Audio side: " << nBytes;
        ioOutput->waitForBytesWritten(1000);
        buffer->seek(nBytes);


        if (nBytes >= BufferSize)
        {
            nBytes = 0;
            buffer->seek(0);
        }
    }

    if (!data.isEmpty())
    {
        ioOutput->write(data);
    }
}//*/

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
