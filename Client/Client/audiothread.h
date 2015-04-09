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
    void setType(int);
    void setRunning(bool);

private:

    bool running;
    int type;

};

#endif // AUDIOTHREAD_H
