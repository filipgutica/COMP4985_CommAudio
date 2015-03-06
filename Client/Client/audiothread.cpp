#include "audiothread.h"
#include "globals.h"
#include <QDebug>

AudioThread::AudioThread(QObject *parent) :
    QThread(parent)
{

}

AudioThread::~AudioThread()
{

}

void AudioThread::run()
{
    int nbytes;
    char temp[10000 + 1];

    while (true)
    {
        if (audioOutput != NULL)
        {
           // qDebug() << "Playing music";
            sem2.acquire();
            buffer->open(QIODevice::ReadOnly);

            buffer->read(temp, 10000);

            nbytes = ioOutput->write(temp, 10000);

            sem1.release();

            //break;
        }
    }
}


