#ifndef CLIENT_LOGGER_H
#define CLIENT_LOGGER_H

#include "tands.h"
#include "util.h"

#include <stdio.h>	//printf
#include <stdlib.h>
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>

/**
* This method is used to log the client actions to the output file.
*/
class ClientLogger {
    std::string output_name;
    FILE * output_file;
    public:
        ClientLogger(int port, char * ip_addr, char * machine_name, pid_t pid);
        ~ClientLogger();
        void logOnSend(int n);
        void logOnReceive(int id);
        void logSleep(int n);
        void logOnFinish(int n);
};

#endif