#ifndef COMMON
#define COMMON

#include <QSemaphore>

extern char buffer[8196];

extern QSemaphore freeBytes;
extern QSemaphore usedBytes;


#endif // COMMON

