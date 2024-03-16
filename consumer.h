#ifndef CONSUMER_H
#define CONSUMER_H

#include "server_logger.h"

class Consumer {
    pthread_t thread_id;
    int read_size, sock, *transId;
    char client_message[100], client_reply[100];
    ServerLogger * logger;
    Mutex * mutex;
    std::map<std::string, int> * transMap;
    public:
        Consumer(int sock, int * transId, ServerLogger * logger, Mutex * mutex, std::map<std::string, int> * transMap);
        bool recvClientInput();
        pthread_t getThreadId();
};

void * thread_function(void * args_p);

#endif