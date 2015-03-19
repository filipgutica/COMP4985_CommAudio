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
                || (buffer->pos() >= 0 && keepPlaying))
            {
                keepPlaying = true;

                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->read(BYTES_PER_SECOND), BYTES_PER_SECOND);
                msleep(10);
                //qDebug() << " Audio side: " << buffer->pos();
                //ioOutput->waitForBytesWritten(10);

                if (nBytes >= AUDIO_BUFFSIZE)
                    nBytes = 0;
            }
            else
                keepPlaying = false;
        }
    }
}


