#include "server_socket_handler.h"

/**
* Constructor
* @param port an integer representing the port number
* @param logger a pointer to the ServerLogger object
* @param mutex a pointer to the Mutex object
* @return
*/
ServerSocketHandler::ServerSocketHandler(int port, ServerLogger * logger, Mutex * mutex) {
    this->port = port;
    this->logger = logger;
    this->mutex = mutex;
    this->transId = 1;
    this->start_time = getTime();
    this->max_clients = 100;
    for (int i = 0; i < this->max_clients; i++) {
        this->client_socket[i] = 0;
    }
    //Create socket
	this->socket_desc = socket(AF_INET, SOCK_STREAM , 0);
	if (this->socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	this->server.sin_family = AF_INET;
	this->server.sin_addr.s_addr = INADDR_ANY;
	this->server.sin_port = htons(this->port);
	
	//Bind
	if( bind(this->socket_desc,(struct sockaddr *)&(this->server), sizeof(this->server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
	}
	puts("bind done");
	
	//Listen
	listen(this->socket_desc, 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	this->c = sizeof(struct sockaddr_in);
}

/**
* Destructor
* @return
*/
ServerSocketHandler::~ServerSocketHandler() {
    delete this->new_sock;
    for (Consumer * c : this->consumers) {
        delete c;
    }
    for (int i = 0; i < this->max_clients; i++) {
        if (this->client_socket[i] > 0) {
            close(this->client_socket[i]);
        }
    }
}

/**
* This method will wait and accept any clients that try to connect to the server. The server has
* a timeout time of 30 seconds. If the server waits for 30 seconds for some kind of activity to
* happen in one of the sockets then the server will stop accepting new connections.
* @return a bool where true means that a connection was successful and false means that either the
*         server waited too long for an activity or a connection attempt failed.
*/
bool ServerSocketHandler::acceptConnection() {
    this->tv.tv_sec = 30;
    FD_ZERO(&(this->readfds));
    FD_SET(this->socket_desc, &(this->readfds));
    this->max_sd = this->socket_desc;
    for (int i = 0; i < this->max_clients; i++) {
        // socket descriptor
        this->sd = client_socket[i];

        // if valid socket descriptor then add to read list
        if (this->sd > 0) {
            FD_SET(this->sd, &(this->readfds));
        }

        // highest file descriptor number, need it for the select function
        if (this->sd > this->max_sd) {
            this->max_sd = sd;
        }
    }
    this->activity = select(this->max_sd + 1, &(this->readfds), NULL, NULL, &(this->tv));
    if ((this->activity < 0) && (errno != EINTR)) {
        printf("Select Error!");
    }
    if (FD_ISSET(this->socket_desc, &(this->readfds))) {
        // Check if a client is trying to connect to the server.
        if (this->client_sock = accept(this->socket_desc, (struct sockaddr *)&(this->client), (socklen_t*)&(this->c))) {
            puts("Connection accepted!");
            this->consumers.push_back(new Consumer(this->client_sock, &(this->transId), this->logger, this->mutex, &(this->transMap)));
            for (int i = 0; i < this->max_clients; i++) {
                if (this->client_socket[i] == 0) {
                    this->client_socket[i] = this->client_sock;
                    printf("Adding socket %i to list of sockets.\n", this->client_sock);
                    break;
                }
            }
            puts("Handler assigned!");
            return true;
        } else {
            puts("Error when trying to connect to socket.");
            return false;
        }    
    } else {
        // Check if a client disconnected.
        for (int i = 0; i < this->max_clients; i++) {
            this->sd = this->client_socket[i];
            if (FD_ISSET(this->sd, &(this->readfds))) {
                // Check if file descriptor is still open
                if (fcntl(this->sd, F_GETFD) != -1) {
                    ;
                } else {
                    close(this->sd);
                    this->client_socket[i] = 0;
                }
                return true;
            }
        }
        printf("Waited longer than 30 seconds for an activity. No longer accepting new connections.\n");
        return false;
    }
}

/**
* This method waits for all the clients to finish execution.
* @return
*/
void ServerSocketHandler::joinConsumers() {
    for (Consumer * c : this->consumers) {
        pthread_join(c->getThreadId(), NULL);
    }
}

/**
* This method logs the final output summary.
*/
void ServerSocketHandler::outputSummary() {
    this->logger->logOnFinish(&(this->transMap), this->start_time, getTime());
}