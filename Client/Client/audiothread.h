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
    int nBytes;
    bool streamMode = false;
    int maxBytes = std::numeric_limits<qint8>::max();
    int totalBytes = 0;
};

#endif // AUDIOTHREAD_H
