#include "streamer.h"
#include <QObject>



Streamer::Streamer(QVector<QString> playlist)
{
    _decoder = new QAudioDecoder();
    _playlist = playlist;

    _fmt.setSampleRate(44100);
    _fmt.setChannelCount(2);
    _fmt.setSampleSize(16);
    _fmt.setCodec("audio/pcm");
    _fmt.setByteOrder(QAudioFormat::LittleEndian);
    _fmt.setSampleType(QAudioFormat::UnSignedInt);


    _decoder->setAudioFormat(_fmt);

    _destAddr.sin_family =          AF_INET;
    _destAddr.sin_addr.s_addr =     inet_addr(TIMECAST_ADDR);
    _destAddr.sin_port =            htons(TIMECAST_PORT);

     MulticastMode();

    connect(_decoder, SIGNAL(bufferReady()), this, SLOT(onBufferReady()));

}

Streamer::Streamer(QString fname, SOCKADDR_IN destAddr)
{
    _decoder = new QAudioDecoder();
    _fname = fname;
    _destAddr = destAddr;

    connect(_decoder, SIGNAL(bufferReady()), this, SLOT(onBufferReady()));
}

Streamer::~Streamer()
{

}


void Streamer::MulticastMode()
{

    struct ip_mreq stMreq;
    struct timeval timeout;
    SOCKADDR_IN stLclAddr, stDstAddr;
    char MCAddr[64] = TIMECAST_ADDR;
    u_short nPort = TIMECAST_PORT;
    u_long lTTL = TIMECAST_TTL;
    int ret;
    bool flag;

    timeout.tv_sec = 0;
    timeout.tv_usec = 32000;

    if ((MulticastSocket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    {
       qDebug() << "Failed to get a socket " << WSAGetLastError() << endl;
       return;
    }

    stLclAddr.sin_family      = AF_INET;
    stLclAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* any interface */
    stLclAddr.sin_port        = 0;

    if ((ret = bind(MulticastSocket, (struct sockaddr*) &stLclAddr, sizeof(stLclAddr))) == SOCKET_ERROR)
    {
        qDebug() << "bind failed error: " << WSAGetLastError();
        return;

    }

    stMreq.imr_multiaddr.s_addr = inet_addr(MCAddr);
    stMreq.imr_interface.s_addr = INADDR_ANY;

    if ((ret = setsockopt(MulticastSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&stMreq, sizeof(stMreq))) == SOCKET_ERROR)
    {
        qDebug() << "IP ADD MEMBERSHIP FAILED errorr: " << WSAGetLastError();
        return;
    }

    if ((ret = setsockopt(MulticastSocket, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&lTTL, sizeof(lTTL))) == SOCKET_ERROR)
    {
        qDebug() << "IP MULTICAST TTL failed error: " << WSAGetLastError();
        return;
    }

    if ((ret = setsockopt(MulticastSocket, IPPROTO_IP, IP_MULTICAST_LOOP, (char*)&flag, sizeof(flag))) == SOCKET_ERROR)
    {
        qDebug() << "IP MULTICAST LOOP failed error: " << WSAGetLastError();
        return;
    }

    if ((ret = setsockopt(MulticastSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout))) == SOCKET_ERROR)
    {
        qDebug() << "SO_SENDTIMEO failed: " << WSAGetLastError();
        return;
    }

    DecodeAudio();

}


void Streamer::DecodeAudio()
{


    _decoder->setSourceFilename(_playlist.at(0));
    qDebug() << "Decoding: " << _playlist.at(0);
    _decoder->start();


}

void Streamer::onBufferReady()
{
    WSABUF *buf;
    QAudioBuffer buff = _decoder->read();
    OVERLAPPED *ol;
    int ret;
    DWORD sent;


    qDebug() << "Buffer size: " << buff.byteCount() ;

    buf = (WSABUF*) malloc(sizeof(WSABUF));

    buf->buf = (char*)buff.constData();
    buf->len = buff.byteCount();

    if(ret = WSASendTo(MulticastSocket, buf, 1, &sent, 0, (struct sockaddr*)&_destAddr,sizeof(_destAddr), ol, NULL) < 0 )
    {
        qDebug() << "Sendto failed error: " << WSAGetLastError();
        return;
    }
}
