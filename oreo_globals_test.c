/**
 * @file oreo_datastructure.h
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief
 * @see
 */

 #include "oreo_globals.h"

int main(int argc, char** argv){
        printf("****************************************\n");
        printf("GLOBALS TESTs \n");      
                DEBUG("THIS DEBUG MESSAGE\n");        
                WARN("THIS WARNING MESSAGE\n");
                LOG("THIS LOG MESSAGE\n");
        printf("OREO_TRACKER_TEST [%d]\n", OREO_TRACKER_TEST);
        printf("TCP_PROTOCOL_NUMBER [%d]\n", TCP_PROTOCOL_NUMBER);
        printf("PORT [%d]\n", PORT);
        printf("PEERCONCURRENT [%d] \n",PEERCONCURRENT);
        printf("BUFFER_SIZE [%d]\n", BUFFER_SIZE);
        printf("****************************************\n");
}

