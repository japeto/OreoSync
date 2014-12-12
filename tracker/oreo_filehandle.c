/**
 * @file oreo_filehandle.c
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and 
 * monitor a connection to oreo tracker
 * @see 
 */

#include "oreo_filehandle.h"

afile * openafile(char * a_file_path){
        afile * file= { 0 };
        file =  malloc (sizeof(afile));
        file->handle = fopen(a_file_path, "rw+");
        if (ferror(file->handle)) {
                fprintf(stderr, "Can't open input file %s !\n",a_file_path);
                exit(1);
        }
        fseek(file->handle, 0, SEEK_END);
        file->size = ftell(file->handle);       //tamaño
        rewind(file->handle);
        
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
        file->name = strdup(name); //~ strcpy(file->name, name);

        SHA1Context sha;
        SHA1Reset(&sha);
        SHA1Input(&sha, name, strlen(name));
        SHA1Result(&sha, file->nameSHA1);
          
        file->path = strdup(a_file_path);
        
        debugMessage("**********************************************************************\n");
        debugMessage("file open info. \n");
        debugMessage("**********************************************************************\n");
        int i;
        debugMessage("\nnameSHA1:");
                for (i=0; i<20; ++i){
                        debugMessage("%02X", file->nameSHA1[i]);}
                printf("\n");
        debugMessage("name : %s  \n",file->name);
        debugMessage("path: %s \n",file->path);
        debugMessage("size: %ld bytes\n",file->size);
        debugMessage("**********************************************************************\n");

        return file;        
}

afile * createafile(char *a_file_name,float a_file_size,char* a_file_path){
        afile* af = malloc(sizeof(afile));
        
        strncpy(af->name,a_file_name,256);
        strncpy(af->path,a_file_path,1024);
        
        af->size = strdup(a_file_size);;


        debugMessage("file create: ( %s ) in [ %s ]\n",a_file_name,a_file_path);
        

        return af;        
}

void freeafile(afile* a_file){
        free(a_file);
}


aChunk ** readChunks(afile * file){        
                
        if(file == NULL)
                return NULL;
        
        char path[1024] = {0};
        strcpy(path, file->path);
        //~ strcat(path, ".chunk");
        if (file->handle == NULL) {
                fprintf(stderr, "Can't open input file in.list!\n");
                exit(1);
        }
        fseek(file->handle, 0, SEEK_END);
        
        numChunks = (float)ftell(file->handle)/(float)CHUNKSIZE;
        double integer;
        double decimal = modf(numChunks, &integer);
        
        aChunk ** chunks = malloc(sizeof(aChunk) * integer);
        
        rewind(file->handle);
        //~ #ifdef OREO_DEBUG_MODE
        debugMessage("**********************************************************************\n");
        debugMessage("generating chunks from file ...\n");
        debugMessage("**********************************************************************\n");                      
        //~ #endif
        //~ integer=20;
        while(integer >= 0 ){
                
                aChunk * chunk =  malloc (sizeof (aChunk));
                if(integer>0){
                        char buff[CHUNKSIZE];
                        fread(buff,CHUNKSIZE,1,file->handle);
                        chunk->size = (int)CHUNKSIZE;
                        chunk->offset = 0;
                        offsetalive=false;
                        strcpy(chunk->data, buff);
                        strncpy(buff ,"",CHUNKSIZE);                        
                        chunk->id = (int)integer;
                        chunk->file = file;
                        sprintf(chunk->name, "%s%d.chunk",file->name,(int)integer);
                        sprintf(chunk->path, "%s%d.chunk",file->path,(int)integer);

                        SHA1Context sha;
                                SHA1Reset(&sha);
                                SHA1Input(&sha, chunk->data, strlen(chunk->data));
                                SHA1Result(&sha, chunk->dataSHA1);                         
                        //~ #ifdef OREO_DEBUG_MODE
                                debugMessage("id: %d  \n",chunk->id);
                                debugMessage("source: %s\n",chunk->file->name);
                                debugMessage("name: %s\n",chunk->name);
                                debugMessage("path: %s\n",chunk->path);
                                debugMessage("dataSHA1:");      
                                        int i;
                                        for (i=0; i<20; ++i){
                                                printf("%02X", chunk->dataSHA1[i]);}
                                        printf("\n");                        
                                debugMessage("offset: %f \n",chunk->offset);                                
                                debugMessage("size: %d \n",(int)chunk->size);                        
                                //~ printf("data: %s\n", chunk->data);
                                debugMessage("\n");
                        //~ #endif
                        chunks[(int)integer]= chunk;                                
                        
                }else if(integer==0 && decimal!=0){
                        char buff[CHUNKSIZE];
                        fread(buff,CHUNKSIZE,1,file->handle);
                        chunk->size = (int)CHUNKSIZE;
                        chunk->offset = decimal;
                        offsetalive=true;
                        strcpy(chunk->data, buff);
                        strncpy(buff ,"",CHUNKSIZE);                          
                        chunk->id = (int)integer;
                        chunk->file = file;
                        sprintf(chunk->name, "%s%d.chunk",file->name,(int)integer);
                        sprintf(chunk->path, "%s%d.chunk",file->path,(int)integer);

                        SHA1Context sha;
                                SHA1Reset(&sha);
                                SHA1Input(&sha, chunk->data, strlen(chunk->data));
                                SHA1Result(&sha, chunk->dataSHA1);                	                        
                        //~ #ifdef OREO_DEBUG_MODE
                                debugMessage("id: %d  \n",chunk->id);
                                debugMessage("source: %s\n",chunk->file->name);
                                debugMessage("name: %s\n",chunk->name);
                                debugMessage("path: %s\n",chunk->path);
                                debugMessage("dataSHA1:");      
                                        int i;
                                        for (i=0; i<20; ++i){
                                                debugMessage("%02X", chunk->dataSHA1[i]);}
                                        debugMessage("\n");                        
                                debugMessage("offset: %f \n",chunk->offset);                                
                                debugMessage("size: %d \n",(int)chunk->size);                        
                                //~ printf("data: %s\n", chunk->data);
                                debugMessage("\n");
                        //~ #endif
                        chunks[(int)integer]= chunk;                                
                }
                integer--;
        }
        #ifdef OREO_DEBUG_MODE
                printf("**************************************************************************\n");
        #endif
        
        return chunks;
}
void writeChunks(aChunk** a_chunks_list){
        double whole;
        double nwhole = modf(numChunks,&whole);
        //~ #ifdef OREO_DEBUG_MODE
                debugMessage("write oreofile by: %s \n",a_chunks_list[(int)numChunks]->file->name);
                debugMessage("in: %s with \n",a_chunks_list[(int)numChunks]->file->path);                
                debugMessage("name: %s.oreo \n",a_chunks_list[(int)numChunks]->file->path);                
                debugMessage("that contains... \n");
                debugMessage("id:\t data in SHA1\n");
        //~ #endif
        int a,b,i;
        for(a=whole;a>=0;a--){
                if(a!=0){ 
                        FILE * pFile;
                        pFile = fopen (a_chunks_list[a]->path, "wb");
                        
                        char * buffer = a_chunks_list[a]->data;                        
                        fwrite (buffer , sizeof(char), CHUNKSIZE, pFile);
                        fclose(pFile);
                        //~ #ifdef OREO_DEBUG_MODE
                                debugMessage("%d\t",a);
                                int i;
                                for (i=0; i<20; ++i){
                                        debugMessage("%02X", a_chunks_list[a]->dataSHA1[i]);}
                                debugMessage("\n");   
                        //~ #endif
                }else{
						
                        FILE * pFile;
                        pFile = fopen (a_chunks_list[a]->path, "wb");
                        char * buffer = a_chunks_list[a]->data;
                        debugMessage("len offset: %s \n",buffer);
                        fwrite (buffer , sizeof(char), strlen(buffer), pFile);
                        fclose(pFile);
                        //~ #ifdef OREO_DEBUG_MODE
                                debugMessage("%d\t",a);
                                int i;
                                for (i=0; i<20; ++i){
                                        debugMessage("%02X", a_chunks_list[a]->dataSHA1[i]);}
                                debugMessage("\n");   
                        //~ #endif                        
                }
        }
        //~ #ifdef OREO_DEBUG_MODE
                if(offsetalive)
                        debugMessage("write %d chunks of %d bytes and 1 chunk of %f bytes \n",(int)whole,CHUNKSIZE,nwhole);
                else
                        debugMessage("write %d chunks of %d bytes \n",(int)whole,CHUNKSIZE);
                debugMessage("**********************************************************************\n");                
        //~ #endif
}
double getNumChunks(){
        return numChunks;
}
void setNumChunks(double num){
        numChunks=num;
}


void folderMonitor(char * adirpath){
DIR           *d;
  struct dirent *dir;
  d = opendir(adirpath);
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      printf("%s\n", dir->d_name);
    }

    closedir(d);
  }
  return(0);   
        
}
