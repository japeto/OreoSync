/**
 * @file tracker.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing 
 *
 * @see 
 */

#include "oreo_tracker.h"

tracker* newTracker(){
        tracker* server = malloc(sizeof(tracker));
        server->peers = NULL;
        server->files = newafolder(1024); //suport 1024 files
        return server;
}
void freetracker(tracker* server){
        freeafolder(server->files);
        removeAllElements(server->peers);
}
void addFile(afile* file){
        #ifdef SHA1
        addFiletoIndex(oreoTracker->files,file->nameSHA1,(void*)file);
        #endif
        #ifdef MD5
        addFiletoIndex(oreoTracker->files,file->nameMD5,(void*)file);        
        #endif
}
void addSeederTofile(aPeer* p,char* name){
        afile* file = (afile*) getFiletoafolder(oreoTracker->files,name);
        if(! existSeeder(file->seeders,p)){
                file->seeders = addElement(file->seeders,p);
        }
}       
void updatePeers(){
        
}
int existSeeder(vector* vec,aPeer* p){
        int i;
        for(i=0;i<vec->size;i++){
                aPeer* ptemp = (aPeer*) getElementVectorIn(vec,i);
                if (strcmp(ptemp->ip, p->ip) == 0 && strcmp(ptemp->port, p->port) == 0){
                        return 1;                        
                }
        }
        return 0;
}

int main(int argc, char** argv){
        oreoTracker = newTracker();
        
        pthread_t threads[PEERCONCURRENT];
        int sockfd = socket(AF_INET, SOCK_STREAM, TCP_PROTOCOL_NUMBER);
        int status[PEERCONCURRENT];
        int idconnection=0;
        if (sockfd < 0){
                perror("oreo_tracker: ERROR opening socket");
                exit(0);
        }
        struct sockaddr_in sockaddr;
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(PORT);
        if (bind(sockfd, (struct sockaddr*) &sockaddr,sizeof(sockaddr)) < 0){
              perror("oreo_tracker");
              exit(0);
        }
        if (listen(sockfd, PEERCONCURRENT) == -1){
                perror("oreo_tracker");
                exit(0);
        }   
        int i;
        for (i=0;i<PEERCONCURRENT;i++){
                status[i] = 0;}  
        while(1){
                perror("oreo_tracker: Waiting for incoming connections...");
                if(waitApeer(sockfd,status,idconnection,threads)){
                        status[idconnection] = STATUS_CONNECTED;
                        idconnection = getNewId(status,PEERCONCURRENT);
                }
        }
}
