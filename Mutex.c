#include "Mutex.h"
#include <stdlib.h>

Mutex* createMutex() {
    Mutex* mutex = (Mutex*)malloc(sizeof(Mutex));
    if (mutex == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    pthread_mutex_init(&(mutex->mutex), NULL);
    return mutex;
}

void lockMutex(Mutex* mutex) {
    pthread_mutex_lock(&(mutex->mutex));
}

void unlockMutex(Mutex* mutex) {
    pthread_mutex_unlock(&(mutex->mutex));
}

void destroyMutex(Mutex* mutex) {
    pthread_mutex_destroy(&(mutex->mutex));
    free(mutex);
}

