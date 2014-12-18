/**
 * @file oreo_commandhandle.h
 * @author Jefferson Amado Pe&ntilde;a Torres,(jeffersonamado@gmail.com),JAPeTo
 * @date 21 Nov 2014
 * @brief This file containing the command handle make enum by commands
 * types, this validate the command on the current connection,
 * transform commmands from an integer or a string.
 */
#ifndef OREO_COMMANDHANDLE_H
#define OREO_COMMANDHANDLE_H
/**
 * @name    Command handle actions
 * @brief   This class manage commands and verify whether
 * a command is <b>GETFILE</b>, <b>SEEK</b>,
 *  <b>UNKNOWN</b>, <b>SENDME</b>
 * @ingroup handle
 *
 * This API provides certain actions by command handle.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "oreo_globals.h"
/**
 * @brief When a peer requests a service,
 * this has a type and data.
 */
typedef enum {
        SEEK_COMMAND, 	 /*!< With this commnad the peer say Send me chunk*/
        SENDME_COMMAND,  /*!< With this commnad the peer say nothing*/
        GETFILE_COMMAND, /*!< With this commnad the peer say sendme this file*/
        REQUEST_COMMAND, /*!< */
        HAS_COMMAND,     /*!< */
        UPDATE,          /*!< With this commnad the peer say upadte mi state or my list*/
        UNKNOWN, 	 /*!< With this commnad the peer say nothing*/
} CommandType;
/**
 * @brief A aCommand allows <b>OreoSync</b>
 * to send request in specified format
 * they are flexible and serve a variety
 * of purposes
 * @see CommandType
 */
typedef struct aCommand{
  CommandType type; 	/*!< <b>type</b> defines a response
                        *to specified command
                        *@see CommandType */
  char* payload;	/*!< <b>command</b> the body of the
                        *command must be well-formed.
                        * This content of message */

} aCommand;

/**
 * @brief This method allow make a new
 * aCommand object
 *
 * @param [size] size  The payload
 * or message content
 *
 * @return A new aCommand empty
 * @retval aCommand empty aCommand
 * @retval NULL  Oops, did something.
 *
 *
 * Example Usage:
 * @code
 *    aCommand command = new aCommand(DATA); //Size od payload
 * @endcode
 */
aCommand* newCommand(int size);
/**
 * @brief Deallocate memory allocate by this aCommand
 * @param [a_command] This is aCommand to delete
 */
void deleteCommand(aCommand* a_command);
/**
 * @brief With this method verify whether a command is announce
 * @param [a_command] This a Command that contains information
 * @param [payload] This is the information
 * @return indicates whether aCommand is Announce or not
 * @retval 0 This aCommand is type <b>UNKNOWN</b>
 * @retval 1 This aCommand is <b>SEEK</b> type @see CommandType
 */
int isSeek(aCommand* a_command, char* payload);
/**
 * @brief With this method verify whether a command is sendme
 * @param [a_command] This a Command that contains information
 * @param [payload] This is the information
 * @return indicates whether aCommand is Announce or not
 * @retval 0 This aCommand is type <b>UNKNOWN</b>
 * @retval 1 This aCommand is <b>SENDME</b> type @see CommandType
 */
int isSendme(aCommand* a_command, char* payload);
/**
 * @brief With this method verify whether a command is getfile
 * @param [a_command] This a Command that contains information
 * @param [payload] This is the information
 * @return indicates whether aCommand is Announce or not
 * @retval 0 This aCommand is type <b>UNKNOWN</b>
 * @retval 1 This aCommand is <b>GETFILE</b> type @see CommandType
 */
int isGetfile(aCommand* a_command, char* payload);
/**
 * @brief With this method verify whether a command is announce
 * @param [a_command] This a Command that contains information
 * @param [payload] This is the information
 * @return indicates whether aCommand is Announce or not
 * @retval 0 This aCommand is type <b>UNKNOWN</b>
 * @retval 1 This aCommand is <b>ANNOUNCE</b> type @see CommandType
 */
int isAnnounce(aCommand* a_command, char* payload);
/**
 * @brief With this method verify whether a command is update
 * @param [a_command] This a Command that contains information
 * @param [payload] This is the information
 * @return indicates whether aCommand is Announce or not
 * @retval 0 This aCommand is type <b>UNKNOWN</b>
 * @retval 1 This aCommand is <b>UPDATE</b> type @see CommandType
 */
int isUpdate(aCommand* a_command, char* payload);
/**
 * @brief With this method is verify
 * whether a command is known or not
 * @param [a_commmand] A command object
 * @param [data] Information transfer from host
 *
 * @return known
 * @retval 1 This aCommand is <b>KNOWN</b> @see CommandType
 * @retval 0 This aCommand is type <b>UNKNOWN</b>
 *
 */
int what_command(aCommand* a_commmand, char* data);
/**
 * @brief This method return the identifier by type of aCommand
 * @param [command] A command object string format
 *
 * @return
 * @retval 1 This aCommand is <b>SEEK_COMMAND</b> type
 * @retval 2 This aCommand is <b>SENDME_COMMAND</b> type
 * @retval 3 This aCommand is <b>GETFILE</b> type
 *
 */
int command_from_string(char* command);
/**
 * @brief This method return the string identifier by type of aCommand
 * @param [type] identifier by type
 *
 * @return
 * @retval SEEK_COMMAND This aCommand is <b>1</b> type
 * @retval SENDME_COMMAND This aCommand is <b>2</b> type
 * @retval GETFILE_COMMAND This aCommand is <b>3</b> type
 *
 */
char* command_from_int(int type);

#endif /*oreo_trackersockethandle.h*/
