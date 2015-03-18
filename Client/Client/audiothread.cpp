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

    while (true)
    {
        msleep(10);
        if (audioOutput != NULL)
        {
           // qDebug() << "Playing music";

           // sem2.acquire();
            if (buffer->size() >= (MAX))
            {
                buffer->open(QIODevice::ReadOnly);

                nBytes += ioOutput->write(buffer->data().constData(), 8192);
                qDebug() << "Audio side: " << nBytes;
                ioOutput->waitForBytesWritten(1000);
                buffer->seek(nBytes);

                if (nBytes >= MAX_BUFFSIZE)
                {
                    nBytes = 0;
                    buffer->seek(0);
                }
            }


          //  sem1.release();


            //break;
        }
    }
}


