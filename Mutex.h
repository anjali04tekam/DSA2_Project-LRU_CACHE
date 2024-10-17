#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

// Mutex structure
typedef struct {
    pthread_mutex_t mutex;
} Mutex;

// Function declarations
Mutex* createMutex();
void lockMutex(Mutex* mutex);
void unlockMutex(Mutex* mutex);
void destroyMutex(Mutex* mutex);

#endif /* MUTEX_H */

