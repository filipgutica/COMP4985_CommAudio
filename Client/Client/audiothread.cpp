#include "audiothread.h"
#include "globals.h"
#include <QDebug>

AudioThread::AudioThread(QObject *parent) :
    QThread(parent)
{
    nBytes = 0;
}

AudioThread::~AudioThread()
{

}

void AudioThread::run()
{
    bool keepPlaying = false;
    buffer->open(QIODevice::ReadOnly);

    while (true)
    {
        if (audioOutput != NULL)
        {
            if (buffer->pos() >= HIGH_WATERMARK
                || (buffer->pos() >= 1 && keepPlaying))
            {
                keepPlaying = true;

              //  sem2.acquire();
                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->read(BYTES_PER_SECOND/10), BYTES_PER_SECOND/10);
                msleep(32);
                //msleep(200);
             //   sem1.release();
                qDebug() << " Audio pos: " << buffer->pos();

                if (nBytes >= AUDIO_BUFFSIZE)
                    nBytes = 0;

            //If single stream mode is set, then check if you have recied the max size of the song, if reached, end thread
            if(streamMode == true)
            {
                totalBytes += BYTES_PER_SECOND/10;
                if( totalBytes >= maxBytes)
                {
                    break;
                }
            }

            }
            else
            {
                keepPlaying = false;
                msleep(500);
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


