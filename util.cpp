#include "util.h"

using namespace std;
using namespace chrono;

/**
* This method gets the number of seconds that has elapsed since January 1, 1970.
* @return a double representing the epoch time.
*/
double getTime() {
    return (double)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() / (double)1000;
}

/**
* This method generates the output name from a machine name and process id.
* @param machine_name a char * representing the machine name of the server or client.
* @param pid the process id of the server or client.
* @return a string where the value is the output name. This is what the output files
*         where the logs will go will be named.
*/
string getOutputName(char * machine_name, pid_t pid) {
    return string(machine_name) + "." + to_string(pid) + ".log";
}