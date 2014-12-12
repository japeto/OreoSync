/**
 * @file oreo_commandprocessor.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and 
 * monitor a connection to oreo tracker
 * @see 
 */
#ifndef OREO_COMMANDPROCESSOR_H
#define OREO_COMMANDPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "oreo_datastructure.h"
#include "oreo_commandhandle.h"
#include "oreo_tracker.h"



/**
 * @brief A command is processed and according type a response is generated
 * @param com command into
 * @param ip address client
 * @return char* response according to command
 */
char* processCommand(command* com, char* ip);
/**
 * @brief A command of type "announce" is processed
 * @param port 
 * @param seeders
 * @param leeches
 * @param ip
 * @return char* response 
 */
char* processAnnouncecommand(char* port, char* ip, char* seeders, char* leeches);
/**
 * @brief A command of type "look" is processed
 * @param criteion 
 * @return char* response 
 */
char* processLookcommand(char* into);
/**
 * @brief A command of type "getfile" is processed
 * @param key 
 * @return char* response 
 */
char* processGetfilecommand(char* key);
/**
 * @brief A command of type "update" is processed
 * @param key 
 * @return char* response 
 */
char* processUpdatecommand(char* seeders, char* leeches, char* ip);
/**
 * whith this method is obtained num port associated to client from 
 * string
 * @param string 
 * @return 
 */
char* announcePort(char* string);
/**
 * whith this method is obtained num port associated to client from 
 * string
 * @param string 
 * @return 
 */
char* announceSeeders(char* string);
/**
 * whith this method is obtained num port associated to client from 
 * string
 * @param string 
 * @return 
 */
char* announceLeeches(char* string);
/**
 * whith this method is obtained num port associated to client from 
 * string
 * @param string 
 * @return 
 */
char* lookElemnts(char* string);
/**
 * whith this method is obtained num port associated to client from 
 * string
 * @param string 
 * @return 
 */
char* getfileKey(char* string);
/**
 * whith this method is obtained num port associated to client from 
 * string
 * @param string 
 * @return 
 */
char* updateSeeders(char* string);
/**
 * whith this method is obtained num port associated to client from 
 * string
 * @param string 
 * @return 
 */
char* updateLeeches(char* string);

#endif /*oreo_trackersockethandle.h*/
