/**
 * @file tracker.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing 
 *
 * @see 
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

#include "oreo_sockethandle.h"
#include "oreo_datastructure.h"
#include "oreo_filehandle.h"
#include "oreo_globals.h"

typedef struct tracker{
        afolder* files;
        vector* peers; 
} tracker;

tracker* oreoTracker;

tracker* newTracker();
void freetracker(tracker* server);
void addFile(afile* file);
void addSeederTofile(aPeer* p,char* file); //sembrador de archivos
void updatePeers();
int existSeeder(vector* vec,aPeer* p);

#endif /*tracker.h*/

