
#include "oreo_conf.h"

int main(int argc, char **argv){
        config* configstruct = get_config(FILENAME);
        /* Struct members */
        printf("%s",configstruct->alias);
        printf("%s",configstruct->home);
        printf("%d\n",configstruct->trackerport);
        printf("%d\n",configstruct->concurrent);
        printf("%d\n",configstruct->clientport);
        printf("%s",configstruct->clientneigborlist);
        printf("%s",configstruct->log);
        printf("%s",configstruct->cachefolder);
        printf("%d\n",configstruct->DEBUGMODE);
        printf("%d\n",configstruct->GUIMODE);
        printf("%d\n",configstruct->WARMSILENT);
        printf("%d\n",configstruct->LOGSILENT);
        printf("%d\n",configstruct->ERRSILENT);
                
        writeConfig(configstruct);
        return 0;
}
