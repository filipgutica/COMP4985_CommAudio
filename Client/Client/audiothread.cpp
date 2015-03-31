#include "audiothread.h"
#include "globals.h"
#include <QDebug>


int nBytes = 0;
int totalNBytes = 0;

AudioThread::AudioThread(QObject *parent) :
    QThread(parent)
{

}

AudioThread::~AudioThread()
{
    streamMode = false;
    maxBytes = 1000000000;
    totalBytes = 0;
}

void AudioThread::run()
{
    bool enoughBuffering = false;
    //int extendingWaitTime = 1000;
    buffer->open(QIODevice::ReadOnly);

    while (true)
    {
        msleep(DELAY);
        // qDebug() << totalNBytes << " " << totalBytesWritten << " " << AUDIO_BUFFSIZE;
        if (audioOutput != NULL)
        {
            if (totalNBytes + HIGH_WATERMARK < totalBytesWritten)   // when we have more than 5s worth of music
                enoughBuffering = true;

            if (enoughBuffering && (totalNBytes + LOW_WATERMARK < totalBytesWritten)) // when we have at least 1s worth of music
            {
                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->read(BYTES_TO_WRITE), BYTES_TO_WRITE);

                if (buffer->pos() >= AUDIO_BUFFSIZE)
                    nBytes = 0;
                totalNBytes += BYTES_TO_WRITE;

<<<<<<< HEAD
                // If single stream mode is set, then check if you have received the max size of the song,
                // if reached, end thread
                if(streamMode == true)
=======
                //If single stream mode is set, then check if you have recied the max size of the song, if reached, end thread
              /*  if(streamMode == true)
>>>>>>> f07df3cf111d2018ef2c1f11ff11d599bfba50d0
                {
                    totalBytes += BYTES_TO_WRITE;
                    if( totalBytes >= maxBytes)
                    {
                        break;
                    }
                }*/

            }
            else
            {
                enoughBuffering = false;
            }
        }
    }
}

void AudioThread::setMaxBytes(int x)
{
    qDebug() << "oooooooh myyyy ghat";
   // maxBytes = x;
    streamMode = true;
}


