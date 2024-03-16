#ifndef COMMAND_H
#define COMMAND_H

#include "client_logger.h"

/**
* This class is used primarily to get the next command
* from the user either as a command line input or as
* a file input.
*/
class Command {
    int n;
    char cmd;
    public:
        Command();
        void getNextCommand();
        int getN();
        char getCmd();
};

#endif