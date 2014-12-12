/**
 * @file oreo_tracker_sockethandled.c
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and monitor a connection to oreo tracker
 * @see 
 */
#include "oreo_sockethandle.h"

int getNewId(int * connectionState, int size){
	int index = 0;
        for (index=0;index<size;index++){
                //~ debugMessage("trackersockethandle:id val (%d)\n",connectionState[index]);
                if(connectionState[index] == 0) {
                        //~ debugMessage("trackersockethandle: next connection with id (%d)\n",index);
                        return index;	/*wheter a slot in vector conecctionState is 0 stored new peer in index*/
                }
        }
        debugMessage("trackersockethandle: has reached the limit, tracker full");
	return -1;	/*return -1 no more ids*/
}

command* waitCommands(dataPeer* peerconnection){
	
	assert(peerconnection != NULL);
	command* com = newCommand(BUFFER_SIZE); 
	char buffer[BUFFER_SIZE];
	char tempBuffer[BUFFER_SIZE];
	int sizeRead = 0;
	int (*checkFunction) (command*, char*);
	do{
		sizeRead = read(peerconnection->socketFd, tempBuffer, BUFFER_SIZE);
                strncat(buffer,tempBuffer,sizeRead);
	}while(!whatCommand(com,buffer));
	switch(com->type){
                case ANNOUNCE:        
                        checkFunction = isAnnounce;
                        break;
                case LOOK:
                        checkFunction = isLook;
                        break;
                case GETFILE:
                        checkFunction = isGetfile;
                        break;
                case UPDATE:
                        checkFunction = isUpdate;
                        break;
                case UNKNOWN:
                        free(com);
                        return NULL;
                break;                
	}       
	int dataComplete = 0;
	dataComplete = checkFunction(com,buffer);
	while(!dataComplete){
                sizeRead = read(peerconnection->socketFd, tempBuffer, BUFFER_SIZE);
                strncat(buffer,tempBuffer,sizeRead);
                dataComplete = checkFunction(com,buffer);
	}
        if (dataComplete == 2){
                perror("trackersockethandle: bad message,issue in make message");
                free(com);
                return NULL;
        }else{
                //~ debugMessage("trackersockethandle: command from peer is (%s)\n",getCommandFromInt(com->type));
                return com;
        }
}

int waitApeer(int socket, int* stateConnection, int identifier ,pthread_t* threads){
	
	struct sockaddr_in* peerIn = malloc(sizeof(struct sockaddr_in)); /*pointer new */
	int peerlength = sizeof(struct sockaddr_in); /*pointer new*/
	int peersocketFd;
	peersocketFd = accept(socket, (struct sockaddr*) peerIn, &peerlength);
	if (socket == -1){
		perror("trackersockethandle: not accept()");
		return 0;
	}
        debugMessage("trackersockethandle: new peer incoming\n");
	dataPeer* connection = malloc(sizeof(dataPeer));/*pointer new*/  
	//set attributes by a new peer
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(peerIn->sin_addr), str, INET_ADDRSTRLEN);
	connection->socketFd = peersocketFd;
	connection->infoConnection = peerIn;
	connection->idConnection = identifier;
	connection->stateConnection = stateConnection;
        //~ debugMessage("trackersockethandle:new peer with ID:(%d) IP:(%s) PORT:(%d)\n",identifier,str,peerIn->sin_port);
	// new thread by a new peer
	if(pthread_create(&threads[identifier], NULL, (void*) peerExchangeCommands , (void*) connection)){
                perror("Error creating thread\n");
                return 1;
        }
	
	return 1;	
}


void peerExchangeCommands(void* dataconnection){
	dataPeer* connection = (dataPeer*) dataconnection;
        //~ debugMessage("trackersockethandle: new connection incoming with id ( %d ) \n",connection->idConnection);
        
                char* welcome = "WELCOME OREO P2P TRACKER\n COMMANDS: \n \tANNOUNCE\n \tLOOK\n \tGETFILE\n \tUPDATE\n";
                write(connection->socketFd, welcome, strlen(welcome));                        
                
	command* com;
		com = waitCommands(connection);
	if (com != NULL){
                //~ debugMessage("trackersockethandle: processing command with type: %d and data: %s\n",com->type,com->data);
		/*obtain ip from client*/
		char* ip = strdup((char*)inet_ntoa(connection->infoConnection->sin_addr));
		/*make response*/
		char* response = (char*)processCommand(com,ip);  
		/*write message to client*/
                //~ debugMessage(">> %s",response);
		write(connection->socketFd, response, strlen(response));
		// free resources
		free(com);
		free(response);
		// shut down part of a full-duplex connection
		shutdown(connection->socketFd,SHUT_RDWR);
		// free server listener array
		connection->stateConnection[connection->idConnection] = STATUS_DISCONNECTED; 
    }else{
		/*timeout or incorrect message*/
		char* response = strdup("400. Bad Request");
		/*write message to client*/
		write(connection->socketFd, response, strlen(response));
		// free resources
		free(response);
		// shut down part of a full-duplex connection
		shutdown(connection->socketFd,SHUT_RDWR);
		// free server listener array
		connection->stateConnection[connection->idConnection] = STATUS_DISCONNECTED; 
    }	
}
