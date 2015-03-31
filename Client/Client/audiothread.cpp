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
    maxBytes = 1000000000;
    totalBytes = 0;
}

void AudioThread::run()
{
    bool keepPlaying = false;
    buffer->open(QIODevice::ReadOnly);

    while (true)
    {
        msleep(DELAY);
        if (audioOutput != NULL)
        {
            if (buffer->pos() >= HIGH_WATERMARK
                || (buffer->pos() >= 1 && keepPlaying))
            {
                keepPlaying = true;

              //  sem2.acquire();
                buffer->seek(nBytes);
                nBytes += ioOutput->write(buffer->read(BYTES_TO_WRITE), BYTES_TO_WRITE);

             //   sem1.release();
             //   qDebug() << " Audio pos: " << buffer->pos();

                if (buffer->pos() >= AUDIO_BUFFSIZE)
                    nBytes = 0;

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
            else if (nBytes == bytesWritten)
            {
                msleep(250);
                keepPlaying = false;
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


