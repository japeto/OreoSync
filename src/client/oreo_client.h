/**
 * @file oreo_client.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 12 Dec 2014
 * @brief This file contains necesary functions for handle 
 * the oreo client module
 * @see aModuleClient
 */
#ifndef OREO_TRACKER_H
#define OREO_TRACKER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
/**
 * @brief this Struct this a <b>OreoSync</b> client
 * 
 */
typedef struct aModuleClient{
        //~ aVector* peers;
}aModuleClient;

/**
 * @brief Make a new client
 */
void newClient();
/**
 * @brief load initial values
 */
int initValues();
/**
 * @brief load initial values
 */
int runClient();
/**
 * @brief Deallocates a allocate memory by oreo client module
 */
void freeClient();
#endif 
