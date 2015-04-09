/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		audiothread.cpp -   Class for the audio playing thread
--
--	PROGRAM:			Server.exe
--
--	FUNCTIONS:			AudioThread
--						~AudioThread
--						run()
--						setType()
--						setRunning()
--
--	DATE:				Febuary 19 2015
--
--	DESIGNERS:			Filip Gutica & Auto-generated
--
--	PROGRAMMERS:		Filip Gutica & Auto-generated
--
--	NOTES:
--	Creates and instantiates the server gui. Has functions for loading songs into the playlist
--  and interactions with the UI
---------------------------------------------------------------------------------------*/
#include "audiothread.h"
#include "globals.h"
#include <QDebug>


int nBytes = 0;
int totalNBytes = 0;

int HIGH_WATERMARK = BYTES_PER_SECOND * 5;

/*------------------------------------------------------------------------------
--	FUNCTION:       AudioThread(QObject *parent)
--
--	PURPOSE:		Constructor for the audiothread
--
--	PARAMETERS:
--		parent      - Parent to the calling class
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
AudioThread::AudioThread(QObject *parent) :
    QThread(parent)
{
    running = true;
}

/*------------------------------------------------------------------------------
--	FUNCTION:       ~AudioThread()
--
--	PURPOSE:		Destructor sets running to false
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
AudioThread::~AudioThread()
{
    running = false;
}

/*------------------------------------------------------------------------------
--	FUNCTION:       setType(int t)
--
--	PURPOSE:		Set the type of streaming the thread will be used for
--
--	PARAMETERS:
--		int t       - Type of streaming
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioThread::setType(int t)
{
    type = t;

    if (type == VOIP)        // Voice chat
        HIGH_WATERMARK = BYTES_PER_SECOND;
    else if (type == STREAM) // Single stream
        HIGH_WATERMARK = BYTES_PER_SECOND * 5;
    else                     // Default
        HIGH_WATERMARK = BYTES_PER_SECOND * 5;
}

/*------------------------------------------------------------------------------
--	FUNCTION:       setRunning(bool r)
--
--	PURPOSE:		 Set the running boolean to false
--
--	PARAMETERS:
--		int t       - Type of streaming
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
/*-----------------------------------------------------------------------------*/
void AudioThread::setRunning(bool r)
{
    running = r;
}

/*------------------------------------------------------------------------------
--	FUNCTION:       run()
--
--	PURPOSE:		Worker function for the audio thread
--
--	PARAMETERS:
--		int t       - Writes bytes from the circular buffer to our audio device
--
--	DESIGNERS:		Filip Gutica
--                  Sanders Lee
--
--	PROGRAMMER:		Filip Gutica
--                  Sanders Lee
/*-----------------------------------------------------------------------------*/
void AudioThread::run()
{
    bool enoughBuffering = false;
    //int extendingWaitTime = 1000;
    buffer->open(QIODevice::ReadOnly);

    while (running)
    {
        qDebug() << totalNBytes;
        if (audioOutput != NULL)
        {
            if ((totalNBytes + HIGH_WATERMARK) < totalBytesWritten)   // when we have more than 5s worth of music
                enoughBuffering = true;

            if (enoughBuffering && ((totalNBytes) <= totalBytesWritten))
            {
                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->read(BYTES_TO_WRITE), BYTES_TO_WRITE);

                if (buffer->pos() >= AUDIO_BUFFSIZE)
                    nBytes = 0;

                totalNBytes += BYTES_TO_WRITE;
            }
        }
        msleep(DELAY); // Wait for bytes to finish writing to the audio device
    }
}


