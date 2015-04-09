/*------------------------------------------------------------------------------------------------------------------
--  SOURCE FILE: downloader.cpp - A dialog box dedicated to client TCP file download
--
--  PROGRAM:     CommAudio
--
--  FUNCTIONS:   Downloader(QWidget *parent) : QDialog(parent), ui(new Ui::Downloader);
--               Downloader::~Downloader();
--               bool Downloader::SetFileName(QString fname);
--               bool Downloader::SetBytesExpected(int eb);
--               void Downloader::StartDownload();
--               void Downloader::tcpReady();
--               void Downloader::tcpUpdate();
--               void Downloader::on_CancelButton_clicked();
--               void Downloader::on_OKButton_clicked();
--
--  DATE:        April 08, 2015
--
--  REVISIONS:   (Date and Description)
--
--  DESIGNER:    Sanders Lee
--               Sebastian Pelka
--
--  PROGRAMMER:  Sanders Lee
--
--  NOTES:
--       This dedicates a dialog window to file download so we can see download progress, cancel the download, and
--  prevent the user from downloading other files while one is already in progress.
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:   SetFileName
--
--  DATE:       April 08, 2015
--
--  REVISIONS:  (Date and Description)
--
--  DESIGNER:   Sanders Lee
--              Sebastian Pelka
--
--  PROGRAMMER: Sanders Lee
--
--  INTERFACE:  bool Downloader::SetFileName(QString fname)
--  QString fname: the file name to save the file as
--
--  RETURNS:    success of file open for write, as a boolean value
--
--  NOTES:
--      Opens a file for writing. File name is given by the user.
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:   SetBytesExpected
--
--  DATE:       April 08, 2015
--
--  REVISIONS:  (Date and Description)
--
--  DESIGNER:   Sanders Lee
--
--  PROGRAMMER: Sanders Lee
--
--  INTERFACE:  bool Downloader::SetBytesExpected(int eb)
--  int eb: the expected file size, in bytes
--
--  RETURNS:    whether the expected number of bytes is a valid value, as a boolean value
--
--  NOTES:
--      Sets the number of bytes the file is expected to have.
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:   StartDownload
--
--  DATE:       April 08, 2015
--
--  REVISIONS:  (Date and Description)
--
--  DESIGNER:   Sanders Lee
--
--  PROGRAMMER: Sanders Lee
--
--  INTERFACE:  void Downloader::StartDownload()
--
--  RETURNS:    nothing
--
--  NOTES:
--      Initializes UI elements to their proper initial states, and then waits for a TCP connection as a "server".
--  The incoming TCP connection is from the actual server application, which will send over a file.
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:   tcpReady
--
--  DATE:       April 08, 2015
--
--  REVISIONS:  (Date and Description)
--
--  DESIGNER:   Sanders Lee
--
--  PROGRAMMER: Sanders Lee
--
--  INTERFACE:  void Downloader::tcpReady()
--
--  RETURNS:    nothing
--
--  NOTES:
--      If there's an incoming connection, take just that one socket connection and link it with the update function.
--  Immediately after, shut down the listening "server" on this end because we don't need any more connections for
--  this dialog box.
----------------------------------------------------------------------------------------------------------------------*/
void Downloader::tcpReady()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(tcpUpdate()));
    tcpServer->close();
}

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:   tcpUpdate
--
--  DATE:       April 08, 2015
--
--  REVISIONS:  (Date and Description)
--
--  DESIGNER:   Sanders Lee
--
--  PROGRAMMER: Sanders Lee
--
--  INTERFACE:  void Downloader::tcpUpdate()
--
--  RETURNS:    nothing
--
--  NOTES:
--      Whenever the socket receives a packet, write the data to file, update the progress bar, and check whether
--  we have enough bytes. If we have enough bytes, the file download is complete, and we can close the file and
--  enable the OK button so the user can exit the dialog box properly. We don't need to put this function in a loop
--  because QT's connect/slotting function automatically does repeated asynchronous checks for us.
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:   on_CancelButton_clicked
--
--  DATE:       April 08, 2015
--
--  REVISIONS:  (Date and Description)
--
--  DESIGNER:   Sanders Lee
--
--  PROGRAMMER: Sanders Lee
--
--  INTERFACE:  void Downloader::on_CancelButton_clicked()
--
--  RETURNS:    nothing
--
--  NOTES:
--      If the user clicks the cancel button, stop the file download and close the TCP socket connection.
--  Return to the parent window after.
----------------------------------------------------------------------------------------------------------------------*/
void Downloader::on_CancelButton_clicked()
{
    totalRBytes = 0;
    // download cancelled, close socket and do other stuff
    if(file != NULL)
    {
        file->deleteLater();
        file->close();
    }
    if (tcpSocket != NULL)
        tcpSocket->close();
    this->accept();
}

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:   on_OKButton_clicked
--
--  DATE:       April 08, 2015
--
--  REVISIONS:  (Date and Description)
--
--  DESIGNER:   Sanders Lee
--
--  PROGRAMMER: Sanders Lee
--
--  INTERFACE:  void Downloader::on_OKButton_clicked()
--
--  RETURNS:    nothing
--
--  NOTES:
--      Once the download is complete, the OK button is enabled, and the user can click this to move back to the
--  parent window.
----------------------------------------------------------------------------------------------------------------------*/
void Downloader::on_OKButton_clicked()
{
    this->accept();
}
