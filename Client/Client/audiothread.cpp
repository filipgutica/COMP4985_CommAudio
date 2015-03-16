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
         msleep(32);
        if (audioOutput != NULL)
        {
           // qDebug() << "Playing music";

           // sem2.acquire();
            if (buffer->size() > 300000)
            {
                buffer->open(QIODevice::ReadOnly);

                nBytes += ioOutput->write(buffer->data().constData(),8000);
                buffer->seek(nBytes);
            }
            else if (nBytes >= MAX_BUFFSIZE)
            {
                nBytes = 0;
                buffer->seek(0);
            }

      //      sem1.release();


            //break;
        }
    }
}


