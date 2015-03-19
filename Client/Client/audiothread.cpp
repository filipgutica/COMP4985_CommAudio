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
    // bool keepPlaying = false;
    buffer->open(QIODevice::ReadOnly);

    while (true)
    {
        msleep(10);
        if (audioOutput != NULL)
        {
            if (buffer->size() >= HIGH_WATERMARK)
               // || (buffer->size() >= LOW_WATERMARK && keepPlaying))
            {
                //keepPlaying = true;

                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->read(BYTES_PER_SECOND), BYTES_PER_SECOND);
                qDebug() << " Audio buffer: " << nBytes;
                ioOutput->waitForBytesWritten(990);

                if (nBytes >= AUDIO_BUFFSIZE)
                    nBytes = 0;
            }
            //else
            //    keepPlaying = false;
        }
    }
}


