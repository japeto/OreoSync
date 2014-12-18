/* 
 * file oreo_tracker_loghandle.c
 *
 */
#include "oreo_tracker_loghandle.h"


void writelog(char* message){
        
	FILE *file;
        file = fopen(LOG_PATH, "a");		
	if (file != NULL) {                
                char* log= malloc(256);
                time_t mytime;
                mytime = time(NULL);
                char* currtime = ctime(&mytime);
                        currtime[strlen(currtime)-1]='\0';
                sprintf(log,"[%s]\t %s\n",currtime,message);
                fputs(log, file);
                free(log);
		fclose(file);
	}else{
                ERR_MSG("\tloghandle: log file [%s] problem ",LOG_PATH);
                perror("log file problem");
        }
} 

void writelogErr(char *message){
	writelog(message);
	writelog("\n");
	//~ SysShutdown();
}

