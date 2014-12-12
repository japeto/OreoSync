
/**
 * @file oreo_initparser.c
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing 
 * @see 
 */
 
#include "oreo_initparser.h"

void pritinitinfo(){
        printf("alias name: %s\n",initinfo->alias);
	printf("client Port No: %d\n",initinfo->trackerport);
	printf("tracker Port No: %d\n",initinfo->clientport);
	printf("home folder: %d\n",initinfo->home);
	printf("log file: %d\n",initinfo->log);
	printf("peers list: %d\n",initinfo->clientnegborlist);
	printf("concurrent peers: %d\n",initinfo->trackercacheconcurrent);
}

static char* lskip(const char* s)
{
    while (*s && isspace((unsigned char)(*s)))
        s++;
    return (char*)s;
}

int loadinitinfo(char *fileName){
        FILE *f=fopen((char *)fileName,"r");    
        if(f==NULL){
                LOG("Error opening ini file no such file\n");
                DEBUG("Error opening ini file no such file\n");
                return 0;
        }
        unsigned char line[512];
	unsigned char *key, *value;
        while(fgets((char *)readLine, 511, f)!=NULL){
                if(!(*line))
                        continue;
        }
}
