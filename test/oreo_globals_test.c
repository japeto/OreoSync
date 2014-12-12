/**
 * @file oreo_datastructure.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief
 * @see
 */

#include "oreo_globals.h"

static int DEBUG_MODE = 0;
static int WARN_SILENT = 1;
static int LOG_SILENT = 1;

int main(int argc, char** argv){

		if (argc > 1) {
			int i;
			for(i=0;i<argc;i++){
				if(strcmp(argv[i],"--debug") ==0){
					 printf("**DEBUG_MODE ON**\n");
					 DEBUG_MODE = 1;
				}else if(strcmp(argv[i],"--fno-log") ==0){
					 printf("**LOG SILENT ON**\n");
					 LOG_SILENT = 0;
				}else if(strcmp(argv[i],"--w") ==0){
					 printf("**WARN SILENT ON**\n");
					 WARN_SILENT = 0;
				}
			}
		}
		
        printf("****************************************\n");
        printf("GLOBALS TESTs \n");                   
		printf("****************************************\n");        
		printf("TCP_PROTOCOL_NUMBER [%d]\n", TCP_PROTOCOL_NUMBER);
		printf("DEFAULT_PORT [%d]\n", DEFAULT_PORT);
		printf("CONCURRENT_PEERS [%d] \n",CONCURRENT_PEERS);
		printf("BUFFER_SIZE [%d]\n", BUFFER_SIZE);
		printf("****************************************\n");   
			DEBUG_MSG("THIS DEBUG MESSAGE\n");        
			WARN_MSG("THIS WARNING MESSAGE\n");
			LOG_MSG("THIS LOG MESSAGE\n");
			
		
}

