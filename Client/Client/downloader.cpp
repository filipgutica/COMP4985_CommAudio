#include "downloader.h"
#include "ui_downloader.h"

Downloader::Downloader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Downloader)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    tcpSocket = NULL;
    totalRBytes = 0;
}

Downloader::~Downloader()
{
    delete ui;
}

bool Downloader::SetFileName(QString fname)
{
    filename = fname;

    file = new QFile(filename);
    if(!file->open(QFile::WriteOnly))
    {
        qDebug() << "File open failed.";
        return false;
    }    
    qDebug() << "File" << fname << "ready for write";

    return true;
}

bool Downloader::SetBytesExpected(int eb)
{
    if (eb > 0)
    {
        bytesExpected = eb;
        return true;
    }
    else
    {
        qDebug() << "Not a valid file size.";
        return false;
    }
}

void Downloader::StartDownload()
{
    ui->OKButton->setEnabled(false);
    ui->CancelButton->setEnabled(true);

    // update the progress bar according to bytesReceived / bytesExpected * 100
    ui->ProgressBar->setValue(0);
    ui->ProgressBar->setMaximum(bytesExpected);

    // start tcp server listening
    tcpServer->listen(QHostAddress::Any, 7575);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(tcpReady()));
    qDebug() << "TCP connection ready for download";

    // once connected, start downloading from socket and writing to file
    while (!tcpServer->isListening() && !tcpServer->listen())
    {
        qDebug() << "I'm not listening";
        return;
    }//*/
}

void Downloader::tcpReady()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(tcpUpdate()));
    tcpServer->close();
}

void Downloader::tcpUpdate()
{    
    int rBytes = (int)tcpSocket->bytesAvailable();
    totalRBytes += rBytes;
    file->write(tcpSocket->readAll(), rBytes);
    ui->ProgressBar->setValue(totalRBytes);
    qDebug() << "bytes received:" << totalRBytes << "/" << bytesExpected;

    // download complete, close socket and do other stuff
    if (totalRBytes == bytesExpected)
    {
        totalRBytes = 0;
        file->close();
        tcpSocket->close();
        ui->OKButton->setEnabled(true);
        ui->CancelButton->setEnabled(false);
        qDebug() << "download complete";
    }
}


void Downloader::on_CancelButton_clicked()
{
    totalRBytes = 0;
    // download cancelled, close socket and do other stuff
    if(file != NULL)
    {
        file->close();
        file->deleteLater();
    }
    if (tcpSocket != NULL)
        tcpSocket->close();
    this->accept();
}

void Downloader::on_OKButton_clicked()
{
    this->accept();
}
