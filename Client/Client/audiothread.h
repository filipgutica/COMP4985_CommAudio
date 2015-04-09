/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	audiothread.h -		Headerfile for audiothread class
--
--	PROGRAM:		Server
--
--
--	DATE:			February 9, 2015
--
--	DESIGNERS:		Filip Gutica & Auto-generated
--
--	PROGRAMMER:		Filip Gutica & Auto-generated
--
--	NOTES:
--
---------------------------------------------------------------------------------------*/
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
