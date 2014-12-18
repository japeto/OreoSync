/* @file oreo_commandprocessor.c
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and monitor a connection to oreo tracker
 * @see
 */
#include "oreo_commandprocessor.h"

int RESPONSELEN = 2000;

char* process_command(aCommand* a_commmand, char* ip){
    char* response= malloc(RESPONSELEN);
        switch(a_commmand->type){
            case SEEK_COMMAND:{
                MSG("\ttrackercommandprocessor: SEEK_COMMAND\n");
                aVector* paths = seek_files(a_commmand->payload);
                response = process_seek_command(paths);
                break;
            }case SENDME_COMMAND:{
                MSG("\ttrackercommandprocessor: SENDME_COMMAND\n");
                aVector* paths = seek_chunks(a_commmand->payload);
                response = process_sendchunk_command(paths);
                break;
            }case UNKNOWN:{
                assert("exist problem inputs commands");
                response = "ERROR";
                break;
            }default:{
                assert("It is shameful, we have problem ");
                response = "ERROR";
                break;
            }
        }//end switch
    return response;
}

aVector* seek_files(char* string){
    /*nuevo vector temporal para la respuesta*/
    aVector* response = newvector(RESPONSELEN,1024); //mejorar
    /*duplico el string*/
    char* strRead = strdup(string);
    /*el primer caracter es [*/
    strRead[0]=' ';
    /*el ultimo caracter es ]*/
    strRead[strlen(strRead)-1]='\0';
    /*extraigo todos los archivos que estan separados por espacio*/
    char* token = strtok(strRead," ");
    /*bucle para extraer los nombres de los archivos*/
    while(token){
        /*ruta del archivo que contiene la lista de chunks*/
        char* path = get_filechunk_path(OreoTracker->folder,token);
        /*agrego a la respuesta la ruta de los archivos que contiene los chunks*/
        if(path != NULL)
            addElement(response,path);
        /*elimino el token que acabo de leer*/
        token = strtok (NULL, " ");
    }//end while
    /*libero la copia del payload*/
    free(strRead);
    /*retorno la respuesta*/
    return response;
}
char* process_seek_command(aVector* file_paths){
    /*un nuevo puntero vacio*/
    char*response = malloc(RESPONSELEN);
    //~ vector_toString(file_paths);
    if(file_paths->size > 0){
        /*Hay respuesta 302 es el status code
         * y seguidas con espacio estan las rutas*/
        strcpy(response,"302");
        int i;
        /*agrego las rutas de los archivos*/
        for(i=0;i<file_paths->size;i++){
            /*obtengo todas las rutas de los archivos de lista de chunks*/
            char* path = (char*)getElementVectorIn(file_paths,i);
            sprintf(response,"%s %s",response,path);
        }//end for
    }else{
        /*En caso de no encontrar*/
        strcpy(response,"304");
    }//end if
    /*retorno la respuesta*/
    return response;
}

aVector* seek_chunks(char* string){
    aVector* response = newvector(RESPONSELEN,1024);       //mejorar
    /*duplico el string*/
    char* strRead = strdup(string);
    /*el primer caracter es [*/
    strRead[0]=' ';
    /*el ultimo caracter es ]*/
    strRead[strlen(strRead)-1]='\0';
    /*extraigo todos los archivos que estan separados por espacio*/
    char* token = strtok(strRead," ");
    /* si el tracker tiene el archivo
     * busco la ruta en su lista de chunks
     */
    if(contains_file(OreoTracker->folder,token)){ //mejorar
        /*elimino el nombre del archivo del tokenizer*/
        token=strtok(NULL," ");
        while(token){
            /*ruta del chunks*/
            char* path = get_chunk_path(OreoTracker->chunklist,token);
            /*agrego a la respuesta la ruta de los archivos que contiene los chunks*/
            if(path != NULL)
                addElement(response,path);
            /*elimino el token que acabo de leer*/
            token=strtok(NULL," ");
        }
    }
    /*libero la copia del payload*/
    free(strRead);
    //~ MSG("\ttrackercommandprocessor: seek_chunks\n");
    /*retorno la respuesta*/
    return response;
}
char* process_sendchunk_command(aVector* file_paths){
    /*un nuevo puntero vacio*/
    char* response = malloc(RESPONSELEN);
    //~ vector_toString(file_paths);
    if(file_paths->size > 0){
        /*Hay respuesta 202 es el status code
         * y seguidas con espacio estan las rutas*/
        strcpy(response,"202");
        int i;
        /*agrego las rutas de los archivos*/
        for(i=0;i<file_paths->size;i++){
            char* path = (char*)getElementVectorIn(file_paths,i);
            sprintf(response,"%s %s",response,path);
        }//end for
        MSG(" response: %s\n",response);
    }else{
        /*En caso de no encontrar*/
        strcpy(response,"204");
    }//end if
    /*retorno la respuesta*/
    return response;
}
char* processAnnouncecommand(char* ip, char* port, char* seeders, char* leeches){
	char*response;
	DEBUG_MSG("trackercommandprocessor: Add announce");
        if(1){
                //~ strcpy(response,"202. (OK)\n");
        }else{
                //~ strcpy(response,"304. (NO CHNAGES)\n");
        }

        return response;
}

char* processUpdatecommand(char* ip, char* seeders, char* leeches){
       char*response;
	DEBUG_MSG("trackercommandprocessor: seek in folder");
        if(1){
                //~ strcpy(response,"410 Gone");
        }else{
                //~ strcpy(response,"409 Conflict");
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
