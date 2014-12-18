/*! \mainpage
* <img src="../logo.jpg" style="width:400px;height:200px">
* <b>Developer</b>&nbsp;Jefferson Amad Pe&ntilde;a Torres, JAPETO<br/>
* <b>Development status</b>&nbsp;	Active <br/>
* <b>Operating system</b>	&nbsp;Linux<br/>
* <b>Type</b>	&nbsp;Online file sharing<br/>
* <br/>
* <b>Introduction</b><br/>
* <p>Many software packages for the various flavors of UNIX and Linux come
* as compressed archives of source files. The same package may be
* "built" to run on different target machines, and this saves the
* author of the software from having to produce multiple versions.
* Unfortunately, this puts the responsibility of actually "building"
* and installing the software on the end user,
* the de facto "system administrator"</p><br/><br/>
* <b>Building and Installation</b><br/>
* <p><b><i>Requirements</i></b><br/>
* <b><i>Installation</i></b><br/>
* You have downloaded or otherwise acquired a software package.
* Most likely it is archived (tarred) and compressed (gzipped),
* in .tar.gz or .tgz form (familiarly known as a "tarball").
* First copy it to a working directory.
* Then untar and gunzip it. The appropriate command
* for this is tar xzvf oreosync.tar.gz.
* The compile.sh is the key to the build process. In its simplest form,
* a bash is a script for compiling or building the "binaries",
* the executable portions of a package. The compile.sh can also provide
* a means of updating a software package without having to recompile
* very single source file in it, but that is a different
* story (or a different article).
* <br/>
* At some point, the Makefile launches cc or gcc. This is actually
* a preprocessor, a C (or C++) compiler, and a linker,
* invoked in that order. This process converts
* the source into the binaries, the actual executables.
* Invoking ./configure.sh usually involves just typing make.
* This generally builds all the necessary executable files for
* the package in question. However, make can also do other tasks,
* such as installing the files in their proper directories
*  (./configure install) and removing stale object files
* (./configure clean).<br/>
* <b><i>Usage</i></b><br/>
* </p></br>
* <b>Getting Started</b><br/>
* <b>Temporary-file directory</b><br/>
* <b>Home directory</b><br/>
* <b>Large-file support</b><br/>
* <b>Binaries</b><br/>
* <b>Libraries</b><br/>
* <b>Documentation</b><br/>
* For general instructions about how to install OreoSync,
* please refer to the top-level README file<br/>
*/
#include "tracker/oreo_sockethandle.h"
#include "tracker/oreo_datastructure.h"
#include "tracker/oreo_filehandle.h"
#include "tracker/oreo_globals.h"
#include "tracker/oreo_tracker.h"
#include "tracker/oreo_tracker.h"
#include "oreo_conf.h"

int DEBUG_MODE = 0;
int GUI_MODE = 0;
int WARN_SILENT = 1;
int LOG_SILENT = 1;
int ERR_SILENT = 1;

int main(int argc, char** argv){

        printf(ANSI_COLOR_BLUE"\n****************************************"ANSI_COLOR_RESET"\n");
        printf("OREO TRACKER RUN by JAPeTo \n");
        printf("IP [%s] and PORT [%d]\n","XXX.XXX.XXX.XXX",TRACKER_PORT);
        printf(ANSI_COLOR_BLUE"****************************************"ANSI_COLOR_RESET"\n \n");

        if (argc > 1) {
                int i;
                for(i=0;i<argc;i++){
                        if(strcmp(argv[i],"--debug") ==0){
                                 printf(ANSI_COLOR_RED"**DEBUG_MODE ON**"ANSI_COLOR_RESET"\n");
                                 DEBUG_MODE = 1;
                        }else if(strcmp(argv[i],"--log") ==0){
                                 printf(ANSI_COLOR_RED"**LOG SILENT ON**"ANSI_COLOR_RESET"\n");
                                 LOG_SILENT = 0;
                        }else if(strcmp(argv[i],"--w") ==0){
                                 printf(ANSI_COLOR_RED"**WARN SILENT ON**"ANSI_COLOR_RESET"\n");
                                 WARN_SILENT = 0;
                        }else if(strcmp(argv[i],"--err") ==0){
                                 printf(ANSI_COLOR_RED"**ERR SILENT ON**"ANSI_COLOR_RESET"\n");
                                 ERR_SILENT = 0;
                        }else if(strcmp(argv[i],"--enable-gui ") ==0){
                                 printf(ANSI_COLOR_RED"**GUI MODE ON**"ANSI_COLOR_RESET"\n");
                                 GUI_MODE = 0;
                        }
                }
        }
        OreoTracker = new_tracker();
        folderMonitor((char*) USER_HOME);
        run_tracker();
}
