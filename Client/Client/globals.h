#ifndef GLOBALS
#define GLOBALS

#define BYTES_PER_SECOND 88200
#define LOW_WATERMARK BYTES_PER_SECOND
<<<<<<< HEAD
#define HIGH_WATERMARK BYTES_PER_SECOND * 3
#define AUDIO_BUFFSIZE BYTES_PER_SECOND * 5
=======
#define HIGH_WATERMARK BYTES_PER_SECOND * 5
#define AUDIO_BUFFSIZE BYTES_PER_SECOND * 10
>>>>>>> a9a682c144d5f3356d26f5a6c342ab6e54b5e9aa
#define MAX_BUFFSIZE BYTES_PER_SECOND
#define DELAY 32
#define BYTES_TO_WRITE 8820

#include <QIODevice>
#include <QBuffer>
#include <QAudioOutput>
#include <QSemaphore>

extern QIODevice *ioOutput;
extern QBuffer *buffer;
extern QAudioOutput *audioOutput;
extern qint64 audioPos;
extern qint64 socketPos;
extern QSemaphore sem1;
extern QSemaphore sem2;
extern int nBytes;
extern int bytesWritten;
extern int totalBytesWritten;

#endif // GLOBALS

