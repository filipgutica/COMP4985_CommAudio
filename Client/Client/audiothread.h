#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QThread>

#include "common.h"

class AudioThread : public QThread
{
    Q_OBJECT
public:
    explicit AudioThread(QObject *parent = 0);
    ~AudioThread();
};

#endif // AUDIOTHREAD_H
