/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
** client
*/

#include "../include/server.h"

int *get_client_roomid_by_socket(server_t *server, SOCKET socket)
{
	for (int i = 0; i < server->nbclients; i++) {
		if (server->clients[i].sockCLient == socket)
			return server->clients[i].roomId;
	}
	return NULL;
}

SOCKET get_client_socket_by_name(server_t *server, char *name)
{
	for (int i = 0; i < server->nbclients; i++) {
		if (strcmp(name, server->clients[i].nickName) == 0)
			return server->clients[i].sockCLient;
	}
	return -1;
}

client_t *get_client_by_socket(server_t *server, SOCKET socket)
{
	for (int i = 0; i < server->nbclients; i++) {
		if (server->clients[i].sockCLient == socket)
			return &server->clients[i];
	}
	return NULL;
}

char *get_client_name_by_socket(server_t *server, SOCKET socket)
{
	for (int i = 0; i < server->nbclients; i++) {
		if (server->clients[i].sockCLient == socket)
			return server->clients[i].nickName;
	}
	return NULL;
}

bool compress_client_array(server_t *server, int socket)
{
	for (int i = 0; i < server->nbclients; i++) {
		if (server->clients[i].sockCLient == socket) {
			for (int j = i; j < server->nbclients; j++) {
				server->clients[j] = server->clients[j + 1];
				//server->fds[j].fd = server->fds[j + 1].fd;
			}
			i--;
			server->nbclients--;
		}
	}
}