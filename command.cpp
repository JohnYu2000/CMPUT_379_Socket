#include "command.h"

/**
* Constructor
* @return
*/
Command::Command() {
    ;
}

/**
* This method gets the next command from the user. This method will
* extract the command type (T, S, or eof) as well as the integer
* parameter.
* @return
*/
void Command::getNextCommand() {
    bool eof = (scanf(" %c%d", &(this->cmd), &(this->n)) == -1);
    if (eof) {
        this->cmd = 'E';
    } else {
        ;
    }
}

/**
* This method returns the integer parameter.
* @return the integer parameter.
*/
int Command::getN() {
    return this->n;
}

/**
* This method return the command type.
* @return a chare representing the command type.
*/
char Command::getCmd() {
    return this->cmd;
}