/**
 * @file oreo_tracker.h
 * @author Jefferson Amado Pe&ntilde;a Torres,(jeffersonamado@gmail.com),JAPeTo
 * @date 21 Nov 2014
 * @brief This file contains necesary functions for handle the oreo tracker module.
 * @see aModuleTracker
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

#include "oreo_sockethandle.h"
#include "oreo_datastructure.h"
#include "oreo_filehandle.h"
#include "oreo_globals.h"
/**
 * @brief Allocate memory by a aModuleTracker object
 * @return A new aModuleTracker empty
 * @retval A aModuleTracker Neither files nor peer
 * @retval NULL  Oops, did something.
 */
aModuleTracker* new_tracker();
/**
 * @brief Deallocate the allocate memory by
 * this aModuleTracker element
 * @param [server] a aModuleTracker element to delete
 */
void freetracker(aModuleTracker* server);
/**
 *  @brief start module tracker
 */
void run_tracker();
/**
 * @brief This method add file to OreoTracker global var
 * @param [a_folder] folder object
 * @param [a_file] file to addto folder
 */
void add_file_tracker(aFolder* a_folder,aFile* a_file);


/**
 * @brief
 * @param
 * @param
 */
void addSeederTofile(aPeer* p,char* file); //sembrador de archivos
/**
 * @brief
 */
void updatePeers();
/**
 * @brief
 * @param
 * @param
 */
int existSeeder(aVector* vec,aPeer* p);

aModuleTracker* OreoTracker;

#endif /*tracker.h*/

