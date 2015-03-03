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

AudioStruct *audioStruct;


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

    player = new QMediaPlayer(0, QMediaPlayer::StreamPlayback);

    audioStruct = new AudioStruct();

    lock = false;

    /*** Connect the audio palyer to the progress slider so they are synchronized ***/
    connect(player, &QMediaPlayer::positionChanged, this, &AudioPlayer::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &AudioPlayer::on_durationChanged);
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
    HANDLE ThreadHandle;
    DWORD ThreadId;

    audioStruct->fmt.setChannelCount(2);
    audioStruct->fmt.setCodec("audio/pcm");
    audioStruct->fmt.setSampleType(QAudioFormat::UnSignedInt);
    audioStruct->fmt.setSampleRate(8000);
    audioStruct->fmt.setSampleSize(8);

    decoder = new QAudioDecoder(this);
    decoder->setAudioFormat(audioStruct->fmt);
    decoder->setSourceFilename(filePath);

    PlayMusic();

    connect(decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));
    decoder->start();



/*
    QAudioBuffer *buff = &decoder->read();
    QBuffer dataBuff;
    dataBuff.setBuffer(&QByteArray::fromRawData((char *)buff->data(), buff->byteCount()));
    // ...
    player->setMedia(NULL, &dataBuff);
    player->setVolume(100);
    player->play();*/
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
    player->pause();
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
    player->play();
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
    player->setPosition(position);
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
    player->setVolume(position);
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
    filePath = file;
    this->setWindowTitle(filePath);
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


void AudioPlayer::readBuffer()
{
    qDebug() << "Buffer ready";

    audioStruct->buff = decoder->read();

    // ...
    /*player->setMedia(NULL, &dataBuff);
    player->setVolume(100);
    player->play();*/
}


void AudioPlayer::PlayMusic()
{
    QAudioOutput *audio = new QAudioOutput(audioStruct->fmt, this);
    audio->setBufferSize(4096);
    QByteArray *data = new QByteArray();

    data->setRawData( (const char*)audioStruct->buff.data(), audioStruct->buff.byteCount() );

    QBuffer *buffer = new QBuffer(data);
    QEventLoop *loop = new QEventLoop(this);
    buffer->open(QIODevice::ReadOnly);
    audio->start(buffer);
    return;
}

DWORD WINAPI AudioThread(LPVOID param)
{
    AudioStruct *audioStruct = (AudioStruct*) param;

    QAudioOutput *audio = new QAudioOutput(audioStruct->fmt, audioStruct->myPlayer);
    audio->setBufferSize(1024);
    QByteArray *data = new QByteArray();


    data->setRawData( (const char*)audioStruct->buff.data(), audioStruct->buff.byteCount() );

    QBuffer *buffer = new QBuffer(data);
    QEventLoop *loop = new QEventLoop(audioStruct->myPlayer);
    buffer->open(QIODevice::ReadOnly);
    audio->start(buffer);


    return 0;
}
