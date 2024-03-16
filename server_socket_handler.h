#ifndef SERVER_SOCKET_HANDLER_H
#define SERVER_SOCKET_HANDLER_H

#include "consumer.h"

/**
* This class handles everything related to sockets for the server. This
* class will first create a socket connection using the constructor. Then
* the class will accept new client connections using the @link acceptConnection()
* method. When the server goes for 30 seconds without a new connection made the
* server will stop accepting new connections and wait for all clients to finish
* execution. Once all clients have finished execution the server will output
* the summary.
*/
class ServerSocketHandler {
    int socket_desc ,client_sock ,c ,*new_sock, port, activity, transId, max_sd, client_socket[100], max_clients, sd;
	struct sockaddr_in server , client;
    fd_set readfds;
    struct timeval tv;
    std::vector<Consumer*> consumers;
    ServerLogger * logger;
    Mutex * mutex;
    std::map<std::string, int> transMap;
    double start_time;
    double finish_time;
    public:
        ServerSocketHandler(int port, ServerLogger * logger, Mutex * mutex);
        ~ServerSocketHandler();
        bool acceptConnection();
        void joinConsumers();
        void outputSummary();
        
};

#endif