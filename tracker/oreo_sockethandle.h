/**
 * @file oreo_sockethandled.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and monitor a connection to oreo tracker
 * @see 
 */
#ifndef OREO_TRACKER_SOCKETHANDLE_H
#define OREO_TRACKER_SOCKETHANDLE_H

#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "oreo_commandhandle.h"
#include "oreo_datastructure.h"


/**
 * @see http://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml
 * @see http://tools.ietf.org/html/rfc793
 */
//~ static const int TCP_PROTOCOL_NUMBER = 6;
/**
 * Port in run oreo tracker
 */
//~ static const int PORT = 8907;

/**
 * @brief This method wait a peer connection and run thread by this peer
 * @param socketFd 
 * @param connectionState
 * @param connectionId
 * @param thread
 * @return  1 whether oreo tracker acept connection 0 otherwise
 */
int waitApeer(int socketFd, int* connectionState, int connectionId,pthread_t* thread);
/**
 * @brief This method return a new identifier by incoming connection, new peer
 * @param connectionState
 * @param size
 * @return  1 whether oreo tracker may acept connection 0 otherwise
 */
int getNewId(int * connectionState, int size);
/**
 * @brief This method maintains excahnge of messages in the connection with peer
 * @param dataconnectionpeer
 */
void peerExchangeCommands(void* dataconnectionpeer);
/**
 * @brief This method make messages 
 * @param connectiondata
 * @return messsage from trakcer to peer
 */
command* waitCommands(dataPeer* connectiondata);

#endif /*oreo_trackersockethandle.h*/
