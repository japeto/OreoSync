/**
 * @file oreo_commandprocessor.h
 * @author Jefferson Amado Pe&ntilde;a Torres,(jeffersonamado@gmail.com),JAPeTo
 * @date 21 Nov 2014
 * @brief This file contains the command processor,
 * here acoording a command sent by peer the server
 * proccess the command a make response.
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
 * @brief A command is processed and
 * according type a response is generated.
 * @param [a_command] This command incomming from other peer
 * @param [ip_address] This is ip address
 * @return generates codes or response acoording to incoming aCommand
 *
 * @retval 202
 * @retval 204
 * @retval 302 SEEK "filename" FOUND.
 * @retval 304 SEEK "filename" NO FOUND.
 * @retval 402
 * @retval 404
 * @retval 502
 * @retval 504
 */
char* process_command(aCommand* a_command, char* ip_address);
/**
 * @brief This method handle the payload of aCommand and
 * obtained the chunk list path the file to seek
 * @param [payload] file names to seek
 *
 * @return a vector with paths of chunklist file paths
 * @retval vector with paths
 * @retval empty vector, no files found
 */
aVector* seek_files(char* payload);
/**
 * @brief A command of type "SEEK" is processed
 * @param [file_paths]  files This is an Vector with file names to seek
 * @return response
 * @retval 202 File found, path of file to sent
 * @retval 204 File not Found.
 */
char* process_seek_command(aVector* file_paths);
/**
 * @brief whith this method is obtained the path of file to sent
 * @param [payload] multiples chunks can be orders
 *
 * @return  response
 * @retval vector with paths
 * @retval empty vector, no files found
 */
aVector* seek_chunks(char* payload);
/**
 * @brief A command of type "GETFILE" is processed
 * @param [key] keys to search in folders
 * @return response
 * @retval vector with paths
 * @retval empty vector, no files found
 */
char* process_sendchunk_command(aVector* key);

//~ #############################################

/**
 * @brief A command of type "update" is processed
 * @param key
 * @param l
 * @param ip
 * @return char* response
 */
char* processUpdatecommand(char* seeders, char* leeches, char* ip);
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
char* updateSeeders(char* string);
/**
 * whith this method is obtained num port associated to client from
 * string
 * @param string
 * @return
 */
char* updateLeeches(char* string);

#endif /*oreo_trackersockethandle.h*/
