#include "application.h"
#include "ui_application.h"
#include "configure.h"
#include "downloader.h"

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

Application::~Application()
{
    delete ui;
}

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

}

void Application::on_actionRadio_triggered()
{
    AudioPlayer *audPlayer = new AudioPlayer();

    audPlayer->show();
}

void Application::on_actionVOIP_triggered()
{

}


void Application::ConnectTCP(QString ip, QString port)
{
    msock = new QTcpSocket( this );
    connect( msock, SIGNAL(readyRead()), SLOT(ReadTCP()) );

    msock->connectToHost(ip, port.toInt());

    char* tcpChar = "tcp";
    QByteArray tcpbytes(tcpChar, sizeof(tcpChar));
    WriteTCP(tcpbytes);
}

void Application::ReadTCP()
{
    if(!downloadRequested)
    {
        QByteArray data = msock->readAll();
        if(expectedSize == 0) // First read
        {
            expectedSize = 1024;
        }
        playlist.insert(currentSize, data);//might need to read data out and then append it
        currentSize = playlist.size();

        if(playlistReceived)
        {
            char* s = data.data();
            audPlayer->setMaxByte((int)*s);
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
        QByteArray data = msock->readAll();
        char *tok = strtok(data.data(), ":");
        tok = strtok(NULL, ":");
        int eb = atoi(tok);
        qDebug() << "got song size:" << eb;

        // open up dialog box for download progress
        Downloader dl;
        if( dl.SetFileName(song) &&
            dl.SetBytesExpected(eb) )
        {
            dl.exec();
            dl.StartDownload();
        }

        downloadRequested = false;
    }
}

void Application::WriteTCP(QByteArray data)
{
    if( msock->waitForConnected() ) {
        msock->write( data );
    }
}

void Application::UpdatePlaylist()
{
    char* songlistRaw = playlist.data();
    QString songlistChar = QString(QLatin1String(songlistRaw));

    qDebug() << songlistChar;

    QStringList songlist = songlistChar.split(QRegExp("[\n]"));

    ui->listMusic->setModel(new QStringListModel(songlist));
}

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
    audPlayer = new AudioPlayer(ip);

    audPlayer->show();

    //Expect file size over tcp from server

    qDebug() << index.data().toString();
}

/***
 * Right clicking the song opens up the download option.
 *
 * Designer:    Filip Gutica
 *              Sanders Lee
 *
 * Programmer:  Filip Gutica
 *              Sanders Lee
 */
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
 */
void Application::SaveNew(QObject * i)
{
    QModelIndex * index = (QModelIndex *) i;

    if ( index->isValid())
    {
        qDebug() << "Download requested: " << index->row();

        // open file for writing song into
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
