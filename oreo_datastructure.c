/**
 * @file oreo_datastructure.c
 * @author JAPETO - jeffersonamado@gmail.com
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
	p->status=STATUS_CONNECTED;
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
	free(p);
}
aPeer* getPeerByIp(vector* vec ,char* ip){
	int i;
	for(i=0;i < vec->size;i++){
                aPeer* p = ((aPeer*) vec->data[i]);
		if(strcmp(p->ip,ip) != 0){
			return p;
		}
	}
	return NULL;
}
aPeer* getPeerByName(vector* vec,char* name){
	int i;
	for(i=0;i < vec->size;i++){
		aPeer* p = ((aPeer*) vec->data[i]);
		if(strcmp(p->name,name) != 0){
			return p;
		}
	}
	return NULL;
}
void addPeer(vector* vec,aPeer* p){
		vec = addElement(vec, (void*)p);
}
//########################################################
//	Vector 
//########################################################

vector* newVector(int element_size, int initial_max){
	vector* vec = (vector*) malloc(sizeof(vector*));
	vec->capacity = initial_max;
    vec->size = 0;
    vec->data = malloc(sizeof(void *) * vec->capacity);
    return vec;
}
void freeVector(vector *vec){
	free(vec->data);
	free(vec);
}
void removeAllElements(vector *vec){
	int i;
	for(i=0;i < vec->capacity ;i++){
		vec->data[i] = NULL;
	}
        vec->size=0;
}
void printv(vector *vec){
	int i;
	for(i=0;i < vec->size;i++){
		if(vec->data[i] != NULL)
                printf("index: %d value: %s \n",i,(char*)vec->data[i]);
	}
}
vector* addElement(vector* vec,void* element){
    if (vec->capacity == vec->size)
        vector_resize(vec, vec->capacity * 2);
    vec->data[vec->size++] = element;	
}
void vector_resize(vector *vec, int capacity){
    void **data = realloc(vec->data, sizeof(void *) * capacity);
    if (data) {
        vec->data = data;
        vec->capacity = capacity;
    }
}

vector* addElementIn(vector* vec,int position,void* element){
        if (position >= 0 && position < vec->size){
                vec->data[position] = element;
        }else if (position >= vec->size && position < vec->capacity){
                vec->data[position] = element;
                vec->size=position;
        }
        return vec;
}
vector* removeElement(vector* vec){
	vec->data[vec->size-1] = NULL;
        vec->size--;
	return vec;
}
vector* removeElementIn(vector* vec,int position){
	if (position < 0 || position >= vec->size)
        return;

    vec->data[position] = NULL;
        int i;
    for (i = 0; i < vec->size - 1; i++) {
        vec->data[i] = vec->data[i + 1];
        vec->data[i + 1] = NULL;
    }

    vec->size--;

    if (vec->size > 0 && vec->size == vec->capacity / 4)
        vector_resize(vec, vec->capacity / 2);
        
    return vec;
}

void* getElementVector(vector* vec){
	return vec->data[vec->size-1];
}

void* getElementVectorIn(vector* vec,int position){
	if (position >= 0 && position < vec->size){
                return vec->data[position];
	}
    return NULL;
}
int contains(vector* vec,void* element){
        int i;
	for(i=0;i < vec->size;i++){
		if(strcmp(vec->data[i],element) != 0){
			return 0;
		}
	}
	return 1;
}

//########################################################
//	aFolder 
//########################################################
afolder* newafolder(int element_size){
	afolder* af = malloc(sizeof(afolder));
	af->key = malloc(sizeof(char*)*element_size);
	af->data = malloc(sizeof(void*)*element_size);
	af->size = element_size;
	af->elements = 0;
	return af;	
}
void freeafolder(afolder* fld){
	free(fld->key);
	free(fld->data);
	free(fld);
}
void addFiletoafolder(afolder* fld,char* key, void* data){
  assert(fld != NULL);
  assert(key != NULL);
  assert(data != NULL);
  assert(fld->elements+1 < fld->size);
  
  //~ fld->id[fld->elements] = fld->elements;
  fld->key[fld->elements] = strdup(key);
  fld->data[fld->elements] = data;
  fld->elements++;	
}
void* getFiletoafolder(afolder* fld,char* key){
        assert(fld != NULL);
        assert(key != NULL);
        int i;
        for (i=0;i<fld->elements ;i++){
                if (strcmp(key,fld->key[i]) == 0)
                        return fld->data[i];
        }
        return NULL;	
}
char* getKey(afolder* fld,void* data){
        assert(fld != NULL);
        assert(data != NULL);
        int i;
        for (i=0;i<fld->elements ;i++){
                if (data == fld->data[i])
                        return fld->key[i];
        }
        return NULL;
}
//~ int getId(afolder* fld,char* key){
        //~ assert(fld != NULL);
        //~ assert(key != NULL);
        //~ int i;
        //~ for (i=0;i<fld->elements ;i++){
                //~ if (strcmp(key,fld->key[i]) == 0)
                        //~ return fld->id[i];
        //~ }
        //~ return NULL;	
//~ }
int containsfile(afolder* fld,char* key){
        assert(fld != NULL);
        assert(key != NULL);
        int i;
        for (i=0;i<fld->elements;i++)        {
                if (strcmp(key,fld->key[i]) == 0)
                        return 1;
        }
        return 0;
}
