
#include "oreo_functions.h"

aNode* newPeer(){
       aNode* peer = malloc(sizeof(aNode));
       peer->address=malloc(32);
       peer->port = malloc(16);
       return peer; 
}
void freeclientPeer(aNode* peer){
        free(peer);
}
aNode* parsePeer(char* address, char* cport){
        aNode* peer = newPeer();
        char * end;
        long int port = strtol(cport, &end, 10 ); //Base 10
        if ( port <= 1024 || port > 65535){
                error("Port number out of range. Port must be between 1024 and 65535");
                freeclientPeer(peer);
                return NULL;
        }else if(strcmp(address,"127.0.0.1")!=0){
                peer->address = strdup(address);
        }else{
                peer->port = port;
                return peer;
        }
}

void peertoString(aNode* peer){
    printf("PEER ADDRESS: %s\nPEER PORT: %d\n\n", peer->address, peer->port); 
}
