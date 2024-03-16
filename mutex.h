#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

/**
* This class is used to store mutexes used throughout this program.
*/
class Mutex {
    pthread_mutex_t trans_id_lock;
    pthread_mutex_t trans_map_lock;
    public:
        Mutex();
        pthread_mutex_t * getTransIdLock();
        pthread_mutex_t * getTransMapLock();
};

#endif