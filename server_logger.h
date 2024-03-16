#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H

#include "mutex.h"
#include "util.h"
#include "tands.h"

#include <stdio.h>
#include <string.h>	//strlen
#include <stdlib.h>	//strlen
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <pthread.h> //for threading , link with lpthread
#include <vector>

#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <map>
#include <fcntl.h>

/**
* This class handles all of the logging methods.
*/
class ServerLogger {
    int port;
    std::string output_name;
    FILE * output_file;
    public:
        ServerLogger(int port, std::string output_name);
        ~ServerLogger();
        void logOnReceive(int id, int n, char * machine_name, pid_t pid);
        void logOnSend(int id, char * machine_name, pid_t pid);
        void logOnFinish(std::map<std::string, int> * transMap, double start_time, double finish_time);
};

#endif