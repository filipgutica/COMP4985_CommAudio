#ifndef GLOBALS
#define GLOBALS

#define BYTES_PER_SECOND 88200
#define LOW_WATERMARK BYTES_PER_SECOND
#define AUDIO_BUFFSIZE BYTES_PER_SECOND * 10
#define MAX_BUFFSIZE BYTES_PER_SECOND
#define DELAY 32
#define BYTES_TO_WRITE 8820
#define VOIP 1
#define STREAM 2

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

