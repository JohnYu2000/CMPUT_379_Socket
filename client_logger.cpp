#include "client_logger.h"

using namespace std;

/**
* Constructor
* @param port an integer representing the port number.
* @param ip_addr a char * representing the ip address of the server.
* @param machine_name a char * representing the name of the client machine.
* @param pid the process id of the client.
* @return
*/
ClientLogger::ClientLogger(int port, char * ip_addr, char * machine_name, pid_t pid) {
    this->output_name = getOutputName(machine_name, pid);
    this->output_file = fopen(this->output_name.c_str(), "w");
    fprintf(this->output_file, "Using port %d\n", port);
    fprintf(this->output_file, "Using server address %s\n", ip_addr);
    fprintf(this->output_file, "Host %s\n\n", this->output_name.c_str());
}

/**
* Destructor
* @return
*/
ClientLogger::~ClientLogger() {
    fclose(this->output_file);
}

/**
* This method will log whenever the client sends data to the server.
* @param n an integer representing the integer parameter passed by the user.
* @return
*/
void ClientLogger::logOnSend(int n) {
    fprintf(this->output_file, "%.2f: Send (T%3d)\n", getTime(), n);
}

/**
* This method will log whenever the client receives data from the server.
* @param id an integer representing the transaction id passed by the server.
* @return
*/
void ClientLogger::logOnReceive(int id) {
    fprintf(this->output_file, "%.2f: Recv (D%3d)\n", getTime(), id);
}

/**
* This method will log whenever the client sleeps.
* @param n an integer representing the integer parameter passed by the user.
* @return
*/
void ClientLogger::logSleep(int n) {
    fprintf(this->output_file, "Sleep %d units\n", n);
}

/**
* This method will log when the client is done execution.
* @param n the number of transactions performed by the client.
* @return
*/
void ClientLogger::logOnFinish(int n) {
    if (n == 1) {
        fprintf(this->output_file, "\nSent %d transaction\n", n);
    } else {
        fprintf(this->output_file, "\nSent %d transactions\n", n);
    }
}