/**
 * @file oreo_commandhandle.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and monitor a connection to oreo tracker
 * @see 
 */
#ifndef OREO_COMMANDHANDLE_H
#define OREO_COMMANDHANDLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "oreo_globals.h"


/**
 * @brief This enum contains commands in comunication 
 */
typedef enum {
	ANNOUNCE, 	/**< <b>ANNOUNCE<b/> with this commnad the peer say has this file*/
	LOOK, 		/**< <b>LOOK<b/> with this commnad the peer say all look this file*/
	GETFILE,	/**< <b>GETFILE<b/> with this commnad the peer say sendme this file*/
	GET,	        /**< <b>GET<b/> with this commnad the peer say sendme this file*/
	UPDATE,		/**< <b>IPDATE<b/> with this commnad the peer say upadte mi state or my list*/
	SENDCHUNK,	/**< <b>SENDCHUNK<b/> with this commnad the peer say nothing */
	UNKNOWN		/**< <b>UNKNOWN<b/> with this commnad the peer say nothing */
} commandtype;
/**
 * @brief This typestruct contains a command send in connection
 */
typedef struct 
{
  commandtype type; 	/**< type by command */
  char* data;		/**< data */
  
} command;

/**
 * constructor
 * @param dataSize size of command 
 */
command* newCommand(int dataSize);
/**
 * delete a command and free memory
 * @param com command to delete
 */
void deleteCommand(command* com);
/**
 * With this method verify whether a command is announce 
 * @param com 
 * @param buffer 
 * @return 1 whether is announce 0 otherwise 
 */
int isAnnounce(command* com, char* data);
/**
 * With this method verify whether a command is look 
 * @param com 
 * @param buffer 
 * @return 1 whether is announce 0 otherwise
 */
int isLook(command* com, char* data);
/**
 * With this method verify whether a command is getfile 
 * @param com 
 * @param buffer 
 * @return 1 whether is announce 0 otherwise
 */
int isGetfile(command* com, char* data);
/**
 * With this method verify whether a command is update 
 * @param com 
 * @param buffer 
 * @return 1 whether is announce 0 otherwise
 */
int isUpdate(command* com, char* data);
/**
 * With this method is verify whether a command is known 
 * @param com 
 * @param buffer 
 * @return 1 whether is known command 0 otherwise
 */
int whatCommand(command* com, char* data);
/**
 * With this method is obtained the number identifier by a command
 * @param com 
 * @param buffer 
 */
int getCommandFromString(char* cmd);
/**
 * With this method is obtained the char* identifier by a command
 * @param type 
 */
char* getCommandFromInt(int type);

#endif /*oreo_trackersockethandle.h*/
