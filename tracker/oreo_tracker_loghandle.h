/**
 * @file oreo_tracker_loghandle.h
 * @author     Jefferson Amado Peña Torres (JAPeTo), jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief Each log message in the logs consists of the following:
 * <ul>
 * <li>The date and time of the log message</li>
 * <li>A type of the log message</li> 
 * <li>The source of the log message, which is either 
 * the tracker module or client module</li>
 * <li>The text of the log message</li> 
 * </ul>
 * @see 
 */
#ifndef OREO_TRACKER_LOGHANDLE
#define OREO_TRACKER_LOGHANDLE

#include <stdlib.h>
#include <stdio.h>
//~ #include <system.h>
#include "oreo_globals.h"
#include "oreo_datastructure.h"

/**
 * @brief  logs a message to LOG_PATH
 * @param [message] message to write in log file
 * @param [tyep]  type of  message to write in log file
 * @see  LogMessageType
 */
void writelog(char* message);
/**
 * @brief  logs a message to LOG_PATH
 * @param [message] message to write in log file
 */
void writelogErr(char* message); 


#endif /*OREO_TRACKER_LOGHANDLE*/
