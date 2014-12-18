
#include "oreo_peerhandle.h"

aNode * node_parser(char * filename){
        aNode** m_node = malloc(MAXPEERS);  //ojo mejorar
        FILE *file = fopen (filename, "r");
        if (file != NULL){
                char line[MAXBUF];
                int nnodes=0;
                while(fgets(line, sizeof(line), file) != NULL){
                        if (line[0] == '[') continue;           //skip
                        if (line[0] == '\n') continue;          //skip
                        if (line[0] == ' ') continue;           //skip
                        char *token;
                        aNode* a_node = malloc(sizeof(aNode*));
                        /* get the first token */
                        char *ch;
                        ch = strtok(line, " ");
                        int i=0;
                        /*get id, ip and port*/
                        while (ch != NULL && strcmp(ch,"\n")!=0) {
                                printf("%d %d %s\n",nnodes,i,ch);
                                if(i==0){       //get id
                                        a_node->id=atoi(ch);
                                }else if(i==1){ //get ip
                                        a_node->address=strdup(ch);
                                }else if(i==2){ //get port
                                        a_node->port=atoi(ch);
                                }
                                i++;
                                ch = strtok(NULL, " ");                        
                        }
                        m_node[nnodes]=a_node;
                        nnodes++;
                }// End while
        }else{
                //~ printf("DATA: ERROR READ");
        }
        return m_node;
}

int peer_update(aNode** m_node){
        FILE * fnode;
        fnode = fopen(PEERPATH, "w");    
        int index=0;
        while(m_node[index] != NULL){
                fprintf(fnode,"%d\t%s\t%d\n",m_node[index]->id,
                                m_node[index]->address,m_node[index]->port);
                index++;
        }
        fclose(fnode);
}
