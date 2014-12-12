/**
 * @file oreo_commandprocessor.c
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and monitor a connection to oreo tracker
 * @see 
 */
#include "oreo_commandprocessor.h"

extern tracker* oreoTracker;

char* processCommand(command* com, char* ip){
        char* response;
        switch(com->type){
                case ANNOUNCE:  {
                        char* port = announcePort(com->data);
                        char* aseeders = announceSeeders(com->data);
                        char* aleeches = announceLeeches(com->data);
                        //~ debugMessage("trackercommandprocessor: the peer with ip ( %s ) send ANNOUNCE command with seed [%s] in port (%s) and leech [%s]\n",ip,aseeders,port,aleeches);
                        response = processAnnouncecommand(ip,port,aseeders,aleeches);
                        break;
                
                }case LOOK:{
                        //~ debugMessage("trackercommandprocessor: the peer with ip ( %s ) send LOOK command\n",ip);                        
                        
                        char* look = lookElemnts(com->data);
                        response = processLookcommand(look);          
                        
                        break;                
                }case GETFILE: {   
                        //~ debugMessage("trackercommandprocessor: the peer with ip ( %s ) send GETFILE command\n",ip);
                        
                        char* key = getfileKey(com->data);
                        //~ debugMessage("key %s",key);
                        response = processGetfilecommand(key);                        
                        
                        break;                            
                }case UPDATE:{
                        //~ debugMessage("trackercommandprocessor: the peer with ip ( %s ) send UPDATE command\n",ip);
                        
                        char* useeders = updateSeeders(com->data);
                        char* uleeches = updateLeeches(com->data);
                        response = processUpdatecommand(ip, useeders, uleeches);
                        
                        break;                
                }case UNKNOWN:{
                        //~ debugMessage("trackercommandprocessor: the peer with ip ( %s ) send UNKNOWN command\n",ip);               
                        assert("exist problem inputs commands");
                        response = "ERROR";                                
                        break;                
                }default:{
                        //~ debugMessage("trackercommandprocessor: the peer with ip ( %s ) send ERROR command\n",ip);
                        assert("It is shameful, we have problem ");
                        response = "ERROR";                
                        break;                
                }
        }
        return response;
}

char* processAnnouncecommand(char* ip, char* port, char* seeders, char* leeches){
	char*response;
	debugMessage("trackercommandprocessor: Add announce");
        if(1){
                strcpy(response,"202. (OK)\n");
        }else{
                strcpy(response,"304. (NO CHNAGES)\n");
        }
        
        return response;
}

char* processGetfilecommand(char* key){
	char*response;
	debugMessage("trackercommandprocessor: seek in folder");
        if(1){
                strcpy(response,"202. (OK)\n");
        }else{
                strcpy(response,"204 No Content \n");
        }      
        return response;
}

char* processLookcommand(char* chunklist){
	char*response;
	debugMessage("trackercommandprocessor: seek in folder");
        if(1){
                strcpy(response,"302. Found");
        }else{
                strcpy(response,"404 Not Found");
        }      
        return response;
}


char* processUpdatecommand(char* ip, char* seeders, char* leeches){
       char*response;
	debugMessage("trackercommandprocessor: seek in folder");
        if(1){
                strcpy(response,"410 Gone");
        }else{
                strcpy(response,"409 Conflict");
        }
        return response;
}


char* announcePort(char* string){
        char* response;
        char* tmp = strdup(string);
        char* skip =strtok(tmp," ");
        char* port =strtok (NULL," ");
        response=strdup(port);                
        return response;
}
char* announceSeeders(char* string){
        char* response;
        char* tmp = strdup(string);
        char* skip  = strtok(tmp, "["); 
        char* strSeeders = strtok(NULL,"]");
        if (strstr(strSeeders,"leech") != NULL){
                free(tmp);
                return NULL;
        }
        response = strdup(strSeeders);
        return response;                        
}
char* announceLeeches(char* string){
        char* response;
        char* tmp = strdup(string);
        char* skip  = strtok(tmp, "]"); 
        char* skip2  = strtok(NULL,"[");
        char* strLeeches = strtok(NULL,"]");
        if (strLeeches == NULL){
                free(tmp);
                return NULL;
        }
        response = strdup(strLeeches);        
        return response;        
}

char* lookElemnts(char* string){
        char* response;
        char* strRead = strdup(string);
        
        
        response = strdup(strRead);
        free(strRead);
        return response;
}

char* getfileKey(char* string){
        char* response;
        char* strRead = strdup(string);
        response = strdup(strRead);
        free(strRead);
        return response;
}

char* updateSeeders(char* string){
        char* response;
        char* tmp = strdup(string);
        char* skip  = strtok(tmp, "["); 
        char* strSeeders = strtok(NULL,"]");
        if (strstr(strSeeders,"leech") != NULL){
                free(tmp);
                return NULL;
        }
        response = strdup(strSeeders);
        return response;       
}
char* updateLeeches(char* string){
        char* response;
        char* tmp = strdup(string);
        char* skip  = strtok(tmp, "]"); 
        char* skip2  = strtok(NULL,"[");
        char* strLeeches = strtok(NULL,"]");
        if (strLeeches == NULL){
                free(tmp);
                return NULL;
        }
        response = strdup(strLeeches);        
        return response;
}
