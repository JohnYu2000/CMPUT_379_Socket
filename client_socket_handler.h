#ifndef CLIENT_SOCKET_HANDLER_H
#define CLIENT_SOCKET_HANDLER_H

#include "command.h"

/**
* This class handles all of the methods dealing with sockets for the client.
*/
class ClientSocketHandler {
	struct sockaddr_in server;
	char message[100] , reply[100], *machine_name;
    char * ip_addr;
    int sock, port, numOfTrans;
    pid_t pid;
    ClientLogger * logger;
    public:
        ClientSocketHandler(char * ip_addr, int port, char * machine_name, ClientLogger * logger);
        ~ClientSocketHandler();
        bool talkToServer();
};

#endif