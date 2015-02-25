#ifndef CLIENT
#define CLIENT

#define BUFFER_SIZE 4092

class Client
{
    private:
        SOCKET  control_line, data_line_udp, data_line_tcp;
        char* audio_buffer[BUFFER_SIZE];
        HANDLE streamThread;        //for terminating threads

    public:
        Client ( string ip_address, int port);
        Client ();
        ~Client();
        int SongRequest (int songID);
        int DownloadFile (int fileID);
        int SentVoice();
        int CreateStream();
        int TerminateStream();
};

#endif // CLIENT

