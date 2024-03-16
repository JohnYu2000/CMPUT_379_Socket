#include "mutex.h"

/**
* Constructor
* @return
*/
Mutex::Mutex() {
    this->trans_id_lock = PTHREAD_MUTEX_INITIALIZER;
    this->trans_map_lock = PTHREAD_MUTEX_INITIALIZER;
}

/**
* This method returns the trans_id_lock mutex. This mutex is used to ensure
* mutual exclusion when the transaction id needs to be read and incremented
* by a thread.
* @return trans_id_lock of type pthread_mutex_t.
*/
pthread_mutex_t * Mutex::getTransIdLock() {
    return &(this->trans_id_lock);
}

/**
* This method returns the trans_map_lock mutex. This mutex is used to ensure
* mutual exclusion when the transaction map (used by the server to track the
* number of transactions performed by each client) is being updated by a thread.
* @return trans_map_lock of type pthread_mutex_t.
*/
pthread_mutex_t * Mutex::getTransMapLock() {
    return &(this->trans_map_lock);
}