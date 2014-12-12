/**
 * @file oreo_globals.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief 
 * @see 
 */
#ifndef OREO_GLOBALS_H
#define OREO_GLOBALS_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//~ #define OREO_DEBUG_MODE       1
#define OREO_LOG              1
//~ #define OREO_WARN             0

#ifdef OREO_DEBUG_MODE
        #define DEBUG(msg, ...) fprintf(stderr,"DEBUG: "msg)
    #else
        #define DEBUG(msg, ...) (void)0        
#endif

#ifdef WARN
        #define WARN(msg, ...) fprintf(stderr,"WARNING: "msg)
    #else
        #define WARN(msg, ...) (void)0
#endif

#ifdef LOG
        #define LOG(msg, ...) fprintf(stderr,"LOG: "msg)
    #else
        #define LOG(msg, ...) (void)0
#endif

static const int OREO_TRACKER_TEST =      0;
/**
 * @see http://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml
 * @see http://tools.ietf.org/html/rfc793
 */
static const int TCP_PROTOCOL_NUMBER = 6;
/**
 * Port in run oreo tracker
 */
static const int PORT = 8907;
/**
 * Num max peer in concurrent connection
 */
static const int PEERCONCURRENT = 10;
/**
 * 
 */
static const int BUFFER_SIZE = 2048;

#endif
