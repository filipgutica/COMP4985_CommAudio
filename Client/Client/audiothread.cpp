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

                sem2.acquire();
                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->read(BYTES_PER_SECOND), BYTES_PER_SECOND);
                sem1.release();
                //msleep(32);
                qDebug() << " Audio pos: " << buffer->pos();

                if (nBytes >= AUDIO_BUFFSIZE)
                    nBytes = 0;
            }
            else
            {
                keepPlaying = false;
            }
        }
    }
}


