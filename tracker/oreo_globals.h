/**
 * @file oreo_globals.h
 * @author     Jefferson Amado Peña Torres, jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief This file contains the definition
 * the several variables with global scope,
 * meaning that it is visible, 
 * this set of all global variables some use 
 * he default is external linkage. "extern".
 * @see http://wiki.bash-hackers.org/scripting/terminalcodes
 * @see http://misc.flogisoft.com/bash/tip_colors_and_formatting
 * @see http://superuser.com/questions/270214/how-can-i-change-the-colors-of-my-xterm-using-ansi-escape-sequences
 */
#ifndef OREO_GLOBALS_H
#define OREO_GLOBALS_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
/**
 * @brief Enable/Disable the debug mode by <b>OreoSync</b>
 * 
 * @details This allows the user to view and/or 
 * manipulate the OreoSync's internal state
 * 
 * Example usage:
 * @code
 * oreosync --debug
 * @endcode
 * 
 */
extern int DEBUG_MODE; 
/**
 * @brief Enable/Disable the warning mode by <b>OreoSync</b>
 * @details  This Warnings are diagnostic messages 
 * that report constructions that are 
 * not inherently erroneous but that 
 * are risky or suggest there may have been 
 * an error.
 * 
 * Example usage:
 * @code
 * oreosync --w
 * @endcode
 * 
 */
extern int WARN_SILENT;
/**
 * @brief Enable/Disable the log silent mode by <b>OreoSync</b>
 * @details  This mode no write in log file
 * 
 * Example usage:
 * @code
 * oreosync --log-silent
 * @endcode
 * 
 */
extern int LOG_SILENT;
/**
 * @brief Enable/Disable the error mode by <b>OreoSync</b>
 * @details  This Errors are messages 
 * that report constructions that are 
 * erroneous but that are risky or suggest 
 * there may have been an error.
 * 
 * Example usage:
 * @code
 * oreosync --Err
 * @endcode
 * 
 */
extern int ERR_SILENT;
//~ http://superuser.com/questions/270214/how-can-i-change-the-colors-of-my-xterm-using-ansi-escape-sequences
/**
 * @brief ANSI escape sequences 
 * consist of a sequence of characters 
 * that print color 
 * @details  The ANSI standard defines 8 colours,
 * plus a bright mode, giving a total of 
 * 16 posibilities. The sequence
 * @code 
 * \e[<number>message
 * @endcode
 * Where number is <b>31</b> by Red color
 * */
#define ANSI_COLOR_RED     "\x1b[31m"
/**
 * @brief ANSI escape sequences 
 * consist of a sequence of characters 
 * that print color 
 * @details The ANSI standard defines 8 colours,
 * plus a bright mode, giving a total of 
 * 16 posibilities. The sequence
 * @code 
 * \e[<number>message
 * @endcode
 * Where number is <b>32</b> by Green color
 * */
#define ANSI_COLOR_GREEN   "\x1b[32m"
/**
 * @brief ANSI escape sequences 
 * consist of a sequence of characters 
 * that print color 
 * @details  The ANSI standard defines 8 colours,
 * plus a bright mode, giving a total of 
 * 16 posibilities. The sequence
 * @code 
 * \e[<number>message
 * @endcode
 * Where number is <b>33</b> by Yellow color
 * */
#define ANSI_COLOR_YELLOW  "\x1b[33m"
/**
 * @brief ANSI escape sequences 
 * consist of a sequence of characters 
 * that print color 
 * @details  The ANSI standard defines 8 colours,
 * plus a bright mode, giving a total of 
 * 16 posibilities. The sequence
 * @code 
 * \e[<number>message
 * @endcode
 * Where number is <b>34</b> by Blue color
 * */
#define ANSI_COLOR_BLUE    "\x1b[34m"
/**
 * @brief ANSI escape sequences 
 * consist of a sequence of characters 
 * that print color 
 * @details  The ANSI standard defines 8 colours,
 * plus a bright mode, giving a total of 
 * 16 posibilities. The sequence
 * @code 
 * \e[<number>message
 * @endcode
 * Where number is <b>35</b> by Magenta color
 * */
#define ANSI_COLOR_MAGENTA "\x1b[35m"
/**
 * @brief ANSI escape sequences 
 * consist of a sequence of characters 
 * that print color 
 * @details  The ANSI standard defines 8 colours,
 * plus a bright mode, giving a total of 
 * 16 posibilities. The sequence
 * @code 
 * \e[<number>message
 * @endcode
 * Where number is <b>36</b> by Cyan color
 * */
#define ANSI_COLOR_CYAN    "\x1b[36m"
/**
 * @brief ANSI escape sequences 
 * consist of a sequence of characters 
 * that print color 
 * @details  The ANSI standard defines 8 colours,
 * plus a bright mode, giving a total of 
 * 16 posibilities. The sequence
 * @code 
 * \e[<number>message
 * @endcode
 * Where number is <b>0</b> by Reset or not color
 * */
#define ANSI_COLOR_RESET   "\x1b[0m"

#ifndef DEBUG_MSG  
#define DEBUG_MSG(...) if(DEBUG_MODE){ fprintf(stderr,ANSI_COLOR_YELLOW "DEBUG: " __VA_ARGS__ );fprintf(stderr, ANSI_COLOR_RESET );}
#endif

#ifndef MSG  
#define MSG(...) if(DEBUG_MODE){ fprintf(stderr, __VA_ARGS__ );}
#endif

#ifndef WARN_MSG
#define WARN_MSG(...)if(WARN_SILENT){fprintf(stderr,ANSI_COLOR_MAGENTA"WARNING: " __VA_ARGS__ ANSI_COLOR_RESET); fprintf(stderr,ANSI_COLOR_RESET);}
#endif

#ifndef LOG_MSG
#define LOG_MSG(msg, ...)if(LOG_SILENT){ writelog(msg);/*fprintf(stderr,ANSI_COLOR_CYAN"LOG: "msg ANSI_COLOR_RESET);*/}
#endif

#ifndef ERR_MSG
#define ERR_MSG(msg, ...)if(ERR_SILENT){fprintf(stderr,ANSI_COLOR_RED"ERROR: "msg ANSI_COLOR_RESET);}
#endif

static const char* LOG_PATH = "./oreolog.log";
static const char* HOME_PATH = ".log";
static const char* USER_HOME = "/home/japeto/OreoSync";
//~ static const char* USER_HOME = "/afs/eisc/user/pregrado/2014/japeto/OreoSync";

/**
 * @see http://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml
 * @see http://tools.ietf.org/html/rfc793
 */
static const int TCP_PROTOCOL_NUMBER = 6;
/**
 * Port in run oreo tracker
 */
static const int TRACKER_PORT = 8907;
//~ static const int TRACKER_PORT = 5640;
/**
 * Num max peer in concurrent connection
 */
static const int CONCURRENT_PEERS = 10;
/**
 * buffer size, where store the chunks
 */
static const int BUFFER_SIZE = 2048;

static const int CHUNKSIZE = 512*1024;

#endif


//~ printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
//~ printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
//~ printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
//~ printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
//~ printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
//~ printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");
