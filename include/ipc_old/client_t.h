/*
* client_t.h
*
*   purpose:  defines client connection placeholder structure for IPC.
*   author:   alex amellal
*
*/

#ifndef CUBESAT_CORE_INCLUDE_IPC_CLIENT_T_H
#define CUBESAT_CORE_INCLUDE_IPC_CLIENT_T_H

// Connection type
#include "conn_t.h"

typedef struct Client
{
  int     conn;     // connection socket placeholders
  char    name[3];  // client name placeholder
} client_t;

#endif /* end of include guard: CUBESAT_CORE_INCLUDE_IPC_CLIENT_T_H */
