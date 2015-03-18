#ifndef GLOBALS
#define GLOBALS

#define BYTES_PER_SECOND 44100 * 2
#define LOW_WATERMARK BYTES_PER_SECOND
#define HIGH_WATERMARK BYTES_PER_SECOND * 30
#define AUDIO_BUFFSIZE BYTES_PER_SECOND * 31

#define MAX_BUFFSIZE BYTES_PER_SECOND

#include <QIODevice>
#include <QBuffer>
#include <QAudioOutput>
#include <QSemaphore>

extern QIODevice *ioOutput;
extern QBuffer *buffer;
extern QAudioOutput *audioOutput;
extern QSemaphore sem1;
extern QSemaphore sem2;

#endif // GLOBALS

