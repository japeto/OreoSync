/**
 * @file oreo_functions.h
 * @author     Jefferson Amado Peña Torres, jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief This file is a particular way of managment functions
 * by <b>OreoSync</b> Client module,here define types and function
 * and structures .
 * Different kinds of data structures are suited to different
 * kinds of applications as aList, aPeer
 */
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

/**
 * @brief This struct hold addresses and port
 */
typedef struct aNode{
        int id;                 /*!< <b>id</b> identifier by peer */
        char * address;         /*!< <b>address</b> address of other peer */
        unsigned short port;    /*!< <b>port</b> port listen commands of peer */
}aNode;

/**
 * @brief Allocate a new node
 * @return A new empty node
 */
aNode* newNode();

/**
 * @brief Deallocate memory allocate by a aNode struct
 */
void freeNode();

/**
 * @brief This method make a new node with address and port
 * @param address address in string format, <b>IPv4</b>
 * @param  cport number by a node
 * @return aNode with address and port specified
 */
aNode* parseNode(char* address, char* cport);

/**
 * @brief This method print a aNode
 * @param peer to print
 */
void peertoString(aNode* peer);

/**
 * @brief This method print a aNode
 * @param node to print
 */

