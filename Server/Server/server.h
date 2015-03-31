#ifndef SERVER
#define SERVER

#include <QDebug>
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <QAudioFormat>
#include <QAudioOutput>
#include "ui_application.h"
#include "application.h"
#pragma comment(lib,"WS2_32")

#define PORT            5150
#define DATA_BUFSIZE    64000
#define TIMECAST_ADDR   "234.5.6.7"
#define TIMECAST_PORT   7575
#define UNICAST_PORT    7000
#define TIMECAST_TTL    2
#define AUDIO_BUFFER    8820
#define DELAY           32
#define MULTICAST_FILE_PATH "../Music/Guns_And_Roses-Paradise_City.wav"

typedef struct _SOCKET_INFORMATION {
   OVERLAPPED Overlapped;
   SOCKET Socket;
   CHAR Buffer[DATA_BUFSIZE];
   WSABUF DataBuf;
   DWORD BytesSEND;
   DWORD BytesRECV;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;

typedef struct PLAYER_INFORMATION
{
    int index;
    SOCKADDR_IN addrIn;

} PLAYER_INFORMATION;

void StartServer(int port, LPVOID app, QVector<QString> songList);
void CALLBACK WorkerRoutine(DWORD Error, DWORD BytesTransferred,LPWSAOVERLAPPED Overlapped, DWORD InFlags);
DWORD WINAPI ListenThread(LPVOID lpParameter);
DWORD WINAPI WorkerThread(LPVOID lpParameter);
DWORD WriteToSocket(SOCKET *sock, WSABUF *buf, DWORD fl, WSAOVERLAPPED *ol);
DWORD ReadSocket(SOCKET *sock, WSABUF *buf, DWORD fl,  WSAOVERLAPPED *ol);
DWORD WINAPI MulticastThread(LPVOID lpParameter);
void StartMulticast();
DWORD WINAPI StreamThread(LPVOID param);

#endif // SERVER

