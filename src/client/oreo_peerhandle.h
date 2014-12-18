/**
 * @file oreo_peerhandle.h
 * @brief     This class implements necessary method by load and write peer files
 * @details   <b>OreoSync</b> read node file and load address and port the peer 
 *              associated
 * @author     Jefferson Amado Peña Torres, jeffersonamado@gmail.com
 * @date       Dec 13, 2014
 * @version    0.1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /**
  * Indiates path of log file
  */
#define PEERPATH "peer.txt"

/**
 * Indicate max length of string in config file
 */
#define MAXBUF 1024
/**
 * Indicate max number of peer in peer file
 */
#define MAXPEERS 800

/**
 * 
 * @brief A struct aNode is a peer representation as aPeer
 * @see aPeer, this struct handle node peers file
 */
typedef struct aNode{
        int id;                 /*!< <b>id</b> identifier by peer */
        char * address;         /*!< <b>address</b> address of other peer */
        unsigned short port;    /*!< <b>port</b> port listen commands of peer */
}aNode;

/**
 * @brief      Read peer or node file
 *
 * @details    This method read a plain text file with peer format,
 *              where attributes
 *                      <ul>
 *                         <li> [ID]    [IP]            [PORT]
 *                      </ul>
 * @note       The tags in this order
 *
 * @param      filename path of log
 *
 * @return     The file log loaded in aNode struct
 * @see aNode elements of type aNode
 * 
 */
aNode * node_parser(char * filename);

/**
 * @brief      write peer or node file
 *
 * @details    This method read a plain text file with peer format,
 *              where attributes
 *                      <ul>
 *                         <li> [ID]    [IP]            [PORT]
 *                      </ul>
 * @note       The tags in this order
 *
 * @param      a_node
 *
 * @return     The file log loaded in aNode struct
 * @see aNode elements of type aNode
 * 
 */
int peer_update(aNode** a_node);

