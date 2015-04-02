#include "audiothread.h"
#include "globals.h"
#include <QDebug>


int nBytes = 0;
int totalNBytes = 0;

int HIGH_WATERMARK = BYTES_PER_SECOND * 5;


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

void AudioThread::setType(int t)
{
    type = t;

    if (type == VOIP)
        HIGH_WATERMARK = BYTES_PER_SECOND;
    else if (type == STREAM)
        HIGH_WATERMARK = BYTES_PER_SECOND * 5;
    else
        HIGH_WATERMARK = BYTES_PER_SECOND * 5;

    qDebug() << "Buffer set at: " << HIGH_WATERMARK;
}

void AudioThread::run()
{
    bool enoughBuffering = false;
    //int extendingWaitTime = 1000;
    buffer->open(QIODevice::ReadOnly);

    while (true)
    {
        //qDebug() << totalNBytes << " " << totalBytesWritten << " " << HIGH_WATERMARK << " " << totalBytesWritten - totalNBytes;
        if (audioOutput != NULL)
        {
            if ((totalNBytes + HIGH_WATERMARK) < totalBytesWritten)   // when we have more than 5s worth of music
                enoughBuffering = true;

            if (enoughBuffering && ((totalNBytes) <= totalBytesWritten + BYTES_TO_WRITE)) // when we have at least 1s worth of music
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
            else
            {
                enoughBuffering = false;
            }
        }
        msleep(DELAY);
    }
}

void AudioThread::setMaxBytes(int x)
{
    qDebug() << "oooooooh myyyy ghat";
   // maxBytes = x;
    streamMode = true;
}


