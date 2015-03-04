#include "playthread.h"

PlayThread::PlayThread(QAudioOutput *audio, QIODevice *ioDevice)
{
    _audio = audio;
    _ioDevice = ioDevice;
}

PlayThread::~PlayThread()
{

}

void PlayThread::run()
{
    while (true)
        _ioDevice = _audio->start();
}
