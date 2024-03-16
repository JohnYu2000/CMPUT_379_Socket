#include "server.h"

int main(int argc, char * argv[]) {
    // Get the port number
    int port = atoi(argv[1]);

    if (port >= 5000 && port <= 64000) {
        ;
    } else {
        printf("Port must be between 5000 and 64000.\n");
        return 0;
    }

    // Get the server machine name
    char machine_name[100];
    if (gethostname(machine_name, 100) < 0) {
        printf("Failed to get the machine name!");
    }

    // Initialize a logger
    ServerLogger * logger = new ServerLogger(port, getOutputName(machine_name, getpid()));

    // Initialize a mutex
    Mutex * mutex = new Mutex();

    // Initialize a socket handler
    ServerSocketHandler * serverSocketHandler = new ServerSocketHandler(port, logger, mutex);

    // Continuously wait for clients to connect
    while (serverSocketHandler->acceptConnection());

    // Wait for clients to finish.
    serverSocketHandler->joinConsumers();

    // Display the output summary.
    serverSocketHandler->outputSummary();

    // Deallocate memory.
    delete logger;
    delete mutex;
    delete serverSocketHandler;
}