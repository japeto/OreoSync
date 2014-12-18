#include "oreo_peerhandle.h"

int main(int argc, char **argv){
        aNode** nodestruct = readPeerFile(FILENAME);
        int index=0;
        /* Struct members */
        while(nodestruct[index] != NULL){
                printf("%d\t%s\t%d\n",nodestruct[index]->id,nodestruct[index]->address,nodestruct[index]->port);
                index++;
        }
        updatePeerfile(nodestruct);
        return 0;
}
