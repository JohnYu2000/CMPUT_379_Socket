#include "consumer.h"

using namespace std;

/**
* Constructor
* @param sock an integer representing the sock file descriptor.
* @param transId an int* representing the transaction id. All consumers have access to the same
*                transaction id value which is stored in the @link ServerSocketHandler class.
* @param logger a ServerLogger* used to log to the output file.
* @param transMap a map pointer that stores the number of transactions for each client.
* @return
*/
Consumer::Consumer(int sock, int * transId, ServerLogger * logger, Mutex * mutex, map<string, int> * transMap) {
    this->sock = sock;
    this->transId = transId;
    this->logger = logger;
    this->mutex = mutex;
    this->transMap = transMap;
    pthread_create(&(this->thread_id), NULL, thread_function, this);
}

/**
* This method will continuously listen for any input by the client. The method will receive the
* integer parameter, machine name, and process id from the client. After, the method will perform
* a Trans operation and return to the client the transaction id.
* @return a bool where true means that the method successfully read and send data to the client.
*         False means that either the client disconnected or reading data from the client failed.
*/
bool Consumer::recvClientInput() {
    if (this->read_size = recv(this->sock, this->client_message, 100, 0) > 0) {
        int client_n;
        char client_machine_name[50];
        pid_t client_pid;
        int client_id;
        sscanf(this->client_message, "%i %s %d", &client_n, client_machine_name, &client_pid);

        pthread_mutex_lock(this->mutex->getTransIdLock());
        client_id = *(this->transId);
        (*(this->transId))++;
        pthread_mutex_unlock(this->mutex->getTransIdLock());

        this->logger->logOnReceive(client_id, client_n, client_machine_name, client_pid);
        Trans(client_n);
        this->logger->logOnSend(client_id, client_machine_name, client_pid);

        sprintf(this->client_reply, "%i", client_id);
        if (send(this->sock, this->client_reply, 100, 0) < 0) {
            puts("Send failed!");
        }

        pthread_mutex_lock(this->mutex->getTransMapLock());
        map<string, int>::iterator it = this->transMap->find(getOutputName(client_machine_name, client_pid));
        if (it == this->transMap->end()) {
            this->transMap->insert({getOutputName(client_machine_name, client_pid), 1});
        } else {
            (it->second)++;
        }
        pthread_mutex_unlock(this->mutex->getTransMapLock());

        return true;
    } else if (this->read_size == 0) {
        puts("Client disconnected");
		fflush(stdout);
        close(this->sock);
        return false;
    } else {
        perror("recv failed");
        return false;
    }
}

/**
* This method returns the thread id of the current thread. This method is called
* in the @link ServerSocketHandler class to wait for the thread to complete
* execution.
* @return the thread id of type pthread_t.
*/
pthread_t Consumer::getThreadId() {
    return this->thread_id;
}

/**
* This is the thread function. The thread function will continuously receive input
* from the client.
* @param args_p a void* where the value is the class @link Consumer
* @return a null pointer.
*/
void * thread_function(void * args_p) {
    Consumer * consumer = (Consumer *) args_p;
    while (consumer->recvClientInput());
    return nullptr;
}