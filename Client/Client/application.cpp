/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		application.cpp -   Source file for the client UI class
--
--	PROGRAM:			Client.exe
--
--	FUNCTIONS:			Application
--						~Application
--						on_actionAudio_Stream_triggered()
--						on_actionRadio_triggered()
--						on_actionVOIP_triggered()
--						ConnectTCP(QString ip, QString port)
--                      ReadTCP()
--                      WriteTCP(QByteArray data)
--                      UpdatePlaylist()
--                      on_listMusic_doubleClicked(const QModelIndex &index)
--                      on_listMusic_customContextMenuRequested(const QPoint &pos)
--                      SaveNew(QObject * i)
--
--
--	DATE:				March 18 2015
--
--	DESIGNERS:			Alex Lam & Sebastian Pelka
--
--	PROGRAMMERS:		Alex Lam & Sebastian Pelka
--
--	NOTES:
--	Creates and instantiates the server gui. Has functions for loading songs into the playlist
--  and interactions with the UI
---------------------------------------------------------------------------------------*/

#include "application.h"
#include "ui_application.h"
#include "configure.h"
#include "downloader.h"
#include "voip.h"


/*------------------------------------------------------------------------------
--	FUNCTION:       Application()
--
--	PURPOSE:		Constructor, initializes the Ui object containing al ui elemnets
--
--	DESIGNERS:		Auto-generated
--
--	PROGRAMMER:		Auto-generated
/*-----------------------------------------------------------------------------*/
Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    ui->listMusic->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listMusic->setContextMenuPolicy(Qt::CustomContextMenu);

    expectedSize = 0;
    currentSize = 0;

    playlistReceived = false;
    downloadRequested = false;

}

/*------------------------------------------------------------------------------
--	FUNCTION:       ~Application()
--
--	PURPOSE:		Destructor, cleans up the ui. Deletes the ui object
--
--	DESIGNERS:		Auto-generated
--
--	PROGRAMMER:		Auto-generated
/*-----------------------------------------------------------------------------*/
Application::~Application()
{
    delete ui;
}

/*------------------------------------------------------------------------------
--	FUNCTION:       on_actionAudio_Stream_triggered()
--
--	PURPOSE:        Creates a configure dialog to retrieve user IP and Port input
--
--  DATE:			March 18 2015
--
--  REVISIONS:      (Date and Description)
--
--  INTERFACE:      Application::on_actionAudio_Stream_triggered()
--
--  RETURNS:        void
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Application::on_actionAudio_Stream_triggered()
{  
//     Configure *conf = new Configure(this);
//     conf->show();
    Configure conf;
    conf.setModal(true);

    if(conf.exec() == QDialog::Accepted)
    {
        port = conf.getPort();
        ip = conf.getIP();

    }
    qDebug() << "IP" + ip + "\nPORT" + port;
    ConnectTCP(ip, port);

    audPlayer = new AudioPlayer(ip);
}

/*------------------------------------------------------------------------------
--	FUNCTION:       on_actionRadio_triggered()
--
--	PURPOSE:        Generates audio player dialog
--
--  DATE:			March 18 2015
--
--  REVISIONS:      (Date and Description)
--
--  INTERFACE:      Application::on_actionRadio_triggered()
--
--  RETURNS:        void
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Application::on_actionRadio_triggered()
{
    AudioPlayer audPlayer;

    audPlayer.exec();


}

/*------------------------------------------------------------------------------
--	FUNCTION:       on_actionVOIP_triggered()
--
--	PURPOSE:        Generates the voice chat dialog
--
--  DATE:			March 18 2015
--
--  REVISIONS:      (Date and Description)
--
--  INTERFACE:      Application::on_actionVOIP_triggered()
--
--  RETURNS:        void
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Application::on_actionVOIP_triggered()
{
    Voip call;

    call.exec();
}


/*------------------------------------------------------------------------------
--	FUNCTION:       ConnectTCP(QString ip, QString port)
--
--	PURPOSE:        creates a TCP socket with the specified ip and port
--
--  DATE:			March 18 2015
--
--  REVISIONS:      (Date and Description)
--
--  INTERFACE:      Application::ConnectTCP(QString ip, QString port)
--                  param: ip: the IP address to be assigned to the socket
--                  param: port: the port to be assigned to the socket
--
--  RETURNS:        void
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Application::ConnectTCP(QString ip, QString port)
{
    msock = new QTcpSocket( this );
    connect( msock, SIGNAL(readyRead()), SLOT(ReadTCP()) );

    msock->connectToHost(ip, port.toInt());

    char* tcpChar = "tcp";
    QByteArray tcpbytes(tcpChar, sizeof(tcpChar));
    WriteTCP(tcpbytes);
}

/*------------------------------------------------------------------------------
--	FUNCTION:       ReadTCP()
--
--	PURPOSE:        read data from the TCP Control Line
--
--  DATE:			March 18 2015
--
--  REVISIONS:      (Date and Description)
--
--  INTERFACE:      Application::ReadTCP()
--
--  RETURNS:        void
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Application::ReadTCP()
{
    QByteArray data = msock->readAll();
    if(!downloadRequested)
    {
        if(expectedSize == 0) // First read
        {
            expectedSize = 1024;
        }
        playlist.insert(currentSize, data);//might need to read data out and then append it
        currentSize = playlist.size();

        if(playlistReceived)
        {
            char* s = data.data();
        }
        else
        {
            if(currentSize == expectedSize)
            {
                UpdatePlaylist();
                expectedSize = 0;
                currentSize = 0;
                playlistReceived = true;
            }
        }
    }
    else
    {
        // read number of bytes expected from server
        char *tok = strtok(data.data(), ":");
        tok = strtok(NULL, ":");
        int eb = atoi(tok);
        qDebug() << "got song size:" << eb;

        // open up dialog box for download progress
        Downloader dl;
        if( dl.SetFileName(song) &&
            dl.SetBytesExpected(eb) )
        {
            dl.StartDownload();
            dl.exec();
        }

        downloadRequested = false;
    }
}

/*------------------------------------------------------------------------------
--	FUNCTION:       WriteTCP(QByteArray data)
--
--	PURPOSE:        Writes binary data to a TCP socket
--
--  DATE:			March 18 2015
--
--  REVISIONS:      (Date and Description)
--
--  INTERFACE:      Application::WriteTCP(QByteArray data)
--                  param: data: the binary data to be written to the socket
--
--  RETURNS:        void
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Application::WriteTCP(QByteArray data)
{
    if( msock->waitForConnected() ) {
        msock->write( data );
    }
}

/*------------------------------------------------------------------------------
--	FUNCTION:       UpdatePlaylist()
--
--	PURPOSE:        Updates the client side playlist with the server song library
--
--  DATE:			March 18 2015
--
--  REVISIONS:      (Date and Description)
--
--  INTERFACE:      Application::UpdatePlaylist()
--
--  RETURNS:        void
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Application::UpdatePlaylist()
{
    char* songlistRaw = playlist.data();
    QString songlistChar = QString(QLatin1String(songlistRaw));

    qDebug() << songlistChar;

    QStringList songlist = songlistChar.split(QRegExp("[\n]"));

    ui->listMusic->setModel(new QStringListModel(songlist));
}

/*------------------------------------------------------------------------------
--	FUNCTION:       on_listMusic_doubleClicked(const QModelIndex &index)
--
--	PURPOSE:        handles a double click on a song in the song list; sends the
--                  song index to the server.
--
--  DATE:			March 18 2015
--
--  REVISIONS:      (Date and Description)
--
--  INTERFACE:      Application::on_listMusic_doubleClicked(const QModelIndex &index)
--                  param: &index: the address of an integer index of the song list
--
--  RETURNS:        void
--
--	DESIGNERS:		Alex Lam & Sebastian Pelka
--
--	PROGRAMMER:		Alex Lam & Sebastian Pelka
/*-----------------------------------------------------------------------------*/
void Application::on_listMusic_doubleClicked(const QModelIndex &index)
{
    QString qs;
    qs = QString("index: %1").arg(index.row());
    qDebug() << index.row();
    qDebug() << qs;
    QByteArray tcpbytes;
    tcpbytes.append(qs);
    WriteTCP(tcpbytes);

    //QString song = index.data().toString();

    //Call song interface
    //start listening to udp socket on pre-agreed port
    audPlayer->startAudioThread();
    if (audPlayer->exec() == QDialog::Rejected)
    {
        char* bytes = "stop";
        QByteArray data(bytes, sizeof(bytes));
        WriteTCP(data);
        audPlayer->clearBuffers();
    }


    //Expect file size over tcp from server
    qDebug() << index.data().toString();
}

/*------------------------------------------------------------------------------
--	FUNCTION:       on_listMusic_customContextMenuRequested()
--
--	PURPOSE:        Right click on songs in the play list to request download
--
--  DATE:			March 18 2015
--
--  RETURNS:        void
--
--	DESIGNERS:		Filip Gutica & Sanders Lee
--
--	PROGRAMMER:		Filip Gutica & Sanders Lee
/*-----------------------------------------------------------------------------*/
void Application::on_listMusic_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->listMusic->indexAt(pos);

    if ( index.isValid() )
    {
        QMenu * myMenu = new QMenu();
        QAction * myAction = new QAction("Download", this);
        myMenu->addAction(myAction);

        // map the action of clicking on "Download" to calling SaveNew()
        QSignalMapper * mapper = new QSignalMapper((QObject *) myMenu);
        mapper->setMapping(myAction, (QObject *) &index);   // associate index object with "Download"
        connect(myAction, SIGNAL(triggered()), mapper, SLOT(map()));
        connect(mapper, SIGNAL(mapped(QObject *)), this, SLOT(SaveNew(QObject *)));

        myMenu->exec(ui->listMusic->mapToGlobal(pos));
    }
}

/***
 * Clicking on the download option starts the download
 *
 * Designer:    Sanders Lee
 *
 * Programmer:  Sanders Lee
 ***/
void Application::SaveNew(QObject * i)
{
    QModelIndex * index = (QModelIndex *) i;

    if ( index->isValid())
    {
        qDebug() << "Download requested: " << index->row();
        song = index->data().toString().split('/').last();

        // send over download request
        QString qs;
        qs = QString("download: %1").arg(index->row());
        QByteArray tcpbytes;
        tcpbytes.append(qs);
        downloadRequested = true;
        WriteTCP(tcpbytes);
    }
}
