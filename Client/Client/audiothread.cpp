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
            }
            else
            {
                keepPlaying = false;
                msleep(500);
            }
        }
    }
}


