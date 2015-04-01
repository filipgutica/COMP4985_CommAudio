#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QtNetwork>

namespace Ui {
class Downloader;
}

class Downloader : public QDialog
{
    Q_OBJECT

public:
    explicit Downloader(QWidget *parent = 0);
    ~Downloader();
    bool SetFileName(QString);
    bool SetBytesExpected(int);
    void StartDownload();

private slots:
    void on_CancelButton_clicked();
    void on_OKButton_clicked();
    void tcpReady();
    void tcpUpdate();

private:
    Ui::Downloader *ui;
    QString filename;
    QFile * file;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    int bytesExpected;
    int bytesReceived;
};

#endif // DOWNLOADER_H
