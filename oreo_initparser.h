/**
 * @file oreo_initparser.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing 
 * @see 
 */

#ifndef OREO_INITPARSER_H
#define OREO_INITPARSER_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>

extern struct initoreo *initinfo;
/**
 * @brief 
 *
 */
struct initoreo{
        unsigned char alias[256];
        unsigned char home[512];
        unsigned char log[256];
        //~ double chunksize[256];
	unsigned short int trackerport;
	unsigned char trackercachefolder;
	short int trackercacheconcurrent;
	unsigned short int clientport;
        unsigned char clientnegborlist;
};
/**
 * 
 */
void pritinitinfo();
/**
 * @param
 * @return
 */
int loadinitinfo(char *fileName);


#endif /* */

