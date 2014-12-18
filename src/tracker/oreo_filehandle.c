/* @file oreo_filehandle.c
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and
 * monitor a connection to oreo tracker
 * @see
 */

#include "oreo_filehandle.h"


void folderMonitor(char * a_dirpath){
        DIR *dir;
        struct dirent *ent;
        struct stat buf;
        char * namefile;
        int exists;
        int total_size;
        DEBUG_MSG("oreo_filehandle: opening and load oreo folder \n");
        //~ LOG_MSG("[INFO]\toreo_filehandle:opening and load oreo folder");
        if ((dir = opendir (a_dirpath)) != NULL) {
                int i=0;
                /*monitor oreo folder*/
                while ((ent = readdir (dir)) != NULL) {
                        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0 || strstr(ent->d_name, ".oreo")!= NULL){
                                continue;    /* skip self, oreofolder and parent */
                        }
                        namefile = ent->d_name;
                        char nameandpath[strlen(a_dirpath)+strlen(namefile)];
                        sprintf(nameandpath, "%s/%s", a_dirpath,namefile);
                        aFile* file;
                        file=open_afile(nameandpath);
                        add_file_tracker(OreoTracker->folder, file);
                        i++;
                }
                /*read oreo chunks*/
                //~ DIR * dirchunks;
                                        //~ namefile = ent->d_name;
                        //~ char nameandpath[strlen(a_dirpath)+strlen(namefile)];
                        //~ sprintf(nameandpath, "%s/%s", a_dirpath,namefile);
                //~ folder_tostring(OreoTracker->files);
                closedir (dir);
        }else{
                DEBUG_MSG("oreo_filehandle: could not open oreo folder  \n");
                LOG_MSG("[ERROR]\toreo_filehandle:could not open oreo folder");
                ERR_MSG("oreo_filehandle: could not open oreo folder  \n");
                fprintf(stderr, "oreo_filehandle: could not open oreo folder %s !\n",a_dirpath);
        }

}

