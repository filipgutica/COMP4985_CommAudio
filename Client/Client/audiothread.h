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

    bool streamMode;
    int maxBytes;
    int totalBytes;
};

#endif // AUDIOTHREAD_H
