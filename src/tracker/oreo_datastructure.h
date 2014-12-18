/*
 ** oreo_datastructure.h
 **
 ** Copyright 2014 Jefferson Amado Peña <jeffersonamado@gmail.com>
 **
 ** This program is free software; you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program; if not, write to the Free Software
 ** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 ** MA 02110-1301, USA.
 **
 */
/**
 * @file oreo_datastructure.h
 * @author Jefferson Amado Pe&ntilde;a Torres,(jeffersonamado@gmail.com),JAPeTo
 * @date 21 Nov 2014
 * @brief This file is a particular way of organizing data in OreoSync,
 * here define types and data structures
 */
#ifndef OREO_DATASTRUCTURE_H
#define OREO_DATASTRUCTURE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "sha1.h"  /* from RFC3174 */
#include "md5.h"  /* from RFC1321 */
#include "oreo_globals.h"

/**
 * @brief A connection state (session) with a specific Peer identified IP and Port
 * maintained a status in others peers
 */
enum ConnStateType{
  STATE_DISCONNECTED,		/*!< The peer is dis-connected*/
  STATE_CONNECTED,			  /*!< The peer is connected*/
  STATE_BROKEN,         /*!< The connection to the peer is broken*/
	STATE_DOWNLOADING		/*!< The peer is downloading*/
};
/**
* @brief Define a chunk preserving their most relevant characterisctics
*
* This struct abstract a chunk having its characterics as:
* file, status,size.
*
* @see http://es.wikipedia.org/wiki/Offset_(inform%C3%A1tica)
* @see http://es.wikipedia.org/wiki/Secure_Hash_Algorithm#SHA-1
//~ */
typedef struct aChunk{
  /**
   * @brief Has value
   */
  char* key;
  /**
   * @brief path chunk
   */
  char* path;
} aChunk;
/**
 * @brief A aChunklist allow quikly seek of keys
 */
typedef struct aChunkList{
  /**
   * @brief Collection of aChunk objects
   * @see aChunk
   */
  aChunk** chunks;
  /**
   * @brief Collection of hash key  values
   */
  char** key;
  /**
   * @brief Number elements in aChunklist struct
   */
  int elements;
} aChunkList ;
/**
 * @brief Allocate memory by a new aChunk object
 */
aChunk* newchunk();
/**
 * @brief This print/show a aChunk struct
 * @param [a_chunk] chunk to print
 */
void chunk_toString(aChunk* a_chunk);
/**
 * @brief Allocate memory by a new aChunkList object
 */
aChunkList* newchunkList();
/**
 * @brief With this method is add a chunk to chunklist struct
 * @param [a_chunklist] store all chunks in tracker
 * @param [a_chunk] chunk to add
 */
void add_chunk(aChunkList* a_chunklist,aChunk* a_chunk);
/**
 * @brief With this method is obtained the path chunk from  ¿key
 * @param [a_chunklist] store all chunks in tracker
 * @param [key] key to seek
 * @return path
 */
char* get_chunk_path(aChunkList* a_chunklist,char* key);
/**
 * @brief This method print a aChunkList struct
 * @param [a_chunklist] chunklist to print
 */
void chunklist_toString(aChunkList* a_chunklist);
/**
 * @brief A struct dataPeer represent a peer,
 * used to manage connections, submit transactions, and query.
 */
typedef struct {
  /**
  * @brief Each peer has a unique
  * temporal number identification,
  * This allow multiple peer
  * and one thread for peer
  */
  int idConnection;
  /**
   *@brief Structures for handling
  * internet addresses
  * These are the basic structures
  * for all syscalls and functions
  * that deal with internet addresses
  */
  struct sockaddr_in* infoConnection;
  /**
  * @brief Upon successful completion,
  * accept() shall return the
  * non-negative file descriptor
  * of the accepted socket.
  *
  * @return A new descriptor
  * @retval identifier accept connection return the decriptor
  * @retval -1 shall be returned and errno set to indicate the error
  */
  int socketFd;
  /**
  *@brief The ConnectionState values
  *  are used by the State definite in  ConnStateType@see ConnStateType
  */
  int* connectionState;
} dataPeer; /*data peer*/

/**
 * @brief A struct aVector implements an array with
 * fast random access and an ability to automatically
 * resize when appending elements.
 *
 * aVector is abstract a container where can be accessed
 * sequentially, aaVector allow the user to denote an initial
 * capacity for the container and size of elements
 */
typedef struct aVector{

    int capacity;		  /*!<
                      * capacity Max capacity in aVector,
                      * Note: this can be grow
                      */
    int size;			    /*!< This is the number of actual
                      * objects held in the aVector,
                      * which is not necessarily equal
                      * to its storage capacity
                      */
    void **data;    	/*!< data An encoded format
                      *for converting a specific
                      * type of data to storable information
                      */

} aVector;

/**
 * @brief This method make a new aVector empty
 * @param [element_size] size of data
 * @param [initial_max] set a capacity value in type struct aVector
 * @return a new aVector empty ready by save new values
 */
aVector* new_vector(int element_size, int initial_max);
/**
 * @brief Appends the specified element to the end of this Vector.
 * @param [a_vector] vector
 * @param [element] specified element
 * @return vector with new value add
 */
aVector* addElement(aVector* a_vector,void* element);
/**
 * @brief Inserts the specified element at the specified position in this Vector.
 * @param [a_vector] vector
 * @param [position] specified position
 * @param [element] specified element
 * @return vector with new value add
 */
aVector* addElementIn(aVector* a_vector,int position,void* element);
/**
 * @brief Removes the element at the last position in this Vector.
 * @param [a_vector] vector
 * @return vector without last value
 */
aVector* removeElement(aVector* a_vector);
/**
 * @brief Removes the element at the specified position in this Vector.
 * @param [a_vector] vector
 * @param [position] specified position
 * @return vector without specified element in vector
 */
aVector* removeElementIn(aVector* a_vector,int position);
/**
 * @brief Returns the element at the last position in this Vector.
 * @param [a_vector] vector
 * @return element in (void*) format
 */
void* getElementVector(aVector* a_vector);
/**
 * @brief Returns the element at the last position in this Vector.
 * @param [a_vector] vector
 * @param [position] position
 * @return element in (void*) format
 */
void* getElementVectorIn(aVector* a_vector,int position);
/**
 * @brief Returns 1 if this vector contains the specified element.
 * @param [a_vector] vector
 * @param [element] vector
 * @return indicates whether a element into a vetor
 * @retval 2 This vector contains the element
 * @retval 1 This no content this element
 */
int contains(aVector* a_vector,void* element);
/**
 * @brief Private resize
 * @param [a_vector] vector
 * @param [capacity] vector
 */
void vector_resize(aVector* a_vector, int capacity);
/**
 * @brief Deallocates the memory previously allocated by this vector
 * @param [a_vector] vector
 */
void freeVector(aVector *a_vector);
/**
 * @brief Removes all components from this vector and sets its size to zero.
 * @param [a_vector] vector
 */
void removeAllElements(aVector *a_vector);
/**
 * @brief  Print a string representation of this Vector,
 * containing the String representation of each element.
 * @param [a_vector] vector
 */
void vector_toString (aVector* a_vector);

/**
 * @brief A struct aPeer refers a particular instance
 *  of a peer connected where this aPeer has name
 * or alias, a IP , a PORT and status.
 */
typedef struct aPeer{
    char* name;     /*!< name alias or nickname the peer */
    char* ip;       /*!< ip address in IPv4 format */
    char* port;     /*!< port port in run OreoSync */
    int status;     /*!< status peer status */
} aPeer;
/**
 * @brief This method make empty aPeer.
 * @param [alias] name alias or nickname the peer
 * @param [ip]    ip address in IPv4 format
 * @param [port]  port port in run OreoSync
 * @param [status] status peer status
 * @return empty aPeer
 */
aPeer* createPeer(char* alias,char* ip, char* port,int status);
/**
 * @brief This method make empty aPeer.
 * @param [ip]    ip address in IPv4 format
 * @param [port]  port port in run OreoSync
 * @return empty aPeer
 */
aPeer* newaPeer(char* ip, char* port);
/**
 * @brief This method Deallocate memory allocate by aPeer object.
 * @param [a_peer] peer to delete
 */
void freePeer(aPeer* a_peer);
/**
 * @brief This method obtained aPeer object from ip.
 * @param [a_vector] vector of peers
 * @param [ip]  ip address to seek
 * @return peer found
 * @retval apeer peer found with ip
 * @retval NULL peer no found
 */
aPeer* getPeerByIp(aVector* a_vector ,char* ip);
/**
 * @brief This method obtained aPeer object from name or alias.
 * @param [a_vector] vector of peers
 * @param [ip]  ip address to seek
 * @return peer found
 * @retval apeer peer found with ip
 * @retval NULL peer no found
 */
aPeer* getPeerByName(aVector* a_vector ,char* ip);
/**
 * @brief This method add aPeer object to peer vector.
 * @param [a_vector] vector of peers
 * @param [a_peer] peer to add
 */
void addPeer(aVector* a_vector,aPeer* a_peer);

/**
 * @brief A struct aFile implemetns an abstract,
 * system view of hierarchical pathnames, used to
 * retrieve and handle files from within one's own computer.
 */
typedef struct aFile{
  FILE * file_handle;   		/*!< file_handle Is an abstract indicator
                            *or descriptor for accessing to file.
                            *
                            * Object FILE identifies a stream and
                            * contains the information needed to
                            *  control it, including a pointer to
                            * its buffer, its position indicator
                            * and all its state indicators. */

  char* simple_name;  			/*!< simple_name It identifies a
                            *specific file, and differentiates
                            * that file from other members of a folder
                            *
                            * Note: this given name has extension
                            * and test.txt is diferent that text.mp3 */

  char* dir_path;				    /*!< dir_path It identifies specifies
                            *a unique location in a file system.
                            * A path points to a file system location
                            * by following the directory tree hierarchy
                            * expressed in a string of characters
                            * in which path components */

  unsigned char name_sha[20];	/*!< name_sha give name in sha algortimh*/
  unsigned char* name_md5;  	/*!< name_md5 give name in md5 algortimh*/
  struct stat file_stat;		  /*!< file_stat a system struct that
                              * is defined to store information about files
                              */
  char* chunks_path;			    /*!< chunks_path path the file chunks
                              * associated to file
                              */
  unsigned long file_size;		/*!< file_size number of bytes that
                              * indicates how much storage is
                              * associated with the file
                              */

} aFile;
/**
 * @brief Allocate memory by a new aFile object
 * @param [a_file_name] file name
 * @param [a_file_size] size of file
 * @param [a_file_path] path of file
 * @return a new empty aFile
 */
aFile* newafile(char *a_file_name,long a_file_size,char* a_file_path);

/**
 * @brief With this method load a struct afile whit file information in the pathname
 * @warning whether the file no open or no could be read
 * @param [a_file_path] A pathname file
 * @return A struct file loaded
 */
aFile * open_afile(char * a_file_path);
/**
 * @brief With this method make a chunk list from file information in the pathname
 * @warning whether the file no open or no could be read
 * @param [a_file] A pathname file
 * @return path chunk list path
 */
char* create_chunk_list(aFile* a_file);
/**
 * @brief writes the string c,known as char*, to stream.
 * @param [a_file] A pathname file
 * @return void
 */
void file_toString(aFile* a_file);
/**
 * @brief This method print a folder content.
 * @param [a_file] A pathname file
 * @return void
 */
void freeafile(aFile* a_file);
/**
 * @brief A struct afolder is the way an OreoSync handle the <b>oreo folder</b>
 * its folder contains files are tipically shared to peers.
 */
typedef struct aFolder{
    aFile** files;				  /*!< files a directory or folder is a cataloging structure which contains references to files, and possibly other directories*/
    char** namefile;			/*!< namefile This is equal to simple_files is used for performance seek in folder*/
    int size;						  /*!< size This value indicates number of elements in folder*/
    int elements;				  /*!< elements This value indicates the max number of elements that folder managed*/
} aFolder;
/**
 * @brief This method allocate memory by a new aFolder object
 * @param [element_size] number the elements in folder
 * @return aFolder struct
 * @retval empty aFolder struct
 * @retval NULL not allocate memory by aFolder
 */
aFolder* newafolder(int element_size);
/**
 * @brief This method add a file to aFolder object.
 * @param [a_folder] folder object with content
 * @param [a_file] file to add to folder struct
 * @param [a_filename] name file to add, this is used by search
 */
void add_file(aFolder* a_folder,aFile* a_file,char* a_filename);
/**
 * @brief  This method return a chunk list path according to file.
 * @param [a_folder] folder content
 * @param [a_filename] name file to search
 * @return path of file with chunk list
 */
char* get_filechunk_path(aFolder* a_folder,char* a_filename);
/**
 * @brief  This method return the folder identifier
 * @param [a_folder] folder content
 * @param [a_filename] name file to search
 * @return identifier to file in folder
 */
int get_id_file(aFolder* a_folder,char* a_filename);
/**
 * @brief This method verify whether contains file or not.
 * @param [a_folder]
 * @param [a_filename]
 * @return The folder contains file
 * @retval 0 Success, contains file
 * @retval 1 No contains file
 */
int contains_file(aFolder* a_folder,char* a_filename);
/**
 * @brief This method print aFolder content
 * @param [a_folder] folder to print
 */
void folder_tostring(aFolder* a_folder);
/**
 * @brief This method deallocate memory allocate by aFolder object.
 * @param [a_folder]
 */
void freeafolder(aFolder* a_folder);
/**
 * @brief A struct aModuleTracker implement a search
 * system for OreoSync, this is remarkable struct contains
 * links tos files and peers connections.
 */
typedef struct aModuleTracker{
  /**
  * @brief files Is an indexer for a files in system
  * @see aFolder
  * @see aFile
  */
  aFolder* folder;
  /**
   * @brief peers Is a vector that contains peers
   * connected to this module
   * @see aVector
   * @see aPeer
   */
  aChunkList* chunklist;
  /**
   * @brief peers Is a vector that contains peers
   * connected to this module
   * @see aVector
   * @see aPeer
   */
  aVector* peers;

} aModuleTracker;
/**
 * @brief global var
 * @details An indexer allows instances of a particular class
 * or struct to be indexed just like arrays
 */
extern aModuleTracker* OreoTracker;


#endif

