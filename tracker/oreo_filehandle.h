/**
 * @file oreo_filehandle.h
 * @author Jefferson Amado Peña Torres, jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief This file contains the Monitor file activity invokes a inotify struct when files that you specify in OreoSync folders.
 * @see aFolder
 * @see aFile
 */
 
#ifndef OREO_FILEHANDLE_H
#define OREO_FILEHANDLE_H

#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <stdio.h> 


#include "oreo_datastructure.h"
#include "oreo_globals.h"

//~ extern tracker* oreoTracker;
/**
 * @brief This method monitor OreoSync folder. 
 * @param [a_dirpath] paths of OreoSync folder
 */
void folderMonitor(char * a_dirpath);

#endif
