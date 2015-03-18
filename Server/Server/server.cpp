
#include "server.h"

SOCKET AcceptSocket;
SOCKET ListenSocket;
SOCKET MulticastSocket;
QTextBrowser *Log;
WSAEVENT AcceptEvent;
Application *mainWindow;
QVector<QString> SongList;
CRITICAL_SECTION critSection;

void StartServer(int port, LPVOID app, QVector<QString> songList)
{
   WSADATA wsaData;
   SOCKADDR_IN InternetAddr;
   INT Ret;
   HANDLE ThreadHandle;
   HANDLE ThreadListenHandle;
   DWORD ThreadId;
   DWORD ThreadIdListen;
   QString strInfo;

   mainWindow = (Application*) app;

   SongList = songList;

   InitializeCriticalSection(&critSection);

   if ((Ret = WSAStartup(0x0202,&wsaData)) != 0)
   {
     qDebug() << "WSAStartup failed with error " << Ret << endl;
      WSACleanup();
      return;
   }

   if ((ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
   {
      qDebug() << "Failed to get a socket " << WSAGetLastError() << endl;
      return;
   }

   StartMulticast();

   InternetAddr.sin_family = AF_INET;
   InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   InternetAddr.sin_port = htons(port);

   if (bind(ListenSocket, (PSOCKADDR) &InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
   {
      qDebug() << "bind() failed with error " << WSAGetLastError() << endl;
      return;
   }

   if (listen(ListenSocket, 5))
   {
      qDebug() << "listen() failed with error " << WSAGetLastError() << endl;
      return;
   }

   if ((AcceptEvent = WSACreateEvent()) == WSA_INVALID_EVENT)
   {
      qDebug() << "WSACreateEvent() failed with error " << WSAGetLastError() << endl;
      return;
   }

   /*** Displaying results to the log ***/
   strInfo = QString("Server listening on port: %1").arg(port);
   mainWindow->appendToLog(strInfo);
   //mainWindow->show();

   // Create a worker thread to service completed I/O requests. 

   if ((ThreadHandle = CreateThread(NULL, 0, WorkerThread, (LPVOID) AcceptEvent, 0, &ThreadId)) == NULL)
   {
      qDebug() << "CreateThread failed with error " << GetLastError() << endl;
      return;
   }

   // Create listen thread to listen for new connections

   if ((ThreadListenHandle = CreateThread(NULL, 0, ListenThread, (LPVOID) AcceptEvent, 0, &ThreadIdListen)) == NULL)
   {
      qDebug() << "CreateThread failed with error " << GetLastError() << endl;
      return;
   }

}

/***********************************************************
 *
 * Set up the multicast socket
 *
 **********************************************************/
void StartMulticast()
{
    HANDLE hThread;
    DWORD threadID;
    struct ip_mreq stMreq;
    SOCKADDR_IN stLclAddr, stDstAddr;
    char MCAddr[64] = TIMECAST_ADDR;
    u_short nPort = TIMECAST_PORT;
    u_long lTTL = TIMECAST_TTL;
    int ret;
    bool flag;

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



    if ((hThread = CreateThread(NULL, 0, MulticastThread, (LPVOID) &stDstAddr, 0, &threadID)) == NULL)
    {
        qDebug() << "CreateThread failed with error " << GetLastError() << endl;
        return;
    }

}

/**********************************************************************
 *
 * Multicast thread for streaming songs to multicast group.
 *
 *********************************************************************/
DWORD WINAPI MulticastThread(LPVOID lpParameter)
{
    SOCKADDR_IN stDstAddr;
    QString send;
    WSABUF *buf;
    DWORD sent;
    DWORD flags;
    OVERLAPPED *ol;
    char temp[AUDIO_BUFFER];
    int i = 0;

    buf = (WSABUF*) malloc(sizeof(WSABUF));

    /* Assign our destination address */
      stDstAddr.sin_family =      AF_INET;
      stDstAddr.sin_addr.s_addr = inet_addr(TIMECAST_ADDR);
      stDstAddr.sin_port =        htons(TIMECAST_PORT);

    int ret;
    QFile file("../Music/Avicii_-_Levels.wav");

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "cannot find file";
        return 0;
    }

    while(TRUE)
    {
        if ((file.read(temp, AUDIO_BUFFER)))
        {
            buf->buf = temp;
            buf->len = AUDIO_BUFFER;
            ZeroMemory((&ol), sizeof(ol));

            i+= AUDIO_BUFFER;

            Sleep(64);
            if(ret = WSASendTo(MulticastSocket, buf, 1, &sent, 0, (struct sockaddr*)&stDstAddr,sizeof(stDstAddr), ol, NULL) < 0 )
            {
                qDebug() << "Sendto failed error: " << WSAGetLastError();
                return 1;
            }


            file.seek(i);
            memset(temp, 0, sizeof(temp));
        }
        else
        {
            file.seek(0);
        }
    }

    return 0;
}



/**********************************************************************
 *
 * Listen for new connections
 *
 * *******************************************************************/
DWORD WINAPI ListenThread(LPVOID lpParameter)
{
    while(TRUE)
    {
        AcceptSocket = accept(ListenSocket, NULL, NULL);

        if (WSASetEvent(AcceptEvent) == FALSE)
        {
            qDebug() << "WSASetEvent failed with error " << WSAGetLastError() << endl;
            return 0;
        }
    }
}

DWORD WINAPI WorkerThread(LPVOID lpParameter)
{
   DWORD Flags;
   LPSOCKET_INFORMATION SocketInfo;
   WSAEVENT EventArray[1];
   DWORD Index;
   DWORD RecvBytes, SendBytes;
   QString strInfo;

   // Save the accept event in the event array.

   EventArray[0] = (WSAEVENT) lpParameter;

   while(TRUE)
   {
      // Wait for accept() to signal an event and also process WorkerRoutine() returns.

        while(TRUE)
        {
            Index = WSAWaitForMultipleEvents(1, EventArray, FALSE, WSA_INFINITE, TRUE);

            if (Index == WSA_WAIT_FAILED)
            {
                qDebug() << "WSAWaitForMultipleEvents failed with error " << WSAGetLastError() << endl;
                return FALSE;
            }

            if (Index != WAIT_IO_COMPLETION)
            {
                // An accept() call event is ready - break the wait loop
                break;
            }
        }

        WSAResetEvent(EventArray[Index - WSA_WAIT_EVENT_0]);

        // Create a socket information structure to associate with the accepted socket.

        if ((SocketInfo = (LPSOCKET_INFORMATION) GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
        {
            qDebug() << "GlobalAlloc() failed with error " << GetLastError() << endl;
            return FALSE;
        }

        // Fill in the details of our accepted socket.

        SocketInfo->Socket = AcceptSocket;
        ZeroMemory(&(SocketInfo->Overlapped), sizeof(WSAOVERLAPPED));
        SocketInfo->BytesSEND = 0;
        SocketInfo->BytesRECV = 0;
        SocketInfo->DataBuf.len = DATA_BUFSIZE;
        SocketInfo->DataBuf.buf = SocketInfo->Buffer;

        Flags = 0;

        /***
        * Post WSARecv on the socket to begin receiving data on it.
        ***/
        RecvBytes = ReadSocket(&SocketInfo->Socket, &SocketInfo->DataBuf, Flags, &SocketInfo->Overlapped);
        qDebug() << "Socket  " << AcceptSocket << "connected" << endl;
        strInfo = QString("Accepted connection: %1").arg(AcceptSocket);
        mainWindow->appendToLog(strInfo);



    }

    return TRUE;
}

/*******************************************************************
 *
 * Completion routine
 *
 ******************************************************************/
void CALLBACK WorkerRoutine(DWORD Error, DWORD BytesTransferred, LPWSAOVERLAPPED Overlapped, DWORD InFlags)
{
    DWORD SendBytes, RecvBytes;
    DWORD Flags;
    QString strInfo;

    char temp[1024];

    // Reference the WSAOVERLAPPED structure as a SOCKET_INFORMATION structure
    LPSOCKET_INFORMATION SI = (LPSOCKET_INFORMATION) Overlapped;

    if (Error != 0)
    {
        qDebug() << "I/O operation failed with error " << Error << endl;
    }

    if (Error != 0 || BytesTransferred == 0)
    {
        qDebug() << "Closing socket " << SI->Socket << endl;
        strInfo = QString("Closing socket: %1").arg(SI->Socket);
        mainWindow->appendToLog(strInfo);

        closesocket(SI->Socket);
        GlobalFree(SI);
        return;
    }

   // Check to see if the BytesRECV field equals zero. If this is so, then
   // this means a WSARecv call just completed so update the BytesRECV field
   // with the BytesTransferred value from the completed WSARecv() call.

   /***
    * We will process client requests here
    * Check for requested songs, start UDP thread etc...
    ***/
    if (SI->BytesRECV == 0)
    {
        SI->BytesRECV = BytesTransferred;
        SI->BytesSEND = 0;

        ZeroMemory(&(SI->Overlapped), sizeof(WSAOVERLAPPED));

        strInfo = QString("Received: %1 on socket: %2").arg(SI->Buffer).arg(SI->Socket);
        mainWindow->appendToLog(strInfo);

        /***
         * Here we should check for a client mode.
         * If the clients mode is stream.. we send over the list.
         * Im leaving it up to you to set up the way a client sends over its mode.
         ***/

         //qDebug() << "before regex: " << SI->Buffer;

         QRegExp rx("index: *");

        if (rx.indexIn(SI->Buffer) != -1)
        {
            qDebug() << "received " << SI->Buffer;
        }


        if (strcmp(SI->Buffer, "tcp") == 0)
        {
            for (int i = 0; i < SongList.size(); i++)
            {
                strcat(temp, (char*)SongList.at(i).toUtf8().constData());
                strcat(temp, "\n");

            }
            SI->DataBuf.buf = temp;
//            SI->DataBuf.len = strlen(temp);
            SI->DataBuf.len = 1024;

            qDebug() << SI->DataBuf.len;

            SendBytes = WriteToSocket(&SI->Socket, &SI->DataBuf, 0, &SI->Overlapped);

        }
    }

    /***
     * We are in the completion port. Therefore a WSARecv call finished so we set the bytes received field to 0
     * We then post another WSARecv call to continue receiving data on this socket.
     ***/
    SI->BytesRECV = 0;

    ZeroMemory(&(SI->Overlapped), sizeof(WSAOVERLAPPED));
    Flags = 0;
    SI->DataBuf.len = DATA_BUFSIZE;
    SI->DataBuf.buf = SI->Buffer;
    SI->BytesRECV = 0;
    RecvBytes = ReadSocket(&SI->Socket, &SI->DataBuf, Flags, &SI->Overlapped);
}

/*------------------------------------------------------------------------------
--	FUNCTION: WriteToSocket()
--
--	PURPOSE:		Wrapper function for writing data to a WSASocket using
--					WSASend and overlapped structures
--
--	PARAMETERS:
--			SOCKET *sock		-Socket to write to
--			WSABUF *buf			-Buffer to be written
--			WSAOVERLAPPED *ol	-Overlapped structure to be used for Overlapped I/O
--
--	Return:
            DWORD	Number of bytes written.
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
--
/*-----------------------------------------------------------------------------*/
DWORD WriteToSocket(SOCKET *sock, WSABUF *buf, DWORD fl, WSAOVERLAPPED *ol)
{
    DWORD sb;

    if (WSASend(*sock, buf, 1, &sb, 0, ol, NULL) == SOCKET_ERROR)
    {
        if (WSAGetLastError() != ERROR_IO_PENDING)
        {
            qDebug() << "WSASend() failed with error " << WSAGetLastError();
            return 0;
        }
    }

    return sb;
}

/*------------------------------------------------------------------------------
--	FUNCTION: ReadSocket()
--
--	PURPOSE:		Wrapper function for receiving data from a WSASocket using
--					WSARecv and overlapped structures
--
--	PARAMETERS:
--			SOCKET *sock		-Socket to receive from
--			WSABUF *buf			-Receive buffer
--			DWORD fl			-Flags
--			WSAOVERLAPPED *ol	-Overlapped structure to be used for Overlapped I/O
--
--	Return:
            DWORD	Number of bytes written.
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
--
/*-----------------------------------------------------------------------------*/
DWORD ReadSocket(SOCKET *sock, WSABUF *buf, DWORD fl,  WSAOVERLAPPED *ol)
{
    DWORD rb;

    if (WSARecv(*sock, buf, 1, &rb, &fl, ol, WorkerRoutine) == SOCKET_ERROR)
    {
        if (WSAGetLastError() != ERROR_IO_PENDING)
        {
            qDebug() << "WSASRecv() failed with error " << WSAGetLastError();
            return 0;
        }

    }

    return rb;
}


