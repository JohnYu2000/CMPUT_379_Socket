CMPUT 379 Fall 2022
Name: John Yu
CCID: junye

Files:
    - client_folder
        - client_logger.cpp (Implementation for client logging is defined here)
        - client_logger.h (Contains class responsible for logging the client)
        - client_socket_handler.cpp (Client socket handling is defined in here)
        - client_socket_handler.h (Contains class responsible for client socket handling)
        - client.cpp (Main file for the client is defined in here)
        - client.h (This is the entry point for the client)
        - command.cpp (Command is implemented here)
        - command.h (Contains class responsible for retrieving user input)
    - common
        - mutex.cpp (Mutexes are defined here)
        - mutex.h (Contains class responsible for storing mutexes used throughout program)
        - tands.cpp (Tands are defined here)
        - tands.h (Contains the tands functions provided by the assignment specifications)
        - util.cpp (Functions are defined here)
        - util.h (Contains functions to get epoch time and the file output name)
    - man_folder
        - client.man (Man page for the client)
        - server.man (Man page for the server)
    - server_folder
        - consumer.cpp (Class is defined here)
        - consumer.h (Class is responsible for creating a thread to handle each client connection)
        - server_logger.cpp (Logger is defined in here)
        - server_logger.h (Class is responsible for logging the server activity)
        - server_socket_handler.cpp (Server socket handling is defined in here)
        - server_socket_handler.h (Class is responsible for server socket handling)
        - server.cpp (Main file for the server is defined in here)
        - server.h (This is the entry point for the server)
    - Makefile (Compiles and links the client and server. Also generates the man pages and tar file)
    - README (Provides additional information about my submission)

Assumptions:
    - The port number must be in the range 5000 and 64000 inclusive.
    - The maximum number of clients that can be connected at the same time is 100.
    - Inputs are all either in the form `T<n>` or `S<n>`.
    - The server will stop accepting new clients after 30 seconds of inactivity.
    - Weird and unexpected behavior may occur on very large n values.
    - My server is multithreaded so long transactions will not bottleneck other clients.

Approach:
    - Server:
        1. Create, bind, and listen to socket.
        2. Use select() to monitor the activity of each socket.
        3. Accept incoming connection from client.
        4. Create a new thread to handle the client.
        5. Receive data from client, perform a transaction, and send data back to client.
        6. Log relevant events.
        7. When client disconnects, close the socket descriptor.
        8. Wait for all client threads to finish.
        9. Log the summary.
    - Client:
        1. Connect to the server.
        2. Read commands from command prompt or file.
        3. If command is a transaction send data to server and wait until data received back from server.
        4. If command is a sleep then perform a sleep.
        5. Log relevant events.
        6. When eof is reached log the session summary and terminate.

Instructions:
    Server:
        1. In the main directory where the makefile is located, run `make server`. This will create a server
           executable called server.
        2. Run `./server port` where the port is the port number.
        3. The server will stop accepting new connections after 30 seconds of inactivity.
    Client:
        1. In the main directory where the makefile is located, run `make client`. This will create a client
           executable called client.
        2. Run `./client port ip_address` where port is the port number and ip_address is the ip address the
           server is running on.
        3. Type in `T<n>` to run a transaction. Type in `S<n>` to sleep.
        4. Press CTRL+D to terminate the client.
    Man:
        1. Run `make man` to generate the man pages.

References:
    I used this source to get started with socket programming.
        https://www.binarytides.com/server-client-example-c-sockets-linux/

    I used this source to create a non-blocking socket.
        https://www.binarytides.com/multiple-socket-connections-fdset-select-linux/

    I used this source to check if a socket descriptor is still open.
        https://stackoverflow.com/questions/12340695/how-to-check-if-a-given-file-descriptor-stored-in-a-variable-is-still-valid

    I used the following sources to help me make my MAN pages.
        https://www.cyberciti.biz/faq/linux-unix-creating-a-manpage/
        https://babbage.cs.qc.cuny.edu/courses/cs701/Handouts/man_pages.html
        https://linux.die.net/man/7/man-pages
        https://www.cyberciti.biz/faq/howto-use-linux-unix-man-pages/
        https://man7.org/linux/man-pages/man7/groff_man.7.html
