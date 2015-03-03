#ifndef CLIENT
#define CLIENT

#include <QString>

#define BUFFER_SIZE 4092

class Client
{
    private:
       // SOCKET  control_line, data_line_udp, data_line_tcp;
       // char* audio_buffer[BUFFER_SIZE];
       // HANDLE streamThread;        //for terminating threads

    public:
        Client ( QString ip_address, int port, int mode);
        ~Client();
        int SongRequest (int songID);
        int DownloadFile (int fileID);
        void SendVoice();
        int CreateStream();
        int TerminateStream();
};

#endif // CLIENT

