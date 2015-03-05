#ifndef MULTICASTTHREAD_H
#define MULTICASTTHREAD_H

#include <QThread>
#include <QtNetwork>

class MulticastThread : public QThread
{
    Q_OBJECT
public:
    explicit MulticastThread(QObject *parent = 0);
    ~MulticastThread();
    void run();

signals:
    void bufferFillCountChanged(int bCount);
    void producerCountChanged(int count);

public slots:
    void processPendingDatagrams();
};

#endif // MULTICASTTHREAD_H
