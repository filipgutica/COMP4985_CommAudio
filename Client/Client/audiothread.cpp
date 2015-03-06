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
    while (true)
    {
        if (buffer->size() >= 352800 && audioOutput != NULL)
        {
           // qDebug() << "Playing music";
            sem.acquire();
            buffer->open(QIODevice::ReadOnly);

            ioOutput->write(buffer->data(), buffer->size());
            sem.release();

            //break;
        }
    }
}


