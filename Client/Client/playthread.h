#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>
#include <QAudioOutput>
#include <QIODevice>

class PlayThread :public QThread
{
    public:
        PlayThread(QAudioOutput *audio, QIODevice *ioDevice);
        ~PlayThread();

    protected:
        void run();

    private:
         QAudioOutput *_audio;
         QIODevice *_ioDevice;
};

#endif // PLAYTHREAD_H
