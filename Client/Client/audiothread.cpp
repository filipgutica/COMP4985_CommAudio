#include "audiothread.h"
#include "globals.h"
#include <QDebug>


int nBytes = 0;
int totalNBytes = 0;

int HIGH_WATERMARK = BYTES_PER_SECOND * 5;

/*------------------------------------------------------------------------------
--	FUNCTION:       AudioThread(QObject *parent
--
--	PURPOSE:        Constructor for AudioThread
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
AudioThread::AudioThread(QObject *parent) :
    QThread(parent)
{
    running = true;
    streamMode = false;
    maxBytes = 1000000000;
    totalBytes = 0;
}

/*------------------------------------------------------------------------------
--	FUNCTION:       ~AudioThread()
--
--	PURPOSE:        Destructor for AudioThread
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
--	PURPOSE:        Allows the programmer to set the amount of data that will be
--                  buffered by the audio thread
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void AudioThread::setType(int t)
{
    type = t;

    if (type == VOIP)
        HIGH_WATERMARK = BYTES_PER_SECOND;
    else if (type == STREAM)
        HIGH_WATERMARK = BYTES_PER_SECOND * 5;
    else
        HIGH_WATERMARK = BYTES_PER_SECOND * 5;
}

/*------------------------------------------------------------------------------
--	FUNCTION:       setRunning(bool r)
--
--	PURPOSE:        sets the running boolean
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void AudioThread::setRunning(bool r)
{
    running = r;
}

/*------------------------------------------------------------------------------
--	FUNCTION:       run()
--
--	PURPOSE:        writes to the buffer from the UDP socket
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void AudioThread::run()
{
    bool enoughBuffering = false;
    //int extendingWaitTime = 1000;
    buffer->open(QIODevice::ReadOnly);

    while (running)
    {
        qDebug() << totalNBytes << " " << totalBytesWritten << " " << HIGH_WATERMARK << " " << totalBytesWritten - totalNBytes;
        if (audioOutput != NULL)
        {
            if ((totalNBytes + HIGH_WATERMARK) < totalBytesWritten)   // when we have more than 5s worth of music
                enoughBuffering = true;

            if (enoughBuffering && ((totalNBytes) <= totalBytesWritten)) // when we have at least 1s worth of music
            {

                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->read(BYTES_TO_WRITE), BYTES_TO_WRITE);


                if (buffer->pos() >= AUDIO_BUFFSIZE)
                    nBytes = 0;

                totalNBytes += BYTES_TO_WRITE;

                //If single stream mode is set, then check if you have recied the max size of the song, if reached, end thread
              /*  if(streamMode == true)
                {
                    totalBytes += BYTES_TO_WRITE;
                    if( totalBytes >= maxBytes)
                    {
                        break;
                    }
                }*/

            }

        }
        msleep(DELAY);
    }
}

/*------------------------------------------------------------------------------
--	FUNCTION:       setMaxBytes(int x)
--
--	PURPOSE:        sets the Maximum number of bytes
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
--
--  NOTES:          THIS FUNCTION HAS BEEN RETIRED; WE ARE KEEPING IT HERE FOR
--                  REFERENCE IN CASE IT IS NEEDED LATER.
/*-----------------------------------------------------------------------------*/
void AudioThread::setMaxBytes(int x)
{
    qDebug() << "oooooooh myyyy ghat";
   // maxBytes = x;
    streamMode = true;
}


