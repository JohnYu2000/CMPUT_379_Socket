#include "server_logger.h"

using namespace std;

/**
* Constructor
* @param port an integer representing the port number.
* @param output_name a string representing the name of the output file.
* @return
*/
ServerLogger::ServerLogger(int port, string output_name) {
    this->port = port;
    this->output_name = output_name;
    this->output_file = fopen(this->output_name.c_str(), "w");
    fprintf(this->output_file, "Using port %d\n\n", this->port);
}

/**
* Destructor
* @return
*/
ServerLogger::~ServerLogger() {
    fclose(this->output_file);
}

/**
* This method will write a log whenever the server receives data from the client.
* @param id an integer representing the transaction id.
* @param n an integer representing the integer parameter provided by the client.
* @param machine_name a char * representing the machine name of the client.
* @param pid the process id of the client.
*/
void ServerLogger::logOnReceive(int id, int n, char * machine_name, pid_t pid) {
    fprintf(this->output_file, "%.2f: #%3d (T%3d) from %s\n", getTime(), id, n, getOutputName(machine_name, pid).c_str());
}

/**
* This method will write a log whenever the server sends data back to the client.
* @param id an integer representing the transaction id.
* @param machine_name a char * representing the machine name of the client.
* @param pid the process id of the client.
*/
void ServerLogger::logOnSend(int id, char * machine_name, pid_t pid) {
    fprintf(this->output_file, "%.2f: #%3d (Done) from %s\n", getTime(), id, getOutputName(machine_name, pid).c_str());
}

/**
* This method will write a log when the server has finished serving all clients.
* @param transMap a map where the key is the name of the client and the value is the number of transactions
*                 performed by that client.
* @param start_time the epoch time that the server started executing.
* @param finish_time the epoch time that the server finished executing.
*/
void ServerLogger::logOnFinish(map<string, int> * transMap, double start_time, double finish_time) {
    fprintf(this->output_file, "\nSUMMARY\n");
    int transaction_count;
    map<string, int>::iterator it;
    for (it = transMap->begin(); it != transMap->end(); it++) {
        fprintf(this->output_file, "%4d transactions from %s\n", it->second, (it->first).c_str());
        transaction_count += (int)(it->second);
    }

    double total_time = finish_time - start_time;
    double rate = (double)transaction_count / total_time;
    fprintf(this->output_file, "%4.1f transactions/sec (%d/%.2f)\n", rate, transaction_count, total_time);
}