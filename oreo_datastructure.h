/**
 * @file oreo_datastructure.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief 
 * @see 
 */
#ifndef OREO_DATASTRUCTURE_H
#define OREO_DATASTRUCTURE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

enum connstatus{
	STATUS_DISCONNECTED,
	STATUS_DOWNLOADING,
	STATUS_CONNECTED
};

struct IPv4{
    unsigned char b1, b2, b3, b4;
};

/**
 * @brief  this typestruct store necesary by known a peer
 */
typedef struct 
{
  int socketFd;							/**< client socket accept connection*/
  struct sockaddr_in* infoConnection;	/**< socket information*/
  int idConnection;						/**< Connection identifier*/
  int* stateConnection;					/**< Connection status  */
  
} dataPeer; /*data peer alias*/

typedef struct vector{
    
    int capacity;
    int size;
    void **data;    
    
} vector;

vector* newVector(int element_size, int initial_max);
vector* addElement(vector* vec,void* e);
vector* addElementIn(vector* vec,int position,void* element);
vector* removeElement(vector* vec);
vector* removeElementIn(vector* vec,int position);

void* getElementVector(vector* vec);
void* getElementVectorIn(vector* vec,int position);
int contains(vector* vec,void* e);
void vector_resize(vector *vec, int capacity);
void freeVector(vector *vec);
void removeAllElements(vector *vec);
void printv(vector* vec);

typedef struct aPeer{
    char* name;
    char* ip;
    char* port;
    int status;
} aPeer;

aPeer* createPeer(char* alias,char* ip, char* port,int status);
aPeer* newaPeer(char* ip, char* port);
void freePeer(aPeer* p);
aPeer* getPeerByIp(vector* vec ,char* ip);
void addPeer(vector* vec,aPeer* p);

typedef struct afolder{
	char** key; 
	void** data;
	int size;
	int elements;
} afolder;

afolder* newafolder(int element_size);
void freeafolder(afolder* ind);
void addFiletoafolder(afolder* ind,char* key, void* data);
void* getFiletoafolder(afolder* ind,char* key);
char* getKey(afolder* ind,void* data);
int containsfile(afolder* ind,char* key);

#endif

