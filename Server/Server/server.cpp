#include "server.h"

SOCKET AcceptSocket, ListenSocket, MulticastSocket;
WSAEVENT AcceptEvent;
Application *mainWindow;
QVector<QString> SongList;
CRITICAL_SECTION critSection;
HANDLE ThreadStream;

void StartServer(int port, LPVOID app, QVector<QString> songList)
{
   WSADATA wsaData;
   INT Ret;
   HANDLE ThreadHandle;
   HANDLE ThreadListenHandle;
   DWORD ThreadId;
   DWORD ThreadIdListen;
   QString strInfo;
   SOCKADDR_IN InternetAddr;

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

    DWORD threadID;
    struct ip_mreq stMreq;
    struct timeval timeout;
    SOCKADDR_IN stLclAddr, stDstAddr;
    HANDLE ThreadMulti;
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


    if ((ThreadMulti = CreateThread(NULL, 0, MulticastThread, (LPVOID) &stDstAddr, 0, &threadID)) == NULL)
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
    QFile *file;
    char temp[AUDIO_BUFFER];
    int i = 0;

    buf = (WSABUF*) malloc(sizeof(WSABUF));

    /* Assign our destination address */
    stDstAddr.sin_family =      AF_INET;
    stDstAddr.sin_addr.s_addr = inet_addr(TIMECAST_ADDR);
    stDstAddr.sin_port =        htons(TIMECAST_PORT);

    int ret;


    for (int j = 0; j < SongList.size(); j++)
    {

        file  = new QFile(SongList.at(j));

        if (!file->open(QIODevice::ReadOnly))
        {
            qDebug() << "cannot find file";
            return 0;
        }

        qDebug() << "Streaming: " << SongList.at(j);

        while ((file->read(temp, AUDIO_BUFFER)))
        {
            buf->buf = temp;
            buf->len = AUDIO_BUFFER;
            ZeroMemory((&ol), sizeof(ol));

            i+= AUDIO_BUFFER;
            Sleep(DELAY);
            if(ret = WSASendTo(MulticastSocket, buf, 1, &sent, 0, (struct sockaddr*)&stDstAddr,sizeof(stDstAddr), ol, NULL) < 0 )
            {
                qDebug() << "Sendto failed error: " << WSAGetLastError();
                return 1;
            }


            file->seek(i);
            memset(temp, 0, sizeof(temp));

        }

        delete file;

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
 * Function:    WorkerRoutine
 *
 * DESIGNER:    Filip Gutica
 *
 * PROGRAMMER:  Filip Gutica    - Wrote initial function, Handle initial
 *                                client connection
 *              Alex Lam        - Handled single stream request
 *              Sebastian Pelka - Handled single stream requests
 *              Sanders Lee     - Handle download requests
 *
 * Returns:
 *              - void
 *
 * Params:
 *              - Error
 *              - BytesTransferred
 *              - Overlapped
 *              - Inflags
 *
 * Notes:
 * Compuletion routine for the TCP control line of this application.
 * Check received data on our TCP control socket, and process client
 * requests.
 *
 * Based off in class completion routine example code by Aman Abdulla
 ******************************************************************/
void CALLBACK WorkerRoutine(DWORD Error, DWORD BytesTransferred, LPWSAOVERLAPPED Overlapped, DWORD InFlags)
{
    DWORD SendBytes, RecvBytes;
    DWORD Flags;
    QString strInfo;
    QRegExp rx("index: *");
    QRegExp rxdown("download: *");
    QRegExp rxStop("stop");
    char temp[TEMP_BUFFSIZE];

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
    ***/
    if (SI->BytesRECV == 0)
    {
        SI->BytesRECV = BytesTransferred;
        SI->BytesSEND = 0;

        ZeroMemory(&(SI->Overlapped), sizeof(WSAOVERLAPPED));

        strInfo = QString("Received: %1 on socket: %2").arg(SI->Buffer).arg(SI->Socket);
        mainWindow->appendToLog(strInfo);

        /***
         *
         * Single stream to client
         *
         ***/
        if (rx.indexIn(SI->Buffer) != -1)
        {
            char *tok = strtok(SI->Buffer, ":");
            tok = strtok(NULL, ":");
            qDebug() << "received " << tok;

            ProcessSongRequest(tok, SI);

            memset(tok, 0, sizeof(tok));
        }

        /***
         *
         * Send requested music file to the client via TCP
         *
         ***/
        if (rxdown.indexIn(SI->Buffer) != -1)
        {
            char *tok = strtok(SI->Buffer, ":");
            tok = strtok(NULL, ":");
            qDebug() << "request to send song #" << tok;
            ProcessDownloadRequest(tok, SI);

            memset(tok, 0, sizeof(tok));
        }

        /***
         *
         * Send requested music file to the client via TCP
         *
         ***/
        if (rxStop.indexIn(SI->Buffer) != -1)
        {
            TerminateThread(ThreadStream, 0);
        }

        /***
         *
         * sends the music list to the client
         *
         ***/
        if (strcmp(SI->Buffer, "tcp") == 0)
        {
            for (int i = 0; i < SongList.size(); i++)
            {
                strcat(temp, (char*)SongList.at(i).toUtf8().constData());
                strcat(temp, "\n");
            }
            SI->DataBuf.buf = temp;
            // SI->DataBuf.len = strlen(temp);
            SI->DataBuf.len = 1024;

            qDebug() << SI->DataBuf.len;

            SendBytes = WriteToSocket(&SI->Socket, &SI->DataBuf, 0, &SI->Overlapped);

        }

        memset(SI->Buffer, 0, sizeof(SI->Buffer));
    }

    /***
     * We are in the completion routine. Therefore a WSARecv call finished so we set the bytes received field to 0
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

/*-------------------------------------------------------------------------------
-- FUNCTION: StartStream()
--
--
-- NOTES:
--
--------------------------------------------------------------------------------*/
DWORD WINAPI StreamThread(LPVOID param)
{
    SOCKET PlayerSocket;
    SOCKADDR_IN dest_addr;
    QString send;
    WSABUF *buf;
    WSABUF *filesize;
    DWORD sent;
    DWORD flags;
    OVERLAPPED *ol;
    char temp[AUDIO_BUFFER];
    int i = 0;
    int ret;

    PLAYER_INFORMATION *info = (PLAYER_INFORMATION*) param;

    buf = (WSABUF*) malloc(sizeof(WSABUF));

    /* Assign our destination address */
    dest_addr.sin_family =      AF_INET;
    dest_addr.sin_addr.s_addr = info->addrIn.sin_addr.s_addr;
    dest_addr.sin_port =        htons(UNICAST_PORT);

    qDebug() << "Destination addr: " << inet_ntoa(dest_addr.sin_addr);
    qDebug() << "Destination port: " << ntohs(dest_addr.sin_port);

    QFile file(SongList.at(info->index));

    qDebug() << "Opening file: " << SongList.at(info->index);

    //open the file for reading
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "cannot find file";
        return 0;
    }

    //create the new UDP socket
    if ((PlayerSocket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    {
       qDebug() << "Failed to get a socket " << WSAGetLastError() << endl;
       return 0;
    }

    //go into a loop and read the file chunk by chunk

    while ((file.read(temp, AUDIO_BUFFER)))
    {
        buf->buf = temp;
        buf->len = AUDIO_BUFFER;
        ZeroMemory((&ol), sizeof(ol));

        i+= AUDIO_BUFFER;
        Sleep(DELAY);
        if(int ret = WSASendTo(PlayerSocket, buf, 1, &sent, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr), ol, NULL) < 0 )
        {
            qDebug() << "Sendto failed error: " << WSAGetLastError();
            return 1;
        }


        //qDebug() << i;
        file.seek(i);
        memset(temp, 0, sizeof(temp));
    }


    return 0;
}

/*-------------------------------------------------------------------------------
-- FUNCTION: DownloadThread()
--
-- DESIGNER: Filip Gutica
--
-- PROGRAMMER: Sanders Lee
--
-- NOTES:
--
--------------------------------------------------------------------------------*/
DWORD WINAPI DownloadThread(LPVOID param)
{
    SOCKET PlayerSocket;
    SOCKADDR_IN dest_addr;
    WSABUF *buf;
    OVERLAPPED *ol;
    char temp[AUDIO_BUFFER];

    PLAYER_INFORMATION *info = (PLAYER_INFORMATION*) param;

    buf = (WSABUF*) malloc(sizeof(WSABUF));

    /* Assign our destination address */
    dest_addr.sin_family =      AF_INET;
    dest_addr.sin_addr.s_addr = info->addrIn.sin_addr.s_addr;
    dest_addr.sin_port =        htons(FILE_TRANSFER_PORT);

    qDebug() << "Destination addr: " << inet_ntoa(dest_addr.sin_addr);
    qDebug() << "Destination port: " << ntohs(dest_addr.sin_port);

    QFile file(SongList.at(info->index));

    qDebug() << "Opening file: " << SongList.at(info->index);

    //open the file for reading
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "cannot find file";
        return 0;
    }

    //create the new TCP socket
    if ((PlayerSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    {
       qDebug() << "Failed to get a socket " << WSAGetLastError() << endl;
       return 0;
    }

    //connect socket to port
    if (connect(PlayerSocket , (struct sockaddr *)&dest_addr , sizeof(dest_addr)) < 0)
    {
        qDebug() << "connection error";
        return 1;
    }

    //go into a loop and read the file chunk by chunk
    while(!file.atEnd())
    {
        buf->len = file.read(temp, AUDIO_BUFFER);
        buf->buf = temp;
        ZeroMemory((&ol), sizeof(ol));
        WriteToSocket(&PlayerSocket, buf, 0, ol);
        qDebug() << "packet sent";
    }

    return 0;
}

void ProcessSongRequest(char *s, LPSOCKET_INFORMATION SI)
{
    SOCKADDR_IN client_addr;
    DWORD ThreadStreamId;
    PLAYER_INFORMATION *playerInfo;
    playerInfo = (PLAYER_INFORMATION*)malloc(sizeof(PLAYER_INFORMATION));
    char temp[TEMP_BUFFSIZE];

    //find the index'th song in the vector
    QString filepath = SongList.at(atoi(s));

    //get the file Qfile
    QFile file(filepath);

    //get the file size
    int filesize = file.size();

    //put info in the buffer
    sprintf(temp, "size:%d", filesize);

    SI->DataBuf.buf = temp;
    SI->DataBuf.len = 1024;

    int client_size = sizeof(client_addr);
    getpeername(SI->Socket, (PSOCKADDR) &client_addr, &client_size);

    //write metadata to the TCP control line
    WriteToSocket(&SI->Socket, &SI->DataBuf, 0, &SI->Overlapped);

    //put data into structure to be sent to the thread
    playerInfo->index = atoi(s);
    playerInfo->addrIn = client_addr;

    //stream song
    if ((ThreadStream = CreateThread(NULL, 0, StreamThread, (LPVOID) playerInfo, 0, &ThreadStreamId)) == NULL)
    {
       qDebug() << "CreateThread failed with error " << GetLastError() << endl;
       return;
    }
}

void ProcessDownloadRequest(char* s, LPSOCKET_INFORMATION SI)
{
    SOCKADDR_IN client_addr;
    HANDLE ThreadDownload;
    DWORD ThreadDownloadId;
    PLAYER_INFORMATION *playerInfo;
    playerInfo = (PLAYER_INFORMATION*)malloc(sizeof(PLAYER_INFORMATION));

    char temp[TEMP_BUFFSIZE];
    //find the index'th song in the vector
    QString filepath = SongList.at(atoi(s));

    //get the file Qfile
    QFile file(filepath);

    //get the file size
    int filesize = file.size();
    qDebug() << "song filesize:" << filesize;

    //put info in the buffer
    sprintf(temp, "size:%d", filesize);

    SI->DataBuf.buf = temp;
    SI->DataBuf.len = 1024;

    int client_size = sizeof(client_addr);
    getpeername(SI->Socket, (PSOCKADDR) &client_addr, &client_size);

    //write metadata to the TCP control line
    WriteToSocket(&SI->Socket, &SI->DataBuf, 0, &SI->Overlapped);
    qDebug() << "successfully wrote song metadata";

    //put data into structure to be sent to the thread
    playerInfo->index = atoi(s);
    playerInfo->addrIn = client_addr;

    //send song file
    if ((ThreadDownload = CreateThread(NULL, 0, DownloadThread, (LPVOID) playerInfo, 0, &ThreadDownloadId)) == NULL)
    {
       qDebug() << "CreateThread failed with error " << GetLastError() << endl;
       return;
    }
}
