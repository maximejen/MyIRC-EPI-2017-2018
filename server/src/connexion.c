/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
** connexion
*/

#include "../include/server.h"

bool close_all_connexion(server_t *server, int nfds)
{
	for (int i = 0; i < nfds; i++) {
		if (server->fds[i].fd >= 0)
			close(server->fds[i].fd);
	}
}

bool close_connexion(server_t *server, int id)
{
	close(server->fds[id].fd);
	server->fds[id].fd = -1;
}

bool compress_array(server_t *server, int nfds)
{
	for (int i = 0; i < nfds; i++) {
		if (server->fds[i].fd == -1) {
			for (int j = i; j < nfds; j++) {
				server->fds[j].fd = server->fds[j + 1].fd;
			}
			i--;
			nfds--;
		}
	}
}