#ifndef GLOBALS
#define GLOBALS

#define BYTES_PER_SECOND 88200
#define LOW_WATERMARK BYTES_PER_SECOND
#define HIGH_WATERMARK BYTES_PER_SECOND * 20
#define AUDIO_BUFFSIZE BYTES_PER_SECOND * 21

#define MAX_BUFFSIZE BYTES_PER_SECOND

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

#endif // GLOBALS

