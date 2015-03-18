#include "application.h"
#include "ui_application.h"
#include "configure.h"

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    ui->listMusic->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listMusic->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listMusic, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));

    expectedSize = 0;
    currentSize = 0;
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
    QString port;
    QString ip;


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
    AudioPlayer audPlayer;

    audPlayer.exec();
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
    QByteArray data = msock->readAll();
    /*
    playlist.insert(currentSize, data);

    if(playlist.contains('\n'))
    {
        UpdatePlaylist();
    }
    */


    if(expectedSize == 0) // First read
    {
        /*
        QByteArray a2;
        a2.reserve(sizeof(int));
        for(int i = 0; i < sizeof(int); i++)
        {
            q2.append(data[i]);
        }
        expectedSize =
        */
        expectedSize = 1024;
    }
    playlist.insert(currentSize, data);//might need to read data out and then append it
    currentSize = playlist.size();

    if(currentSize == expectedSize)
    {
        UpdatePlaylist();
        expectedSize = 0;
        currentSize = 0;
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

    QString song = index.data().toString();

    //AudioPlayer audPlayer;

    //audPlayer.setAudio(song);

    //audPlayer.exec();

    qDebug() << index.data().toString();
}

void Application::on_listMusic_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->listMusic->indexAt(pos);

    QMenu myMenu;
    myMenu.addAction("Download");

    if ( index.isValid())
    {
        myMenu.exec(ui->listMusic->mapToGlobal(pos));

        qDebug() << "Download requested: " << index.row();

        QString qs;
        qs = QString("download: %1").arg(index.row());
        qDebug() << index.row();
        qDebug() << qs;
        QByteArray tcpbytes;
        tcpbytes.append(qs);
        WriteTCP(tcpbytes);

        QString song = index.data().toString();

    }
}
