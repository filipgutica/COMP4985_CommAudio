/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	globals.h -         Header containing global declarations necesarry to our
--                                      client application
--
--	PROGRAM:		Client
--
--	DESIGNERS:		Filip Gutica
--
--	PROGRAMMER:		Filip Gutica
--
--	NOTES:
--
---------------------------------------------------------------------------------------*/
#ifndef GLOBALS
#define GLOBALS

#define BYTES_PER_SECOND 88200
#define LOW_WATERMARK BYTES_PER_SECOND
#define AUDIO_BUFFSIZE BYTES_PER_SECOND * 30
#define MAX_BUFFSIZE BYTES_PER_SECOND
#define DELAY 32
#define BYTES_TO_WRITE 8820
#define VOIP 1
#define STREAM 2
#define MULTICAST_PORT 7575

#include <QIODevice>
#include <QBuffer>
#include <QAudioOutput>
#include <QSemaphore>

extern QIODevice *ioOutput;
extern QBuffer *buffer;
extern QAudioOutput *audioOutput;
extern int nBytes;
extern int bytesWritten;
extern int totalBytesWritten;
extern int totalNBytes;

#endif // GLOBALS

