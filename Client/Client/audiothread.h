#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QThread>



class AudioThread : public QThread
{
    Q_OBJECT
public:
    AudioThread(QObject *parent = 0);
    ~AudioThread();
    void run();

private:
    int nBytes;
};

#endif // AUDIOTHREAD_H
