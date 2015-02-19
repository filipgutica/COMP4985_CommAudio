#ifndef SERVER
#define SERVER

#include <QDebug>
#include <stdio.h>
#include <WinSock2.h>
#include "ui_application.h"
#pragma comment(lib,"WS2_32")

#define PORT 5150
#define DATA_BUFSIZE 8192

typedef struct _SOCKET_INFORMATION {
   OVERLAPPED Overlapped;
   SOCKET Socket;
   CHAR Buffer[DATA_BUFSIZE];
   WSABUF DataBuf;
   DWORD BytesSEND;
   DWORD BytesRECV;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;

void StartServer(int port, QTextBrowser *log);
void CALLBACK WorkerRoutine(DWORD Error, DWORD BytesTransferred,LPWSAOVERLAPPED Overlapped, DWORD InFlags);
DWORD WINAPI ListenThread(LPVOID lpParameter);
DWORD WINAPI WorkerThread(LPVOID lpParameter);


#endif // SERVER

