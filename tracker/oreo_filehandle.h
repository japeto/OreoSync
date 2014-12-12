/**
 * @file oreo_filehandle.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File 
 * @see 
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
#include <stdio.h> 

#include "oreo_datastructure.h"
#include "sha1.h"  /* from RFC3174 */
#include "md5.h"  /* from RFC3174 */

/**
 * 
 */
double numChunks;
bool offsetalive;

/*
 *  This structure will hold context information for a file
 */
typedef struct afile{
	
  FILE * handle;
  char name[256];  
  char path[1024];
  unsigned char nameSHA1[20];
  unsigned char nameMD5[128];
  unsigned long size;
  vector* seeders;

} afile;
/**
* @brief Define a chunk preserving their most relevant characterisctics
*
* This struct abstract a chunk having its characterics as:
* file, status,size.
*
* @see http://es.wikipedia.org/wiki/Offset_(inform%C3%A1tica)
* @see http://es.wikipedia.org/wiki/Secure_Hash_Algorithm#SHA-1
*/
typedef struct aChunk{
  afile *file;
  char name[256];
  char path[1024];
  unsigned int id ;
  char data[512000];
  unsigned char dataSHA1[20];
  float offset; 
  float size;
} aChunk;
/**
 * @param char* a paht
 * @return afile 
 */
afile * openafile(char * a_file_path);
/**
 * @param a_file_name
 * @param a_file_size
 * @param a_file_part
 * @return afile 
 */
afile * createafile(char *a_file_name,float a_file_size,char* a_file_path);
/**
 * @param afile
 * @return void
 */
void freeafile(afile* a_file);
/**
 * @param a_file
 * @return aChunk
 */
aChunk** readChunks(afile * a_file);
/**
 * @param a_chunk_list
 * @return void
 */
void writeChunks(aChunk ** a_chunks_list);
/**
 * @return double
 */
double getNumChunks();
/**
 * 
 */
void setNumChunks();


void folderMonitor(char * adirpath);

#endif
