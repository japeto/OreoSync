/**
 * @file oreo_commandhandle.c
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and monitor a connection to oreo tracker
 * @see
 */
#include "oreo_commandhandle.h"


command* newCommand(int dataSize){
	command* c =  malloc(sizeof(command));
	c->type = UNKNOWN;
	c->data = malloc(sizeof(char) * dataSize);
	return c;
}
void deleteCommand(command* c){
	free(c->data);
	free(c);
}
int isAnnounce(command* com, char* data){
        int start = strcspn(data, " ")+1;
        int end = strlen(data);
        strncpy(com->data, data+start, end);
        debugMessage("trackercommandhandle: handle ANNOUNCE command\n");
        return 1;
}
int isLook(command* com, char* data){
        int start = strcspn(data, " ")+1;
        int end = strlen(data);
        strncpy(com->data, data+start, end);
        debugMessage("trackercommandhandle: handle LOOK command\n");
        return 1;
}
int isGetfile(command* com, char* data){
        int start = strcspn(data, " ")+1;
        int end = strlen(data);
        strncpy(com->data, data+start, end);
        //~ debugMessage("trackercommandhandle: handle GETFILE %s command\n",com->data);
        return 1;
}
int isUpdate(command* com, char* data){

        int start = strcspn(data, " ")+1;
        int end = strlen(data);
        strncpy(com->data, data+start, end);
        debugMessage("trackercommandhandle: handle UPDATE command\n");
        return 1;
}
int whatCommand(command* com, char* data){
	assert(com != NULL);
	assert(data != NULL);
	int commandSize = strcspn(data, " ");
        //~ debugMessage("trackercommandhandle:command size: %d\n", commandSize);
	char cmd[64]; 						//OJO
	if(commandSize == BUFFER_SIZE){
		com->type = UNKNOWN;
		return 0;
	}else{
                strncpy(cmd,data,commandSize);
                com->type = getCommandFromString(cmd);
                //~ debugMessage("trackercommandhandle:is known command id type ( %d ) \n",com->type);
                //~ debugMessage("trackercommandhandle:is known command type ( %s ) \n",cmd);
                return 1;
	}
}

int getCommandFromString(char* cmd){
	if (strstr(cmd,"announce") != NULL){
		//~ debugMessage("trackercommandhandle:command %s with identifier is %d\n",cmd,ANNOUNCE);
		return ANNOUNCE;
	}else if (strstr(cmd,"look") != NULL){
                //~ debugMessage("trackercommandhandle:command %s with identifier is %d\n",cmd,LOOK);
		return LOOK;
	}else if (strstr(cmd,"getfile") != NULL){
                //~ debugMessage("trackercommandhandle:command %s with identifier is %d\n",cmd,GETFILE);
		return GETFILE;
	}else if (strstr(cmd,"GET") != NULL){
                //~ debugMessage("trackercommandhandle:command %s with identifier is %d\n",cmd,GET);
		return GET;
                
	}else if (strstr(cmd,"update") != NULL){
                //~ debugMessage("trackercommandhandle:command %s with identifier is %d\n",cmd,UPDATE);
		return UPDATE;
	}else{
                //~ debugMessage("trackercommandhandle:command %s with identifier command is %d\n",cmd,UNKNOWN);
		return UNKNOWN;
	}
}
char* getCommandFromInt(int type){
	switch(type){
		case ANNOUNCE:
			//~ debugMessage("trackercommandhandle:command %d with type %s\n",ANNOUNCE,"anounce");
			return "announce";
			break;
		case LOOK:
			//~ debugMessage("trackercommandhandle:command %d with type %s\n",LOOK,"look");
			return "look";
			break;
		case GETFILE:
			//~ debugMessage("trackercommandhandle:command %d with type %s\n",GETFILE,"getfile");
			return "getfile";
			break;
		case GET:
			//~ debugMessage("trackercommandhandle:command %d with type %s\n",GET,"get");
			return "get";
			break;
		case UPDATE:
			//~ debugMessage("trackercommandhandle:command %d with type %s\n",UPDATE,"update");
			return "update";
			break;
		case UNKNOWN:
			//~ debugMessage("trackercommandhandle:command %d with type %s\n",UNKNOWN,"unknown");
			return "unknown";
			break;
		default:
			return NULL;
			break;
	}
}
