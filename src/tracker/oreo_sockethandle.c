/* @file oreo_tracker_sockethandled.c
 * @author JAPETO - jeffersonamado@gmail.com
 * @date 21 Nov 2014
 * @brief File containing the socket handling, allow acept and monitor a connection to oreo tracker
 * @see
 */
#include "oreo_sockethandle.h"

int get_peer_id(int * connectionState, int size){
	/*indice del nuevo usuario*/
	int index;
        for (index=0;index<size;index++){
		/*en el primer campo vacio retorne este id para un nuevo usuario*/
                if(connectionState[index] == 0) {
                        return index;
                }
        }
        WARN_MSG("trackersockethandle: has reached the limit, tracker full");
	/*no ha mas ids*/
	return -1;
}

aCommand* expected_command(dataPeer* peerconnection){
    /*recibe una conexion mapeado a una estructura dataPeer*/
    assert(peerconnection != NULL);
    /*Creo un nuevo comando vacio para asignar un tipo y una carga util*/
    aCommand* a_command = newCommand(BUFFER_SIZE);
    /*almacen para recibir todos los datos del peer*/
    char buffer[BUFFER_SIZE];
    /*mientras lee voy almacenando en este*/
    char tempBuffer[BUFFER_SIZE];
    /*indica la cantida de datos leidos desde el emisor*/
    int sizeRead = 0;
    /*para poder usarlo como una funcion,
    * que verifique un comando
    * sin perder la carga util
    * */
    int (*checkFunction) (aCommand*, char*);
    /*bucle para llenar el almacen*/
    do{
    /*leo los datos que envia el emisor*/
    sizeRead = read(peerconnection->socketFd, tempBuffer, BUFFER_SIZE);
    /*lo leido lo copio de la temporal al almacen definitivo*/
    strncat(buffer,tempBuffer,sizeRead);
    /*si es conocido el comando sigo leyendo*/
    }while(!what_command(a_command,buffer));

    /*dependiendo el tipo de comando revizo el payload*/
    switch(a_command->type){
	case SEEK_COMMAND:
	    checkFunction = isSeek;
	    break;
	case SENDME_COMMAND:
	    checkFunction = isSendme;
	    break;
	case UNKNOWN:
	    free(a_command);
	    return NULL;
	    break;
    }
    /*indica si este comando tiene un cabecera y un payload*/
    int dataComplete = 0;
    dataComplete = checkFunction(a_command,buffer);
    while(!dataComplete){
	sizeRead = read(peerconnection->socketFd, tempBuffer, BUFFER_SIZE);
	strncat(buffer,tempBuffer,sizeRead);
	dataComplete = checkFunction(a_command,buffer);
    }
    /*Verifico si se ha creado un mal comando*/
    if (dataComplete == 2){
	DEBUG_MSG("expected_command: Bad aCommand, proble make a incoming aCommand ");
	LOG_MSG("[ERROR]\texpected_command: Bad aCommand, proble make a incoming aCommand ");
	ERR_MSG("'expected_command: Bad aCommand, proble make a incoming aCommand ");
	fprintf(stderr, "expected_command: Bad aCommand, proble make a incoming aCommand ");
	perror("expected_command: Bad aCommand, proble make a incoming aCommand ");
	/*libero los recurso, algo se hizo mal aqui o en el socket*/
	free(a_command);
	return NULL;
    }else{
	MSG("\texpected_command: incoming comand is: (%s%s%s)\n",ANSI_COLOR_CYAN,command_from_int(a_command->type),ANSI_COLOR_RESET);
	return a_command;
    }
}

int wait_peer(int socket, int* connectionState, int identifier,pthread_t* threads){
    /*punteros temporales para mapear las entradas*/
    struct sockaddr_in* client_addr = malloc(sizeof(struct sockaddr_in));
    int peerlength = sizeof(struct sockaddr_in);
    int peersocketFd;
    /*accepto la conexion, OJO aqui esta lo bonito del multihilo*/
    peersocketFd = accept(socket, (struct sockaddr*) client_addr, &peerlength);
    /*algun problema al aceptar la conexion*/
    if (socket == -1){
	DEBUG_MSG("wait_peer: Can't accept connection \" no accept()\" ");
	LOG_MSG("[ERROR]\twait_peer: Can't accept connection \" no accept() \"");
	ERR_MSG("wait_peer: Can't accept connection \" no accept()\" ");
	fprintf(stderr, "wait_peer: Can't accept connection \" no accept()\" ");
	return -1;
    }
    /*objeto dataPeer para mapear la conexion a esta estructura, aqui esta vacio*/
    dataPeer* connection = malloc(sizeof(dataPeer));
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr->sin_addr), str, INET_ADDRSTRLEN);
    /*guardo descriptor del socket*/
    connection->socketFd = peersocketFd;
    /*guardo struct sockaddr_in*/
    connection->infoConnection = client_addr;
    /*establezco un identificador para la conexion*/
    connection->idConnection = identifier;
    /*establezco un estado al dataPeer*/
    connection->connectionState = connectionState;
    DEBUG_MSG("wait_peer: New peer incoming with IP [%s] and PORT [%d]\n",
		strdup((char*)inet_ntoa(connection->infoConnection->sin_addr)),(int) ntohs(connection->infoConnection->sin_port));
    /*inicio un nuevo hilo para este nueva conexion y nuevo datapeer*/
    if(pthread_create(&threads[identifier], NULL, (void*) exchange_commands , (void*) connection)){
	DEBUG_MSG("wait_peer: Can't run thread by peer");
	LOG_MSG("[ERROR]\twait_peer: Can't run thread by peer");
	ERR_MSG("wait_peer: wait_peer: Can't run thread by peer");
	fprintf(stderr, "wait_peer: wait_peer: Can't run thread by peer");
	return 2;
    }
    return 1;
}
write_response(int sd, const void *response, size_t count){
    if(strstr(response,"202") != NULL) {
	write(sd, "202", strlen("202"));
	/*obtengo las rutas de los chunks a enviar*/
	char* path = strtok(response," ");
	/*elimino el status code*/
	path = strtok(NULL,"");
	while(path){
	    int fd;                    /* file descriptor for file to send */
	    int rc;                    /* holds return code of system calls */
	    int desc;                  /* file descriptor for socket */
	    struct stat stat_buf;      /* argument to fstat */
	    off_t offset = 0;          /* file offset */
	    fd = open(path, O_RDONLY);
	    if (fd == -1) {
		DEBUG_MSG("write_response: Can't open socket by send chunk %s ! \n",path);
		LOG_MSG("[ERROR]\twrite_response: Can't open socket by send chunk %s ! ",path);
		ERR_MSG("write_response: Can't open socket by send chunk %s !\n",path);
		fprintf(stderr, "Can't open socket by send chunk %s !\n",path);
	    }
	    /* get the size of the file to be sent */
	    fstat(fd, &stat_buf);
	    /* copy file using sendfile */
	    offset = 0;
	    rc = sendfile (sd, fd, &offset, stat_buf.st_size);
	    if (rc == -1) {
		DEBUG_MSG("write_response: Can't by send chunk %s ! \n",path);
		LOG_MSG("[ERROR]\twrite_response: Can't by send chunk %s !",path);
		ERR_MSG("write_response: Can't by send chunk %s !\n",path);
		fprintf(stderr, "Can't by send chunk %s !\n",path);
	    }
	    if (rc != stat_buf.st_size) {
		DEBUG_MSG("write_response: Incomplete transfer from sendfile: %d of %d bytes \n",rc,(int)stat_buf.st_size);
		LOG_MSG("[ERROR]\twrite_response: Can't by send file !");
		ERR_MSG("write_response: Incomplete transfer from sendfile: %d of %d bytes \n",rc,(int)stat_buf.st_size);
		fprintf(stderr, "Incomplete transfer from sendfile: %d of %d bytes \n",rc,(int)stat_buf.st_size);
	    }
	    write(sd, "NULL\n", strlen("NULL\n"));
	    path = strtok(NULL," ");
	}//end while
    }else if(strstr(response,"302") != NULL) {
	write(sd, "302", strlen("302"));
	/*obtengo las rutas de los chunks a enviar*/
	char* path = strtok(response," ");
	/*elimino el status code*/
	path = strtok(NULL,"");
	while(path){
	    int fd;                    /* file descriptor for file to send */
	    int rc;                    /* holds return code of system calls */
	    int desc;                  /* file descriptor for socket */
	    struct stat stat_buf;      /* argument to fstat */
	    off_t offset = 0;          /* file offset */
	    fd = open(path, O_RDONLY);
	    if (fd == -1) {
		DEBUG_MSG("write_response: Can't open socket by send chunk %s ! \n",path);
		LOG_MSG("[ERROR]\twrite_response: Can't open socket by send chunk %s ! ",path);
		ERR_MSG("write_response: Can't open socket by send chunk %s !\n",path);
		fprintf(stderr, "Can't open socket by send chunk %s !\n",path);
	    }
	    /* get the size of the file to be sent */
	    fstat(fd, &stat_buf);
	    /* copy file using sendfile */
	    offset = 0;
	    rc = sendfile (sd, fd, &offset, stat_buf.st_size);
	    if (rc == -1) {
		DEBUG_MSG("write_response: Can't by send chunk %s ! \n",path);
		LOG_MSG("[ERROR]\twrite_response: Can't by send chunk %s !",path);
		ERR_MSG("write_response: Can't by send chunk %s !\n",path);
		fprintf(stderr, "Can't by send chunk %s !\n",path);
	    }
	    if (rc != stat_buf.st_size) {
		DEBUG_MSG("write_response: Incomplete transfer from sendfile: %d of %d bytes \n",rc,(int)stat_buf.st_size);
		LOG_MSG("[ERROR]\twrite_response: Can't by send file !");
		ERR_MSG("write_response: Incomplete transfer from sendfile: %d of %d bytes \n",rc,(int)stat_buf.st_size);
		fprintf(stderr, "Incomplete transfer from sendfile: %d of %d bytes \n",rc,(int)stat_buf.st_size);
	    }
	    write(sd, "NULL\n", strlen("NULL\n"));
	    path = strtok(NULL," ");
	}//end while
    }else if(strstr(response,"402") != NULL) {
	fprintf(stderr,"response: 402 \n");
	write(sd, "402", strlen("402"));
    }else if(strstr(response,"502") != NULL) {
	fprintf(stderr,"response: 502 \n");
	write(sd, "502", strlen("502"));
    }else if(strstr(response,"204") != NULL) {
	fprintf(stderr,"response: 204 \n");
    }else if(strstr(response,"304") != NULL) {
	fprintf(stderr,"response: 304 \n");
    }else if(strstr(response,"404") != NULL) {
	fprintf(stderr,"response: 404 \n");
    }else if(strstr(response,"504") != NULL) {
	fprintf(stderr,"response: 504 \n");
    }
    //~ if(strstr(response,"302") != NULL) {
	//~ fprintf(stderr,"response: 302 \n");
	//~ write(sd, "302", strlen("302"));
	//~ a_file_path = strtok(NULL," ");       // delete status code
	//~ while(a_file_path){
	//~ int fd;                    /* file descriptor for file to send */
	//~ int rc;                    /* holds return code of system calls */
	//~ int desc;                  /* file descriptor for socket */
	//~ struct stat stat_buf;      /* argument to fstat */
	//~ off_t offset = 0;          /* file offset */
	//~ fd = open(a_file_path, O_RDONLY);
	//~ if (fd == -1) {
	//~ DEBUG_MSG("exchange_commands: Can't open socket by send file %s ! \n",a_file_path);
	//~ LOG_MSG("[ERROR]\texchange_commands: Can't open socket by send file %s ! ",a_file_path);
	//~ ERR_MSG("exchange_commands: Can't open socket by send file %s !\n",a_file_path);
	//~ fprintf(stderr, "Can't open socket by send file %s !\n",a_file_path);
	//~ }
	//~ /* get the size of the file to be sent */
	//~ fstat(fd, &stat_buf);
	//~ /* copy file using sendfile */
	//~ offset = 0;
	//~ rc = sendfile (connection->socketFd, fd, &offset, stat_buf.st_size);
	//~ if (rc == -1) {
	//~ DEBUG_MSG("exchange_commands: Can't by send file %s ! \n",a_file_path);
	//~ LOG_MSG("[ERROR]\texchange_commands: Can't by send file %s !",a_file_path);
	//~ ERR_MSG("exchange_commands: Can't by send file %s !\n",a_file_path);
	//~ fprintf(stderr, "Can't by send file %s !\n",a_file_path);
	//~ }
	//~ if (rc != stat_buf.st_size) {
	//~ DEBUG_MSG("exchange_commands: Incomplete transfer from sendfile: %d of %d bytes \n",rc,(int)stat_buf.st_size);
	//~ LOG_MSG("[ERROR]\texchange_commands: Can't by send file !");
	//~ ERR_MSG("exchange_commands: Incomplete transfer from sendfile: %d of %d bytes \n",rc,(int)stat_buf.st_size);
	//~ fprintf(stderr, "Incomplete transfer from sendfile: %d of %d bytes \n",rc,(int)stat_buf.st_size);
	//~ }
	//~ write(connection->socketFd, "NULL\n", strlen("NULL\n"));
	//~ a_file_path = strtok(NULL," ");
	//~ } //End while
}
void exchange_commands(void* dataconnection){
    /*recibo una estructura en tipo (void*) desde wait_peer */
    dataPeer* connection = (dataPeer*) dataconnection;
    /*creo un commando vacio donde ponder lo que envie este peer*/
    aCommand* a_command;
    a_command = expected_command(connection);
    /*Si es formalmente un comando */
    if (a_command != NULL){
	/*obtengo la ip del peer*/
	char* ip_address;
	ip_address = strdup((char*)inet_ntoa(connection->infoConnection->sin_addr));
	/*proceso el comando y obtengo la respuesta*/
	char* response =(char*)process_command(a_command,ip_address);
	//~ MSG("response: %s",response);
	/*write message to client*/
	write_response(connection->socketFd, response, strlen(response));
	/*libero los recursos*/
	free(a_command);
	free(response);
	/*reestablezco el estado de la conexion*/
	connection->connectionState[connection->idConnection] = STATE_DISCONNECTED;  //igual a 0
	/*termino la conexion "full-duplex" */
	shutdown(connection->socketFd,SHUT_RDWR);
    }else{
	/*commando incorrecto*/
	char* response = strdup("604"); //bad request
	/*Escribo el status code*/
	write(connection->socketFd, response, strlen(response));
	/*libero los recursos*/
	free(a_command);
	/*reestablezco el estado de la conexion*/
	connection->connectionState[connection->idConnection] = STATE_DISCONNECTED;  //igual a 0
	/*termino la conexion "full-duplex" */
	shutdown(connection->socketFd,SHUT_RDWR);
    }
}
