#include "oreo_datastructure.h"


int main(int argc, char** argv){        
        
        printf("****************************************\n"); 
        printf("vector TEST\n"); 
        printf("****************************************\n"); 
        vector* vec = newVector(256,20);
        char buffer[20];
        
        printf("vector size: %d\n",vec->size);
        
        int i;
        //addElement
        for(i=0;i<20;i++){
                addElement(vec,(void*) "data" );
        }        
        printv(vec);
        printf("vector size: %d\n",vec->size);
        //addElementIn
        for(i=0;i<20;i++){
                addElementIn(vec,i,(void*)"JAPETO");
        }
        printv(vec);
        printf("vector size: %d\n",vec->size);
        
        printf("vector value: %s \n", (char*)getElementVector(vec));
        printf("vector index: 2 value: %s \n",(char*)getElementVectorIn(vec,2));
        if(contains(vec,(void*)"JAPETO")){
                printf("contains JAPETO TRUE\n");
        }
        if(!contains(vec,(void*)"data")){
                printf("contains data FLASE\n");
        }
        printf("vector size: %d\n",vec->size);
        //removeElement
        for(i=0;i<10;i++){
                removeElement(vec);
        }        
        printv(vec);
        printf("vector size: %d\n",vec->size);
        for(i=vec->size-1;i<vec->capacity;i++){
                addElementIn(vec,i,(void*)"JAPETO");
        } 
        printv(vec);
        printf("vector size: %d\n",vec->size);       
        //removeElementIn
        removeElementIn(vec,1);
        printv(vec);
        printf("vector size: %d\n",vec->size);         
        removeAllElements(vec);
        printv(vec);
        printf("vector size: %d\n",vec->size); 
        freeVector(vec);
        printf("****************************************\n"); 
        printf("****************************************\n"); 
        printf("aPeer TEST\n"); 
        printf("****************************************\n"); 
        vector* vecp = newVector(1800,5);
        printf("vector of peers size: %d - %d\n",vec->size,vec->capacity);         
        
        aPeer* p = newaPeer("127.0.0.1","8918");
        printf("p info [%s, %s, %s, %d] \n",  p->name, p->port, p->ip, p->status);
        aPeer* cp = createPeer("JAPeTo","127.255.2.1","4563",STATUS_DOWNLOADING);
        printf("c info [%s, %s, %s, %d] \n",  cp->name, cp->port, cp->ip, cp->status);
        
        addElement(vecp,p);
        addElement(vecp,cp);
        printf("vector of peers size: %d\n",vec->size); 

        aPeer* q = getPeerByIp(vecp,"127.0.0.1");
        printf("q info [%s, %s, %s, %d] \n",  q->name, q->port, q->ip, q->status);

        aPeer* r = getPeerByName(vecp,"JAPeTo");
        printf("r info [%s, %s, %s, %d] \n",  r->name, r->port, r->ip, r->status);        
        
        printf("****************************************\n"); 
        printf("****************************************\n"); 
        printf("afolder TEST\n"); 
        printf("****************************************\n");                
        
        afolder* af = newafolder(1024);
        addFiletoafolder(af,"123456","este es contenido de un archivo");        
        addFiletoafolder(af,"1256","contenido de un archivo");
        addFiletoafolder(af,"123457","este");
        addFiletoafolder(af,"1289456","este es contenido");
        addFiletoafolder(af,"23456","este es la data de un archivo");
        
        printf("data %s\n", (char*)getFiletoafolder(af,"123456"));
        printf("data %s\n", (char*)getFiletoafolder(af,"1289456"));
        printf("data %s\n", (char*)getFiletoafolder(af,"23456"));
        
        printf("key %s\n", getKey(af,"este es contenido de un archivo"));
        printf("key %s\n", getKey(af,"contenido de un archivo"));
        printf("key %s\n", getKey(af,"este es un archivo"));
        if(containsfile(af,"1256")){
                printf("contains file\n"); 
        }else{
                printf("not contains file\n"); 
        }
        freeafolder(af);
        printf("****************************************\n"); 
}
