/*----------------------------------------------------------------------------------------------------------------------------
--  SOURCE FILE: client.cpp     contains all methods for the Client class
--
--  PROGRAM: commAudio
--
--  FUNCTIONS:
--      Client ( string ip_address, int port, int mode);
--      ~Client();
--      int SongRequest (int songID);
--      int DownloadFile (int fileID);
--      void SendVoice();
--      int CreateStream();
--      int TerminateStream();
--
--  DATE:       February 25, 2015
--
--  REVISIONS: (Date and Description)
--
--  DESIGNERS:  Alex Lam, Sebastian Pelka
--
--  PROGRAMMERS: Alex Lam, Sebastian Pelka
--
--  NOTES:
--  The client class fulfills the following responsibilities:
--  1) Connect to a Streaming Audio Server
--  2) Requests streaming of an audio file on the server
--  3) Play back audio
--  4) Connect to another Client for voice chat mode
--  5) Accept incoming voice chat requests in voice chat mode
--  6) Join a multicast server
--  7) Download an audio file
--  8) Send audio input from microphone
--  9) Disconnect from a remote client
--
---------------------------------------------------------------------------------------------------------------------------*/
#include "client.h"

/*---------------------------------------------------------------------------------------------------------------------------
--  FUNCTION: Client
--
--  DATE: February 25, 2015
--
--  REVISIONS: (Date and Description)
--
--  DESIGNER: Alex Lam, Sebastian Pelka
--
--  PROGRAMMER:
--
--  INTERFACE: Client ( string ip_address, int port, int mode );
--
--  RETURNS: void.
--
--  NOTES:
--  Constructor. This version of the constructor is used to connect to and interface with another instance of an application
--  specified by the ip address and port. For hosting a voice chat, pass null in the first two arguments.
---------------------------------------------------------------------------------------------------------------------------*/
Client::Client ( string ip_address, int port, int mode)
{

}


/*---------------------------------------------------------------------------------------------------------------------------
--  FUNCTION: ~Client
--
--  DATE: February 25, 2015
--
--  REVISIONS: (Date and Description)
--
--  DESIGNER: Alex Lam, Sebastian Pelka
--
--  PROGRAMMER:
--
--  INTERFACE: Client();
--
--  RETURNS: void.
--
--  NOTES:
--  Deconstructor for objects of the Client class.
---------------------------------------------------------------------------------------------------------------------------*/
Client::Client ()
{

}


/*---------------------------------------------------------------------------------------------------------------------------
--  FUNCTION: SongRequest
--
--  DATE: February 25, 2015
--
--  REVISIONS: (Date and Description)
--
--  DESIGNER: Alex Lam, Sebastian Pelka
--
--  PROGRAMMER:
--
--  INTERFACE: int SongRequest (int songID)
--      int songID: an integer identifying a song located on a server.
--
--  RETURNS: -1 if the song request fails, otherwise returns 0
--
--  NOTES:
--  this function is called when a user wants to add a song to their playlist, which is stored serverside.
---------------------------------------------------------------------------------------------------------------------------*/
int Client::SongRequest (int songID)
{
    return 0;
}


/*---------------------------------------------------------------------------------------------------------------------------
--  FUNCTION: DownloadFile
--
--  DATE: February 25, 2015
--
--  REVISIONS: (Date and Description)
--
--  DESIGNER: Alex Lam, Sebastian Pelka
--
--  PROGRAMMER:
--
--  INTERFACE: int DownloadFile (int fileID)
--      fileID: an integer specifying a file located on the
--
--  RETURNS: -1 if the file download request fails
--
--  NOTES:
--  this function sends a request to the server to download a file via TCP from the server to the client.
---------------------------------------------------------------------------------------------------------------------------*/
int Client::DownloadFile (int fileID)
{
    return 0;
}

/*---------------------------------------------------------------------------------------------------------------------------
--  FUNCTION: SendVoice
--
--  DATE: February 25, 2015
--
--  REVISIONS: (Date and Description)
--
--  DESIGNER: Alex Lam, Sebastian Pelka
--
--  PROGRAMMER:
--
--  INTERFACE: SendVoice()
--
--  RETURNS: void
--
--  NOTES:
--  This function collects audio data from an active microphone and sends it to the client.
---------------------------------------------------------------------------------------------------------------------------*/
void Client::SendVoice()
{
    return 0;
}

/*---------------------------------------------------------------------------------------------------------------------------
--  FUNCTION: CreateStream
--
--  DATE: February 25, 2015
--
--  REVISIONS: (Date and Description)
--
--  DESIGNER: Alex Lam, Sebastian Pelka
--
--  PROGRAMMER:
--
--  INTERFACE: int CreateStream()
--
--  RETURNS: -1 if the stream creation fails
--
--  NOTES
--  Handles receiving incoming audio data on a socket, and playing it back to the user.
---------------------------------------------------------------------------------------------------------------------------*/
int Client::CreateStream()
{
    return 0;
}


/*---------------------------------------------------------------------------------------------------------------------------
--  FUNCTION: TerminateStream
--
--  DATE: February 25, 2015
--
--  REVISIONS: (Date and Description)
--
--  DESIGNER: Alex Lam, Sebastian Pelka
--
--  PROGRAMMER:
--
--  INTERFACE:
--
--  RETURNS: -1 if the stream termination fails
--
--  NOTES:
--  Handles properly closing down a socket-based connection between a client and server.
---------------------------------------------------------------------------------------------------------------------------*/
int Client::TerminateStream()
{
    return 0;
}
