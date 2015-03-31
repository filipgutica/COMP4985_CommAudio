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
    void setMaxBytes(int);

private:

    bool streamMode = false;
    int maxBytes = 10000000;
    int totalBytes = 0;
};

#endif // AUDIOTHREAD_H
