/* @file tracker.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing
 */

#include "oreo_tracker.h"

aModuleTracker* new_tracker(){
        aModuleTracker* server = malloc(sizeof(aModuleTracker));
        server->peers = NULL;                   //ojo
        server->chunklist = newchunkList();
        server->folder = newafolder(sizeof(aFolder*)*2000);
        return server;
}
void freetracker(aModuleTracker* server){
        freeafolder(server->folder);
        removeAllElements(server->peers);
}

void run_tracker(){
        pthread_t threads[CONCURRENT_PEERS];
        int sockfd = socket(AF_INET, SOCK_STREAM, TCP_PROTOCOL_NUMBER);
        int status[CONCURRENT_PEERS];
        int idconnection=0;
        /**/
        if (sockfd < 0){
                DEBUG_MSG("oreo_tracker: ERROR opening socket");
                LOG_MSG("[ERROR]\toreo_tracker: ERROR opening socket");
                ERR_MSG("oreo_tracker: ERROR opening socket");
                perror("oreo_tracker: ERROR opening socket");
                exit(0);
        }
        struct sockaddr_in sockaddr;
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(TRACKER_PORT); //set port tracker
        /**/
        if (bind(sockfd, (struct sockaddr*) &sockaddr,sizeof(sockaddr)) < 0){
                DEBUG_MSG("oreo_tracker: no accept peers\n");
                LOG_MSG("[ERROR]\toreo_tracker: no accept peers ");
                ERR_MSG("oreo_tracker: no accept peers\n");
                perror("oreo_tracker: no accept peers");
                exit(0);
        }
        /**/
        if (listen(sockfd, CONCURRENT_PEERS) == -1){
                DEBUG_MSG("oreo_tracker: no listen peers");
                LOG_MSG("oreo_tracker: no listen peers");
                ERR_MSG("oreo_tracker: no listen peers");
                perror("oreo_tracker: no listen peers");
                exit(0);
        }
        int i;
        for (i=0;i<CONCURRENT_PEERS;i++){
                status[i] = 0;
        }
        /**/
        DEBUG_MSG("oreo_tracker: Waiting for incoming connections...\n");
        LOG_MSG("[ERROR]\toreo_tracker:  Waiting for incoming connections... ");
        LOG_MSG("[ WARN ]\toreo_tracker:  Waiting for incoming connections... ");
        LOG_MSG("[ INFO ]\toreo_tracker: Waiting for incoming connections...");
        while(1){
                if(wait_peer(sockfd,status,idconnection,threads)){
                        status[idconnection] = STATE_CONNECTED;
                        idconnection = get_peer_id(status,CONCURRENT_PEERS);
                        MSG("\t ideconection : %d",idconnection);
                }
        }
}
void add_file_tracker(aFolder* a_folder,aFile* a_file){
        add_file(a_folder,a_file,a_file->simple_name);
}
void addSeederTofile(aPeer* p,char* name){
        //~ afile* file = (afile*) getFiletoafolder(oreoTracker->files,name);
        //~ if(! existSeeder(file->seeders,p)){
                //~ file->seeders = addElement(file->seeders,p);
        //~ }
}
void updatePeers(){

}
int existSeeder(aVector* vec,aPeer* p){
        int i;
        for(i=0;i<vec->size;i++){
                aPeer* ptemp = (aPeer*) getElementVectorIn(vec,i);
                if (strcmp(ptemp->ip, p->ip) == 0 && strcmp(ptemp->port, p->port) == 0){
                        return 1;
                }
        }
        return 0;
}
//~
//~ int main(int argc, char** argv){
	//~
        //~ printf(ANSI_COLOR_BLUE"\n****************************************"ANSI_COLOR_RESET"\n");
        //~ printf("OREO TRACKER RUN by JAPeTo \n");
        //~ printf(ANSI_COLOR_BLUE"****************************************"ANSI_COLOR_RESET"\n \n");
                //~
        //~ if (argc > 1) {
                //~ int i;
                //~ for(i=0;i<argc;i++){
                        //~ if(strcmp(argv[i],"--debug") ==0){
                                 //~ printf(ANSI_COLOR_RED"**DEBUG_MODE ON**"ANSI_COLOR_RESET"\n");
                                 //~ DEBUG_MODE = 1;
                        //~ }else if(strcmp(argv[i],"--log") ==0){
                                 //~ printf(ANSI_COLOR_RED"**LOG SILENT ON**"ANSI_COLOR_RESET"\n");
                                 //~ LOG_SILENT = 0;
                        //~ }else if(strcmp(argv[i],"--w") ==0){
                                 //~ printf(ANSI_COLOR_RED"**WARN SILENT ON**"ANSI_COLOR_RESET"\n");
                                 //~ WARN_SILENT = 0;
                        //~ }else if(strcmp(argv[i],"--err") ==0){
                                 //~ printf(ANSI_COLOR_RED"**ERR SILENT ON**"ANSI_COLOR_RESET"\n");
                                 //~ ERR_SILENT = 0;
                        //~ }
                //~ }
        //~ }
	//~ printf("\n");
        //~ oreoTracker = newTracker();
        //~ folderMonitor((char*) USER_HOME);
       //~
        //~ pthread_t threads[CONCURRENT_PEERS];
        //~ int sockfd = socket(AF_INET, SOCK_STREAM, TCP_PROTOCOL_NUMBER);
        //~ int status[CONCURRENT_PEERS];
        //~ int idconnection=0;
        //~ if (sockfd < 0){
                //~ DEBUG_MSG("oreo_tracker: ERROR opening socket");
                //~ LOG_MSG("oreo_tracker: ERROR opening socket");
                //~ ERR_MSG("oreo_tracker: ERROR opening socket");
                //~ perror("oreo_tracker: ERROR opening socket");
                //~ exit(0);
        //~ }
        //~ struct sockaddr_in sockaddr;
        //~ sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        //~ sockaddr.sin_family = AF_INET;
        //~ sockaddr.sin_port = htons(DEFAULT_PORT);
        //~ if (bind(sockfd, (struct sockaddr*) &sockaddr,sizeof(sockaddr)) < 0){
              //~ DEBUG_MSG("oreo_tracker: no accept peers ");
              //~ LOG_MSG("oreo_tracker: no accept peers ");
              //~ ERR_MSG("oreo_tracker: no accept peers ");
              //~ perror("oreo_tracker: no accept peers ");
              //~ exit(0);
        //~ }
        //~ if (listen(sockfd, CONCURRENT_PEERS) == -1){
                //~ DEBUG_MSG("oreo_tracker: no listen peers");
                //~ LOG_MSG("oreo_tracker: no listen peers");
                //~ ERR_MSG("oreo_tracker: no listen peers");
                //~ perror("oreo_tracker: no listen peers");
                //~ exit(0);
        //~ }
        //~ int i;
        //~ for (i=0;i<CONCURRENT_PEERS;i++){
                //~ status[i] = 0;
        //~ }
        //~ while(1){
                //~
                //~ DEBUG_MSG("oreo_tracker: Waiting for incoming connections...\n");
                //~ LOG_MSG("oreo_tracker: Waiting for incoming connections...\n");
                //~ if(wait_peer(sockfd,status,idconnection,threads)){
                        //~ status[idconnection] = STATE_CONNECTED;
                        //~ idconnection = getNewId(status,CONCURRENT_PEERS);
                //~ }
        //~ }
//~ }
