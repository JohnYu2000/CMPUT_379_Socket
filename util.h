#ifndef UTIL_H
#define UTIL_H

#include <cstdio>
#include <cstring>
#include <chrono>
#include <string>

double getTime();

std::string getOutputName(char * machine_name, pid_t pid);

#endif