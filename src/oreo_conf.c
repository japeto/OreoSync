/**
 * oreo_conf.c
 * Definitions in "oreo_conf.h"
 */
#include "oreo_conf.h"

config* config_parser(char *filename){
        config* configstruct = malloc(sizeof(config));
        FILE *file = fopen (filename, "r");
        
        if (file != NULL){
                char line[MAXBUF];
                int i = 0; 
                while(fgets(line, sizeof(line), file) != NULL){
                        //~ printf("DATA: %d] %s",i,line); 
                        if (line[0] == '#') continue;
                        if (line[0] == '\n') continue;
                        char *cfline;
                        cfline = strstr((char *)line,DELIM);
                        cfline = cfline + strlen(DELIM);
                        if (i == 0){            //ALIAS
                                configstruct->alias=strdup(cfline);
                        } else if (i == 1){     //HOME
                                configstruct->home=strdup(cfline);
                        } else if (i == 2){     //SERVERPORT
                                configstruct->trackerport=atoi(cfline);
                        } else if (i == 3){     //CLIENTPORT
                                configstruct->clientport=atoi(cfline);
                        } else if (i == 4){     //CONCURENTDOWNLOADS
                                configstruct->concurrent=atoi(cfline);
                        } else if (i == 5){     //NEIGHBORTLIST
                                configstruct->clientneigborlist=strdup(cfline);
                        } else if (i == 6){     //LOGFILE
                                configstruct->log=strdup(cfline);
                        } else if (i == 7){     //CACHEFOLDER
                                configstruct->cachefolder=strdup(cfline);
                        } else if (i == 8){     //DEBUG
                                configstruct->DEBUGMODE=atoi(cfline);
                        } else if (i == 9){     //GUI
                                configstruct->GUIMODE=atoi(cfline);
                        } else if (i == 10){     //WARN
                                configstruct->WARMSILENT=atoi(cfline);
                        } else if (i == 11){     //LOG
                                configstruct->LOGSILENT=atoi(cfline);
                        } else if (i == 12){     //ERR
                                configstruct->ERRSILENT=atoi(cfline);
                        } else {
                                //~ printf("No loaded"); 
                        }
                        i++;
                } // End while
        }else{
               return NULL;
        } // End if file
       
        fclose(file);   
       
        return configstruct;
 
}

int writeConfig(config* configstruct){
        FILE *conffile;
        conffile = fopen("oreo.conf", "w");
        if (conffile != NULL){
        fprintf(conffile,"##OreoSync base configuration\n");
        fprintf(conffile,"##This a configuration file by OreoSync\n");
        fprintf(conffile,"##Configuration file is used as definition of initial values\n");
        fprintf(conffile,"##appereance, user conf , server and client port\n");
        fprintf(conffile,"##The configuraion files in conf/Oreo/ directory can be \n");
        fprintf(conffile,"##inclued to adda extra features or modify default \n");
        fprintf(conffile,"##configuration of OreoSync\n");
        fprintf(conffile,"\n");
        fprintf(conffile,"#User configuration tags\n");
        fprintf(conffile,"#Alias or given name by user\n");
        fprintf(conffile,"ALIAS=%s\n",configstruct->alias);
        fprintf(conffile,"\n");
        fprintf(conffile,"#User home folder,files to shared\n");
        fprintf(conffile,"HOME=%s\n",configstruct->home);
        fprintf(conffile,"\n");
        fprintf(conffile,"#Server configutation tags\n");
        fprintf(conffile,"#Server module port sent answer \n");
        fprintf(conffile,"#to commands from other peer as SEEK, SENDME etc\n");
        fprintf(conffile,"SERVERPORT=%d\n",configstruct->trackerport);
        fprintf(conffile,"\n");
        fprintf(conffile,"#Numbre of concurrent downloads\n");
        fprintf(conffile,"CONCURRENTDOWNLOADS=%d\n",configstruct->concurrent);
        fprintf(conffile,"\n");
        fprintf(conffile,"#Client configuration tags\n");
        fprintf(conffile,"#Client module sent command as SEEK, SENDME\n");
        fprintf(conffile,"CLIENTPORT=%d\n",configstruct->clientport);
        fprintf(conffile,"\n");
        fprintf(conffile,"#This list peer\n");
        fprintf(conffile,"NEIGHBORLIST=%s\n",configstruct->clientneigborlist);
        fprintf(conffile,"\n");
        fprintf(conffile,"#path by log file \n");
        fprintf(conffile,"LOGFILE=%s\n",configstruct->log);
        fprintf(conffile,"\n");
        fprintf(conffile,"#Here store chunks\n");
        fprintf(conffile,"CACHEFOLDER=%s\n",configstruct->cachefolder);
        fprintf(conffile,"\n");
        fprintf(conffile,"#OreoSync modes \n");
        fprintf(conffile,"#show intreaction messages and operations of OreoSync\n");
        fprintf(conffile,"DEBUGMODE=%d\n",configstruct->DEBUGMODE);
        fprintf(conffile,"\n");
        fprintf(conffile,"#show gui user\n");
        fprintf(conffile,"GUIMODE=%d\n",configstruct->GUIMODE);
        fprintf(conffile,"\n");
        fprintf(conffile,"#silent warning messages\n");
        fprintf(conffile,"WARNSILENT=%d\n",configstruct->WARMSILENT);
        fprintf(conffile,"\n");
        fprintf(conffile,"#not write in log file\n");
        fprintf(conffile,"LOGSILENT=%d\n",configstruct->LOGSILENT);
        fprintf(conffile,"\n");
        fprintf(conffile,"#silent error messages\n");
        fprintf(conffile,"ERRSILENT=%d\n",configstruct->ERRSILENT);
        fprintf(conffile,"\n");
        fclose(conffile);
        return 0;
        }else{
            return 1;    
        }
}
/** **/
