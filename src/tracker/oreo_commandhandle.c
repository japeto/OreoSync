/* @file oreo_commandhandle.c
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and monitor a connection to oreo tracker
 * @see
 */
#include "oreo_commandhandle.h"


aCommand* newCommand(int dataSize){
	aCommand* a_command =  malloc(sizeof(aCommand));
	a_command->type = UNKNOWN;
	a_command->payload = malloc(sizeof(char) * dataSize);
	return a_command;
}
void deleteCommand(aCommand* a_command){
	free(a_command->payload);
	free(a_command);
}

int isSeek(aCommand* a_command, char* payload){
    int start = strcspn(payload, " ")+1;
    int end = strlen(payload);
    int response = strlen(strncpy(a_command->payload, payload+start, end));
    return response;
}
int isSendme(aCommand* a_command, char* payload){
        int start = strcspn(payload, " ")+1;
        int end = strlen(payload);
        int response = strlen(strncpy(a_command->payload, payload+start, end));
        return response;
}

//~ ################

int isGetfile(aCommand* a_command, char* payload){
        MSG("\tcommandhandle: handle %s%s%s coomand \n",ANSI_COLOR_BLUE,a_command->type,ANSI_COLOR_RESET);
        int start = strcspn(payload, " ")+1;
        int end = strlen(payload);
        int response = strlen(strncpy(a_command->payload, payload+start, end));
        return response;
}
int isUpdate(aCommand* a_command, char* payload){
        MSG("\tcommandhandle: handle %s%s%s coomand \n",ANSI_COLOR_BLUE,a_command->type,ANSI_COLOR_RESET);
        int start = strcspn(payload, " ")+1;
        int end = strlen(payload);
        int response = strlen(strncpy(a_command->payload, payload+start, end));
        return response;
}
int isAnnounce(aCommand* a_command, char* payload){
        MSG("\tcommandhandle: handle %s%s%s coomand \n",ANSI_COLOR_BLUE,a_command->type,ANSI_COLOR_RESET);
        int start = strcspn(payload, " ")+1;
        int end = strlen(payload);
        int response = strlen(strncpy(a_command->payload, payload+start, end));
        return response;
}
int what_command(aCommand* a_command, char* payload){
    assert(a_command != NULL);
    assert(payload != NULL);
    int commandSize = strcspn(payload, " ");
    if(commandSize == BUFFER_SIZE){
	a_command->type = UNKNOWN;
	return 0;
    }else{
	strncpy(a_command,payload,commandSize);
	a_command->type = command_from_string(a_command);
	return 1;
    }
}

int command_from_string(char* command){
	if (strstr(command,"SEEK") != NULL){
		return SEEK_COMMAND;

	}else if (strstr(command,"SENDME") != NULL){
		return SENDME_COMMAND;
	//~ }else if (strstr(command,"getfile") != NULL){
                //~ DEBUG_MSG("trackercommandhandle:command %s with identifier is %d\n",command,GETFILE);
		//~ return GETFILE;
	//~ }else if (strstr(command,"GET") != NULL){
                //~ DEBUG_MSG("trackercommandhandle:command %s with identifier is %d\n",command,GET);
		//~ return GET;
	//~ }else if (strstr(command,"update") != NULL){
                //~ DEBUG_MSG("trackercommandhandle:command %s with identifier is %d\n",command,UPDATE);
		//~ return UPDATE;
	}else{
                DEBUG_MSG("trackercommandhandle:command %s with identifier command is %d\n",command,UNKNOWN);
		return UNKNOWN;
	}
}
char* command_from_int(int type){
	switch(type){
		case SEEK_COMMAND:
			return "SEEK";
			break;
		case SENDME_COMMAND:
			return "SENDME";
			break;
		//~ case GETFILE:
			//~ DEBUG_MSG("trackercommandhandle:command %d with type %s\n",GETFILE,"getfile");
			//~ return "getfile";
			//~ break;
		//~ case GET:
			//~ DEBUG_MSG("trackercommandhandle:command %d with type %s\n",GET,"get");
			//~ return "get";
			//~ break;
		//~ case UPDATE:
			//~ DEBUG_MSG("trackercommandhandle:command %d with type %s\n",UPDATE,"update");
			//~ return "update";
			//~ break;
		case UNKNOWN:
			DEBUG_MSG("trackercommandhandle:command %d with type %s\n",UNKNOWN,"unknown");
			return "unknown";
			break;
		default:
			return NULL;
			break;
	}
}
