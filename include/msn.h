//msn.h

#ifndef CUBESAT_CORE_INCLUDE_IPC_SERVER_H
#define CUBESAT_CORE_INCLUDE_IPC_SERVER_H

//Project Headers
#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <unistd.h>
#include <vector>
#include <string>
#include <map>

using namespace std; 

//Methods
map<string, string> deSerialize(std::string message, int mapSize);

int is_current_min(char* msnTime);

#endif
