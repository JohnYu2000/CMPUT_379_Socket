#include "client.h"

int main(int argc, char * argv[]) {
    // Get the port number
    int port = atoi(argv[1]);
    if (port >= 5000 && port <= 64000) {
        ;
    } else {
        printf("Port must be between 5000 and 64000.\n");
        return 0;
    }

    // Get the ip address of the server.
    char * ip_addr = argv[2];

    // Get the machine name of the client.
    char machine_name[100];
    if (gethostname(machine_name, 100) < 0) {
        printf("Failed to get the machine name!");
    }

    // Instantiate a new ClientLogger object.
    ClientLogger * logger = new ClientLogger(port, ip_addr, machine_name, getpid());

    // Instantiate a new ClientSocketHandler object.
    ClientSocketHandler * clientSocketHandler = new ClientSocketHandler(ip_addr, port, machine_name, logger);

    // Continuously talk to the server.
    while (clientSocketHandler->talkToServer());

    // Deallocate memory.
    delete logger;
    delete clientSocketHandler;
}