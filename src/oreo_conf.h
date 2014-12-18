/**
 * @file oreo_conf.h
 * @brief     This class implements necessary method by load and write config files
 * @details   <b>OreoSync</b> read config file and load configuration
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
#define LOGPATH "oreo.conf"
/**
 * Indicate max length of string in config file
 */
#define MAXBUF 1024
/**
 * regex delimiter by separate attributes and values
 */
#define DELIM "="
/**
 * @brief A struct config define a config file data
 */
typedef struct config{
        unsigned char* alias;                   /*!< <b>alias</b> 
                                                * given name user*/
        unsigned char* home;                    /*!< <b>home</b> path 
                                                * by <b>OreoSync</b> folder*/
        unsigned char* log;                     /*!< <b>log</b> path 
                                                * by <b>OreoSync</b> log file*/
        unsigned char* cachefolder;             /*!< <b>cachefolder</b> 
                                                * path by <b>OreoSync</b>
                                                * cache folder*/
        unsigned short int trackerport;         /*!< <b>trackerport</b> 
                                                * port identifier by 
                                                * <b>OreoSync</b> tracker module*/        
        unsigned short int clientport;          /*!< <b>clientport</b> 
                                                * port identifier by 
                                                * <b>OreoSync</b> client module*/        
        unsigned char* clientneigborlist;       /*!< <b>clientneigborlist</b> 
                                                * path by <b>OreoSync</b> 
                                                * file node*/
        unsigned short int concurrent;          /*!< <b>concurrent</b> 
                                                * number download concurrents
                                                */
        unsigned short int DEBUGMODE;           /*!< Activate debug mode
                                                * the show events which
                                                * happen while <b>OreoSync</b> run*/
        unsigned short int GUIMODE;             /*!< Activate gui mode and
                                                * the show GUI <b>OreoSync</b> run*/
        unsigned short int WARMSILENT;          /*!< silent warning what
                                                happen while <b>OreoSync</b> run*/
        unsigned short int LOGSILENT;           /*!< no records the events which
                                                happen while <b>OreoSync</b> run*/
        unsigned short int ERRSILENT;           /*!< Silent error which happen
                                                while <b>OreoSync</b> run*/

}config;

/**
 * @brief      Read log file
 *
 * @details    This method read a plain text file with config format,
 *              where attributes
 *                      <ul>
 *                         <li> ALIAS
 *                         <li> HOME
 *                         <li> SERVERPORT
 *                         <li> CLIENTPORT
 *                         <li> CONCURRENTDOWNLOADS
 *                         <li> NEIGHBORLIST
 *                         <li> LOGFILE
 *                         <li> CACHEFOLDER
 *                         <li> DEBUGMODE
 *                         <li> GUIMODE
 *                         <li> LOGSILENT
 *                         <li> ERRSILENT
 *                      </ul>
 * @note       The tags in this order
 *
 * @param      filename path of log
 *
 * @return     The file log loaded in config struct
 * @see config elements of type config
 * 
 */
config * config_parser(char * filename);

/**
 * @brief      Write log file
 *
 * @details    This method write a plain text file with config format,
 *              where attributes
 *                      <ul>
 *                         <li> ALIAS
 *                         <li> HOME
 *                         <li> SERVERPORT
 *                         <li> CLIENTPORT
 *                         <li> CONCURRENTDOWNLOADS
 *                         <li> NEIGHBORLIST
 *                         <li> LOGFILE
 *                         <li> CACHEFOLDER
 *                         <li> DEBUGMODE
 *                         <li> GUIMODE
 *                         <li> LOGSILENT
 *                         <li> ERRSILENT
 *                      </ul>
 * @note       The tags in this order
 *
 * @param      configstruct struct to write
 * @return     The write file boolean status
 *
 * @retval     status   The write status.
 *                      <ul>
 *                         <li> 0 = Success, write new conf file
 *                         <li> 1 = No can be write new conf file 
 *                      </ul>  
 * @see config elements of type config
 */
int config_write(config* configstruct);
