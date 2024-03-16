#include "client_socket_handler.h"

/**
* Constructor
* @param ip_addr a char * representing the ip address of the server.
* @param port an integer representing the port number.
* @param machine_name a char * representing the machine name of the client.
* @param logger a ClientLogger* used to log to the output file.
* @return
*/
ClientSocketHandler::ClientSocketHandler(char * ip_addr, int port, char * machine_name, ClientLogger * logger) {
    this->ip_addr = ip_addr;
    this->port = port;
    this->machine_name = machine_name;
    this->pid = getpid();
    this->numOfTrans = 0;
    this->logger = logger;

    //Create socket
	this->sock = socket(AF_INET , SOCK_STREAM , 0);
	if (this->sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	this->server.sin_addr.s_addr = inet_addr(this->ip_addr);
	this->server.sin_family = AF_INET;
	this->server.sin_port = htons(this->port);

	//Connect to remote server
	if (connect(this->sock, (struct sockaddr *)&(this->server), sizeof(this->server)) < 0)
	{
		perror("connect failed. Error");
	}
	puts("Connected");
}

/**
* Destructor
* @return
*/
ClientSocketHandler::~ClientSocketHandler() {
    ;
}

/**
* This method first gets the command line input or file input from the user. A Trans() or Sleep()
* will be performed depending on the input. When the input is a trans the integer parameter, machinename,
* and process id will be sent to the server. The client will then receive the transaction id from the
* server. When the input is sleep the client will sleep and that to the output file. When the eof is
* is reached the log summary will be outputted to the output file and the client will terminate.
* @return a bool where true means that the client successfully sent and received data from the server
*         or the client successfully slept. False means that either the end of file is reached or
*         the client had problems communicating with the server.
*/
bool ClientSocketHandler::talkToServer() {
    Command cmd = Command();
    cmd.getNextCommand();
    if (cmd.getCmd() == 'T') {
        sprintf(this->message, "%i %s %d", cmd.getN(), this->machine_name, this->pid);
        // Send data to server
        if (send(this->sock, this->message, 100, 0) < 0) {
            puts("Send failed!");
            return false;
        }
        this->logger->logOnSend(cmd.getN());

        // Receive data from server
        if (recv(this->sock, this->reply, 100, 0) < 0) {
            puts("Recv failed!");
        }
        int trans_id;
        sscanf(this->reply, "%i", &trans_id);
        this->logger->logOnReceive(trans_id);

        (this->numOfTrans)++;
        return true;
    } else if (cmd.getCmd() == 'S') {
        // Perform sleep here
        Sleep(cmd.getN());
        this->logger->logSleep(cmd.getN());
        return true;
    } else {
        // eof here
        this->logger->logOnFinish(numOfTrans);
        return false;
    }
}