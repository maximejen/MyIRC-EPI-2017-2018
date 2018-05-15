/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
**        No file there, just an epitech header example
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SOCKET int
#define TIMEOUT 3 * 60 * 1000 //mdr c'est plus simple pour compter
#define MAXCLIENT 200
#define BUFFERSIZE 1000
#define MAXROOM 200

enum Status {
	NONE,		//Used when connecting
	UNACTIVE,
	ACTIVE
};

typedef struct client_s
{
	int roomId;
	SOCKET sockCLient; //can be used as id do not modify
	char *nickName;
}		client_t;

typedef struct channel_s
{
	int id;
	char *roomName;
	enum Status status;
	int nbCLient;

}		channel_t;

typedef struct server_s
{
	SOCKET socketServer;
	char   buffer[BUFFERSIZE];
	int currentSize;
	struct pollfd fds[MAXCLIENT];
	channel_t channels[MAXROOM];
	client_t clients[MAXCLIENT];
	int nbChannels;
	int nbclients;

}	server_t;

void create_server(int port, server_t*);

/*
 * main_loop.c
 */
bool main_loop(server_t *server, int rc);


/*
 * Connexion.c
 */
bool close_connexion(server_t *server, int id);
bool close_all_connexion(server_t *server, int nfds);
bool compress_array(server_t *server, int nfds);



#endif //SERVER_H_
