
#include "server.h"

SOCKET AcceptSocket;
SOCKET ListenSocket;
QTextBrowser *Log;
WSAEVENT AcceptEvent;
CRITICAL_SECTION CriticalSection;

void StartServer(int port)
{
   WSADATA wsaData;
   SOCKADDR_IN InternetAddr;
   INT Ret;
   HANDLE ThreadHandle;
   HANDLE ThreadListenHandle;
   DWORD ThreadId;
   DWORD ThreadIdListen;
   QString strInfo;

   InitializeCriticalSection(&CriticalSection);

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
   DWORD RecvBytes;
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
       * Post initial WSARecv on the socket to begin receiving data on it.
       * In order to get any data though, we need to post another WSARecv later on
       ***/
      if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes, &Flags, &(SocketInfo->Overlapped), WorkerRoutine) == SOCKET_ERROR)
      {
         if (WSAGetLastError() != WSA_IO_PENDING)
         {
            qDebug() << "WSARecv() failed with error " << WSAGetLastError() << endl;
            return FALSE;
         }
      }

      qDebug() << "Socket  " << AcceptSocket << "connected" << endl;

      strInfo = QString("Accepted connection: %1").arg(AcceptSocket);

   }

   return TRUE;
}

/*******************************************************************
 *
 * Copletion routine
 *
 ******************************************************************/
void CALLBACK WorkerRoutine(DWORD Error, DWORD BytesTransferred, LPWSAOVERLAPPED Overlapped, DWORD InFlags)
{
   DWORD SendBytes, RecvBytes;
   DWORD Flags;
   QString strInfo;

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

      qDebug () << "Received: " << SI->Buffer << endl;
   }
   else
   {
      SI->BytesSEND += BytesTransferred;
   }

   /***
    * we can get rid of this since were not an echo-server
    * Perhaps we can use this part for sending a file
    ***/
   if (SI->BytesRECV > SI->BytesSEND)
   {

      // Post another WSASend() request.
      // Since WSASend() is not gauranteed to send all of the bytes requested,
      // continue posting WSASend() calls until all received bytes are sent.

      ZeroMemory(&(SI->Overlapped), sizeof(WSAOVERLAPPED));

      SI->DataBuf.buf = SI->Buffer + SI->BytesSEND;
      SI->DataBuf.len = SI->BytesRECV - SI->BytesSEND;

      if (WSASend(SI->Socket, &(SI->DataBuf), 1, &SendBytes, 0, &(SI->Overlapped), WorkerRoutine) == SOCKET_ERROR)
      {
         if (WSAGetLastError() != WSA_IO_PENDING)
         {
            qDebug() << "WSASend() failed with error " << WSAGetLastError() << endl;
            return;
         }
      }
   }
   else
   {
      SI->BytesRECV = 0;

      /***
       * Now that there are no more bytes to send post another WSARecv() request.
       * This is where we receive the data on the socket.
       ***/

      Flags = 0;
      ZeroMemory(&(SI->Overlapped), sizeof(WSAOVERLAPPED));

      SI->DataBuf.len = DATA_BUFSIZE;
      SI->DataBuf.buf = SI->Buffer;

      if (WSARecv(SI->Socket, &(SI->DataBuf), 1, &RecvBytes, &Flags, &(SI->Overlapped), WorkerRoutine) == SOCKET_ERROR)
      {
         if (WSAGetLastError() != WSA_IO_PENDING )
         {
            qDebug() << "WSARecv() failed with error " << WSAGetLastError() << endl;
            return;
         }
      }
   }
}
