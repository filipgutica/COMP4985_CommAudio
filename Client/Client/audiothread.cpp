#include "audiothread.h"
#include "globals.h"
#include <QDebug>


int nBytes = 0;

AudioThread::AudioThread(QObject *parent) :
    QThread(parent)
{

}

AudioThread::~AudioThread()
{
    streamMode = false;
    maxBytes = 10000000;
    totalBytes = 0;
}

void AudioThread::run()
{
    bool firstTimeBufferFull = false;
    int extendingWaitTime = 1000;
    buffer->open(QIODevice::ReadOnly);

    while (true)
    {
        msleep(DELAY);
        if (audioOutput != NULL)
        {
            // buffer filled to high watermark for the first time
            if(buffer->pos() >= HIGH_WATERMARK)
                firstTimeBufferFull = true;

            if((!firstTimeBufferFull && buffer->pos() >= HIGH_WATERMARK) ||
               (firstTimeBufferFull && nBytes < bytesWritten))
            {
                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->read(BYTES_TO_WRITE), BYTES_TO_WRITE);
                if (buffer->pos() >= AUDIO_BUFFSIZE)
                    nBytes = 0;

                // If single stream mode is set, then check if you have received the max size of the song,
                // if reached, end thread
                if(streamMode == true)
                {
                    totalBytes += BYTES_TO_WRITE;
                    if( totalBytes >= maxBytes)
                    {
                        break;
                    }
                }

            }
            else
            {
                msleep(extendingWaitTime);
                extendingWaitTime += 1000;
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


