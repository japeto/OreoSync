/*
 * oreo_datastructure.c
 *
 * Copyright 2014 Jefferson Amado Peña <jeffersonamado@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */
/* @file oreo_datastructure.c
 * @author Jefferson Amado Pe&ntilde;a Torres,(jeffersonamado@gmail.com),JAPeTo
 * @date 21 Nov 2014
 * @brief
 * @see
 */
#include <stdio.h>
#include <stdlib.h>

#include "oreo_datastructure.h"


//########################################################
//	Peer
//########################################################
aPeer* newaPeer(char* ip, char* port){
	aPeer* p= malloc(sizeof(aPeer));
	p->name= strdup("anonymous");
	p->ip= strndup(ip,16);
	p->port= strndup(port,8);
	p->status=STATE_CONNECTED;
	return p;
}
aPeer* createPeer(char* alias,char* ip, char* port,int status){
	aPeer* p= malloc(sizeof(aPeer));
        p->name= strdup(alias);
	p->ip= strndup(ip,16);
	p->port= strndup(port,8);
	p->status=status;
	return p;
}
void freePeer(aPeer* p){
    WARN_MSG("free a aPeer");
	free(p);
}
aPeer* getPeerByIp(aVector* a_vector ,char* ip){
	int i;
	for(i=0;i < a_vector->size;i++){
                aPeer* a_peer = ((aPeer*) a_vector->data[i]);
		if(strcmp(a_peer->ip,ip) != 0){
			return a_peer;
		}
	}
	return NULL;
}
aPeer* getPeerByName(aVector* a_vector,char* name){
	int i;
	for(i=0;i < a_vector->size;i++){
		aPeer* a_peer = ((aPeer*) a_vector->data[i]);
		if(strcmp(a_peer->name,name) != 0){
			return a_peer;
		}
	}
	return NULL;
}
void addPeer(aVector* a_vector,aPeer* a_peer){
    a_vector = addElement(a_vector, (void*)a_peer);
}
//########################################################
//	Vector
//########################################################

aVector* newvector(int element_size, int initial_max){
    aVector* a_vector = (aVector*) malloc(sizeof(aVector*));
    a_vector->capacity = initial_max;
    a_vector->size = 0;
    a_vector->data = malloc(sizeof(void *) * a_vector->capacity);
    return a_vector;
}

void freeVector(aVector* a_vector){
    WARN_MSG("free a aVector");
	free(a_vector->data);
	free(a_vector);
}
void removeAllElements(aVector *a_vector){
	int i;
	for(i=0;i < a_vector->capacity ;i++){
		a_vector->data[i] = NULL;
	}
    a_vector->size=0;
}
void vector_toString(aVector* a_vector){
    assert(a_vector != NULL);
	int i;
	for(i=0;i < a_vector->size ;i++){
		if(a_vector->data[i] != NULL)
                printf("\tindex: %s%d%s value: %s%s%s \n",ANSI_COLOR_YELLOW,i,ANSI_COLOR_RESET,ANSI_COLOR_GREEN,(char*)a_vector->data[i],ANSI_COLOR_RESET);
	}
}
aVector* addElement(aVector* a_vector,void* element){
    if (a_vector->capacity == a_vector->size)
        vector_resize(a_vector, a_vector->capacity * 2);
    a_vector->data[a_vector->size++] = element;
}
void vector_resize(aVector* a_vector, int capacity){
    WARN_MSG("vector_resize");
    void **data = realloc(a_vector->data, sizeof(void *) * capacity);
    if (data) {
        a_vector->data = data;
        a_vector->capacity = capacity;
    }
}

aVector* addElementIn(aVector* a_vector,int position,void* element){
    if (position >= 0 && position < a_vector->size){
            a_vector->data[position] = element;
    }else if (position >= a_vector->size && position < a_vector->capacity){
            a_vector->data[position] = element;
            a_vector->size=position;
    }
    return a_vector;
}
aVector* removeElement(aVector* a_vector){
	a_vector->data[a_vector->size-1] = NULL;
        a_vector->size--;
	return a_vector;
}
aVector* removeElementIn(aVector* a_vector,int position){
    if (position < 0 || position >= a_vector->size)
            return NULL;

    a_vector->data[position] = NULL;
    int i;
    for (i = 0; i < a_vector->size - 1; i++) {
            a_vector->data[i] = a_vector->data[i + 1];
            a_vector->data[i + 1] = NULL;
    }
    a_vector->size--;
    if (a_vector->size > 0 && a_vector->size == a_vector->capacity / 4)
            vector_resize(a_vector, a_vector->capacity / 2);

    return a_vector;
}

void* getElementVector(aVector* a_vector){
	return a_vector->data[a_vector->size-1];
}

void* getElementVectorIn(aVector* a_vector,int position){
	if (position >= 0 && position < a_vector->size){
                return a_vector->data[position];
	}
    return NULL;
}
int contains(aVector* a_vector,void* element){
    int i;
	for(i=0;i < a_vector->size;i++){
		if(strcmp(a_vector->data[i],element) != 0){
			return 0;
		}
	}
	return 1;
}
//########################################################
//	aFolder
//########################################################
aFolder* newafolder(int element_size){
    aFolder* a_folder = malloc(sizeof(aFolder));
    a_folder->files = malloc(sizeof(aFile*)*element_size);
    a_folder->namefile = malloc(sizeof(char*)*element_size);
    a_folder->size=0;
    a_folder->elements=element_size;
    return a_folder;
}
void freeafolder(aFolder* a_folder){
    WARN_MSG("free a folder");
    assert(a_folder != NULL && "folder: Cannot free null folder");
    int i;
    for(i=0;i<a_folder->size;i++){
            free(a_folder->namefile[i]);
    }
    free(a_folder->namefile);
    free(a_folder);
}
void add_file(aFolder* a_folder,aFile* a_file,char* a_filename){
    assert(a_folder != NULL);                      ///Que no sea un objeto nulo
    assert(a_file != NULL);                        ///Que no sea un objeto nulo
    assert(a_filename != NULL);                      ///Que no sea un objeto nulo
    assert(a_folder->size+1 < a_folder->elements+1); ///Si voy a añadir espero que halla espacio

    a_folder->files[a_folder->size] = a_file;      ///añado el nuevo archivo
    a_folder->namefile[a_folder->size] = strdup(a_filename); ///añado el nombre para agilizar busquedas
    a_folder->size++;
}
char* get_filechunk_path(aFolder* a_folder,char* a_filename){
    assert(a_folder != NULL);
    assert(a_filename != NULL);
    int i;
    /*busco el nombre y en ese indice retorno la ruta del archivo de chunks*/
    for (i=0;i<a_folder->size ;i++){
        if (strcmp(a_filename,a_folder->namefile[i]) == 0)
            return a_folder->files[i]->chunks_path;
    }
    return NULL;
}
int get_id_file(aFolder* a_folder,char* a_filename){
    assert(a_folder != NULL);
    assert(a_filename != NULL);
    int i;
    for (i=0;i < a_folder->size ;i++){
        if (strcmp(a_filename,a_folder->namefile[i]) == 0){
            MSG("  >> %d << \n",i);
            return i;
        }
    }
    return -1;
}
int contains_file(aFolder* a_folder,char* a_filename){
    assert(a_folder != NULL);
    assert(a_filename != NULL);
    int i;
    for (i=0;i<a_folder->size;i++){
        if (strcmp(a_filename,a_folder->namefile[i]) == 0)
                return 1;
    }
    return 0;
}

void folder_tostring(aFolder* a_folder){
    assert(a_folder != NULL); ///si es diferente de null se imprime
    DEBUG_MSG("FOLDER STRING\n");
    int i;
    for (i=0;i<a_folder->size;i++){
        file_toString(a_folder->files[i]);
        MSG("\t id %d x name in folder: %s%s%s \n",i,ANSI_COLOR_RED,a_folder->namefile[i],ANSI_COLOR_RESET);
        MSG("\n");
    }
    MSG("\t x folder size: %s%d%s \n",ANSI_COLOR_RED,a_folder->size,ANSI_COLOR_RESET);
    MSG("\t x folder capacity: %s%d%s \n",ANSI_COLOR_RED,a_folder->elements,ANSI_COLOR_RESET);
}

//########################################################
//	afile
//########################################################

aFile * open_afile(char * a_file_path){
    /*un nuevo archivo vacio*/
    aFile * file= { 0 };
    file =  malloc (sizeof(aFile));
    /*descriptor para el archivo*/
    file->file_handle = fopen(a_file_path, "rw+");
    if (ferror(file->file_handle)){
        DEBUG_MSG("oreo_filehandle: Can't open input file %s in OreoSync folder\n");
        LOG_MSG("[ERROR]\toreo_filehandle: could not open file %s in OreoSync folder",a_file_path);
        ERR_MSG("oreo_filehandle: Can't open %s file in OreoSync folder!\n",a_file_path);
        fprintf(stderr, "Can't open input file %s in OreoSync folder!\n",a_file_path);
    }
    /*status del archivo para saber el tamnio*/
    struct stat st;
    stat(a_file_path, &st);
    file->file_size = st.st_size;       //tamaño
    //~ fseek(file->file_handle, 0, SEEK_END);
    //~ file->file_size = ftell(file->file_handle);       //tamaño
    //~ rewind(file->file_handle);
    /*remuevo la ruta completa y obtengo solo el nombre*/
    char * name= (char *)malloc(strlen(a_file_path) + 1);
    name = strdup(a_file_path);//~ strcpy(name, a_file_path);
    char *ssc;
    int l = 0;
    ssc = strstr(name, "/");
    do{
        l = strlen(ssc) + 1;
        name = &name[strlen(name)-l+2];
        ssc = strstr(name, "/");
    }while(ssc);
    file->simple_name = strdup(name);
    //~ strcpy(file->simple_name, simple_name);

    /*metodos de encripcion solo el nombre*/
    SHA1Context sha;
    SHA1Reset(&sha);
    SHA1Input(&sha, name, strlen(name));
    SHA1Result(&sha, file->name_sha);

    MD5_CTX mdContext;
    MD5Init (&mdContext);
    MD5Update (&mdContext, name, strlen (name));
    MD5Final (&mdContext);
    file->name_md5 = strdup(mdContext.digest);
    /*ruta completa del archivo*/
    file->dir_path = strdup(a_file_path);
    stat(a_file_path,&file->file_stat);   //status file in system
    //~ file->vec_seeders = newVector(sizeof(aPeer),5);

    DEBUG_MSG("**********************************************************************\n");
    //~ LOG_MSG("[INFO]\topenfile: load file [%s] in  oreo folder",name);
    int i;
    //~ char* debugmsg[20];
    DEBUG_MSG("name : %s%s  \n",ANSI_COLOR_RESET,file->simple_name);
    DEBUG_MSG("path: %s%s \n",ANSI_COLOR_RESET,file->dir_path);
    DEBUG_MSG("nameSHA1: ");
    for (i=0; i<20; ++i){
        MSG("%s%02x",ANSI_COLOR_RESET,file->name_sha[i]);
    }
    MSG("\n");
    DEBUG_MSG("nameMD5: ");
    for (i=0; i<16; ++i){
        MSG("%s%02x",ANSI_COLOR_RESET,mdContext.digest[i]);
    }
    MSG("\n");
    DEBUG_MSG("size: %s%ld%s bytes\n",ANSI_COLOR_RESET,file->file_size,ANSI_COLOR_YELLOW);
    /*creo el archivo de rutas*/
    file->chunks_path=create_chunk_list(file);    ///esta aqui por los mensajes
    DEBUG_MSG("chunk path: %s\n",file->chunks_path);

    //~ DEBUG_MSG("**********************************************************************\n");
    return file;
}
char* create_chunk_list(aFile* a_file){
    char* response=malloc(512);
    /*creo la ruta definitiva del chunk*/
    char chunkpath[strlen(USER_HOME)+strlen(a_file->simple_name)];
    sprintf(chunkpath, "%s/.oreo/%s.ocl",USER_HOME,a_file->simple_name);
    response = strdup(chunkpath);
    /*verifico si el archivo ya esxiste*/
    if( access( chunkpath, F_OK ) != -1 ){
        DEBUG_MSG("oreo_filehandle: list chunk by [%s%s%s] ready  \n",ANSI_COLOR_RESET,a_file->simple_name,ANSI_COLOR_YELLOW);
        long part=0;
        while (1) {
            long ndata;
            char* buffer = malloc((unsigned) CHUNKSIZE);
            /*read data of length CUNKSIZE*/
            ndata = fread(buffer, 1, (int) CHUNKSIZE, a_file->file_handle);
            /**/
            char md5[33] = {0};
            if (ndata > 0) {
                /*mak key from data*/
                MD5_CTX mdContext;
                MD5Init (&mdContext);
                MD5Update (&mdContext, buffer, strlen(buffer));
                MD5Final (&mdContext);
                int i;
                /*transform digest to string format*/
                for (i=0; i<16; ++i){
                    sprintf(&md5[i*2], "%02x", (unsigned int)mdContext.digest[i]);
                }
            } else { //stop condition
                break;
            }
            /*creo las keys locales de los archivos y los guardo en el tracker*/
            char* chunk=malloc(128);
            /*creo un chunk vacio*/
            aChunk* a_chunk= newchunk();
                /*creo la clave para los datos*/
                strcpy(a_chunk->key,md5);
                sprintf(chunk,"%s/.oreo/temp/%s.%03ld",USER_HOME,a_file->simple_name,++part);
                /*establezco la ruta del chunk*/
                a_chunk->path=strdup(chunk);
                //~ chunk_toString(a_chunk);
                /*agrego este chunk al tracker*/
                add_chunk(OreoTracker->chunklist,a_chunk);
        }// End while
    }else{
        MSG("\tcratechunklist: file chunk list by [%s%s%s] no found \n",ANSI_COLOR_GREEN,a_file->simple_name,ANSI_COLOR_RESET);
        MSG("\tcratechunklist: file chunk list name [%s%s.ocl%s] in %s/.oreo folder\n",ANSI_COLOR_GREEN,a_file->simple_name,ANSI_COLOR_RESET,USER_HOME);
        FILE * filechunklist;
        char* buffer = malloc((unsigned) CHUNKSIZE);
        long part=0;
        //~ char splitfn[280];
        /*open file*/
        filechunklist = fopen (chunkpath, "w+");
        /*add header data to chunk*/
        fprintf(filechunklist,"File: %s\n",a_file->simple_name);
        //~ fprintf(filechunklist,"Size: %s\n",a_file->file_size);
        fprintf(filechunklist,"Chunks:\n");
        while (1) {
            long ndata;
            /*read data of length CUNKSIZE*/
            ndata = fread(buffer, 1, (int) CHUNKSIZE, a_file->file_handle);
            /**/
            char md5[33] = {0};
            if (ndata > 0) {
                /*mak key from data*/
                MD5_CTX mdContext;
                MD5Init (&mdContext);
                MD5Update (&mdContext, buffer, strlen(buffer));
                MD5Final (&mdContext);
                int i;
                /*transform digest to string format*/
                for (i=0; i<16; ++i){
                    sprintf(&md5[i*2], "%02x", (unsigned int)mdContext.digest[i]);
                }
            } else { //stop condition
                break;
            }
            //~ /*add data to file chunk list  -- id key */
            fprintf(filechunklist,"%d \t %s\n",++part,md5);
            char* chunk=malloc(128);
            aChunk* a_chunk= newchunk();
                strcpy(a_chunk->key,md5);
                sprintf(chunk,"%s/.oreo/temp/%s.%03ld",USER_HOME,a_file->simple_name,part);
                a_chunk->path=strdup(chunk);
                //~ chunk_toString(a_chunk);
                /*agrego este chuk al tracker*/
                add_chunk(OreoTracker->chunklist,a_chunk);
        }// End while
        /*close file descriptor*/
        fclose(filechunklist);
        //~ MSG("\tcratechunklist:Create finishing by file chunk list by [%s]\n",a_file->simple_name);
    }//End else
    /*retorno la respuesta*/
    return response;
}

aFile * newafile(char *a_file_name,long a_file_size,char* a_file_path){
        /*nuevo archivo*/
        aFile* a_file = malloc(sizeof(aFile));
        /*nombre de 256 caracteres*/
        strncpy(a_file->simple_name,a_file_name,256);
        /*ruta de 1024 caracteres*/
        strncpy(a_file->dir_path,a_file_path,1024);
        /*establezco el tamanio*/
        a_file->file_size = a_file_size;
        /*chunks de este archivo*/
        //~ a_file->chunks = malloc(sizeof(char*)*3000);
        /*retorno un nuevo archivo*/
        return a_file;
}
void freeafile(aFile* a_file){
        free(a_file);
}
void file_toString(aFile* a_file){
        //~ MSG("**********************************************************************\n");
        int i;
        MSG("\t x name : %s%s  \n",ANSI_COLOR_RESET,a_file->simple_name);
        MSG("\t x path: %s%s \n",ANSI_COLOR_RESET,a_file->dir_path);
        MSG("\t x nameSHA1: ");
        for (i=0; i<20; ++i){
                MSG("%s%02x",ANSI_COLOR_RESET,a_file->name_sha[i]);
        }
        MSG("\n");
        MSG("\t x nameMD5: ");
        for (i=0; i<16; ++i){
                MSG("%s%02x",ANSI_COLOR_RESET,a_file->name_md5[i]);
        }
        MSG("\n");
        MSG("\t x size: %s%ld%s bytes\n",ANSI_COLOR_RESET,a_file->file_size,ANSI_COLOR_RESET);
        MSG("\t x chunk path: %s\n",a_file->chunks_path);
        //~ MSG("**********************************************************************\n");
}
//########################################################
//	aChunk
//########################################################

aChunk* newchunk(){
    aChunk* a_chunk = malloc(sizeof(aChunk*));
    a_chunk->key=malloc(20);
    a_chunk->path=malloc(512);
    return  a_chunk;
}
void chunk_toString(aChunk* a_chunk){
    MSG("\t key: %s \n",a_chunk->key);
    MSG("\t path: %s \n",a_chunk->path);
}
aChunkList* newchunkList(){
    aChunkList* a_chunklist = malloc(sizeof(aChunkList*)*1024);
    a_chunklist->key= malloc(sizeof(char*)*1024);
    a_chunklist->chunks= malloc(sizeof(aChunk*)*1024);
    a_chunklist->elements=0;
    return a_chunklist;
}
void add_chunk(aChunkList* a_chunklist,aChunk* a_chunk){
    assert(a_chunklist != NULL);
    assert(a_chunk != NULL);
    a_chunklist->key[a_chunklist->elements] =strdup(a_chunk->key);
    a_chunklist->chunks[a_chunklist->elements]= a_chunk;
    //~ MSG("%s@>> %d , %s , %s %s\n",ANSI_COLOR_CYAN,OreoTracker->chunklist->elements,OreoTracker->chunklist->chunks[OreoTracker->chunklist->elements]->key,OreoTracker->chunklist->chunks[OreoTracker->chunklist->elements]->path,ANSI_COLOR_RESET);
    a_chunklist->elements++;
}
char* get_chunk_path(aChunkList* a_chunklist,char* key){
    assert(a_chunklist != NULL);
    assert(key != NULL);
    int i;
    for(i=0; i < a_chunklist->elements;i++){
        if(strcmp(a_chunklist->key[i],key)==0){
            //~ MSG("@>> %s %s == %s -> %s %s\n",ANSI_COLOR_CYAN,OreoTracker->chunklist->key[i],key,a_chunklist->chunks[i]->path,ANSI_COLOR_RESET);
            return a_chunklist->chunks[i]->path;
        }
    }
}
void chunklist_toString(aChunkList* a_chunklist){
    int i;
    for(i=0;i < a_chunklist-> elements ;i++){
        chunk_toString(a_chunklist->chunks[i]);
        fprintf(stderr,"\tkey %s\n",a_chunklist->key[i]);
    }
    fprintf(stderr,"\telements %d\n",a_chunklist->elements);
}

