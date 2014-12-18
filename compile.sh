#!/bin/bash
#* Written by Jefferson Amado Pea Torres, started November 2014.
#
# Copyright (C) 2014 Jefferson Amado Pea Torres
# email: jeffersonamado@gmail.com- jefferson.amado.pena@correounivalle.edu.co
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# VERSION="2.21"
# Warning about compilation and permission
echo "*********************************************************"
echo "*   ____                     _____                      *"
echo "*  / __ \                   / ____|                     *"
echo "* | |  | | _ __  ___   ___ | (___   _   _  _ __    ___  *"
echo "* | |  | || '__|/ _ \ / _ \ \___ \ | | | || '_ \  / __| *"
echo "* | |__| || |  |  __/| (_) |____) || |_| || | | || (__  *"
echo "*  \____/ |_|   \___| \___/|_____/  \__, ||_| |_| \___| *"
echo "*                                    __/ |              *"
echo "*                                   |___/               *"
echo "*                                                       *"
echo "* by JAPeTo                                             *"
echo "*                        OreoSync                       *"
echo "*    This  script make OreoSync folder in user home,    *"
echo "*    make executable oreosync.                          *"
echo "*                                                       *"
echo "*    For general instructions about how to compile      *"
echo "*    OreoSync please refer to the top-level README      *"
echo "*                                                       *"
echo "*********************************************************"
echo
echo "MAKE FOLDER..."
if [ ! -d "$HOME/OreoSync/.oreo/temp" ]; then
        echo "creating $HOME/OreoSync folder"
        mkdir -p "$HOME/OreoSync/.oreo/temp"
fi
echo "Make a OreoSync Binary ..."
gcc -o oreosync src/tracker/md5.h \
        src/tracker/md5.c \
        src/tracker/sha1.h \
        src/tracker/sha1.c \
        src/tracker/oreo_globals.h \
        src/client/oreo_functions.h \
        src/client/oreo_functions.c \
        src/client/oreo_client.h \
        src/client/oreo_client.c \
        src/client/oreo_peerhandle.h \
        src/client/oreo_peerhandle.c \
        src/client/oreo_clientgui.c \
        src/tracker/oreo_tracker_loghandle.h \
        src/tracker/oreo_tracker_loghandle.c \
        src/tracker/oreo_datastructure.c \
        src/tracker/oreo_datastructure.h \
        src/tracker/oreo_commandhandle.h \
        src/tracker/oreo_commandhandle.c \
        src/tracker/oreo_commandprocessor.c \
        src/tracker/oreo_commandprocessor.h  \
        src/tracker/oreo_sockethandle.h \
        src/tracker/oreo_sockethandle.c \
        src/tracker/oreo_filehandle.h \
        src/tracker/oreo_filehandle.c  \
        src/tracker/oreo_tracker.h \
        src/tracker/oreo_tracker.c \
        src/oreo_conf.h \
        src/oreo_conf.c \
        src/oreosync.c -w -lpthread -lm

