/**
 * @file oreo_sockethandle.h
 * @author     Jefferson Amado Peña Torres, jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief This file contains handle for
 * the Socket, wait a peer exchange commands
 * and send response.This allows to OreoSync
 * control and use network sockets.
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
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include "oreo_commandhandle.h"
#include "oreo_datastructure.h"

/**
 * @brief This method wait a peer connection and run thread by this peer
 *
 * @param [socketFd]  identifier by socket
 * @param [connectionState] handle to state of connection by each peer
 * @param [connectionId] identifier by a peer incoming to tracker
 * @param [thread] A thread by each peer, the tracker module is multithread
 *
 * @return A new Peer incoming to tracker module
 * @retval 1 accept connection set identifier,thread and status to peer incoming
 * @retval 2 accept connection set identifier, NO thread
 * @retval -1  Oops, did something.
 */
int wait_peer(int socketFd, int* connectionState, int connectionId,pthread_t* thread);
/**
 * @brief This method write to a file descriptor according to
 * response, this is a file or a status code
 * @param [sd] socket descriptor sd
 * @param [response] data to write
 * @param [count] The number of bytes written may be less than count
 * @return On success, the number of bytes written is returned
 * (zero indicates nothing was written).
 * On error, -1 is returned, and errno is set appropriately.
 * If count is zero and fd refers to a regular file, then write() may
 * return a failure status if one of the errors below is detected.  If
 * no errors are detected, 0 will be returned without causing any other
 * effect.  If count is zero and fd refers to a file other than a
 * regular file, the results are not specified.
 */
write_response(int sd, const void *response, size_t count);
/**
 * @brief This method return a new identifier by incoming connection, new peer
 *
 * @param [connectionState] handle to state of connection by each peer
 * @param [size]
 *
 * @return A new Peer incoming to tracker module
 * @retval 1 accept connection set identifier,thread and status to peer incoming
 * @retval NULL  Oops, did something.
 */
int get_peer_id(int * connectionState, int size);
/**
 * @brief This method maintains
 * excahnge of messages in the connection with peer
 * @param dataconnectionpeer
 */
void exchange_commands(void* dataconnectionpeer);
/**
 * @brief This method read data sent from the peer
 * and identify what command deploy and return
 * a command known and data
 * @param [connectiondata] the data from peer load in dataPeer struct
 * @return aCommand command sent from the peer
 * @retval identifier aCommand identifier
 * @retval NULL  Oops, did something.
 * @see dataPeer
 */
aCommand* expected_command(dataPeer* connectiondata);


#endif /*oreo_trackersockethandle.h*/
