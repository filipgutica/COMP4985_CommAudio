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
   // int nbytes;
    bool keepPlaying = false;
    buffer->open(QIODevice::ReadOnly);

    while (true)
    {
        msleep(10);
        if (audioOutput != NULL)
        {
            if (buffer->size() >= HIGH_WATERMARK ||
                (buffer->size() >= LOW_WATERMARK && keepPlaying))
            {
                keepPlaying = true;

                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->data().constData(), 88200);
                qDebug() << " Audio buffer: " << nBytes;
                ioOutput->waitForBytesWritten(1000);

                if (nBytes >= AUDIO_BUFFSIZE)
                    nBytes = 0;
            }
            else
                keepPlaying = false;
        }
    }
}


