/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
** main_loop
*/

#include "../include/server.h"

bool connect_new_client(server_t *server, nfds_t *nfds)
{
	int newSock = -1;

	client_t client;
	while (newSock == -1) {
		newSock = accept(server->socketServer, NULL, NULL);
		if (newSock < 0) {
			if (newSock != EWOULDBLOCK) {
				perror("accepet() failed");
			}
			break;
		}
		printf("New connection\n");
		server->fds[*nfds].fd = newSock;
		server->fds[*nfds].events = POLLIN;
		*nfds = *nfds + 1;
		client.nickName = NULL;
		client.sockCLient = newSock;
	}
	return true;
}



bool read_data(server_t *server, int i, int rc, nfds_t nfds)
{
	int len = 0;

	printf("Desciptor %d is readable\n", server->fds[i].fd);
	rc = (int)recv(server->fds[i].fd, server->buffer, sizeof(server->buffer), 0);
	if (rc < 0) {
		perror("recv() failed");
		return false;
	}
	if (rc == 0) {
		printf("Connection closed by client\n");
		close_connexion(server, i);
		compress_array(server, (int)nfds);
		return false;
	}
	len = rc;
	printf(" %d bytes received\n", len);
	printf("Read: %s\n", server->buffer);
	return true;
}

bool determine_who_is_talking(server_t *server, nfds_t *nfds, int rc)
{
	for (int i = 0; i < server->currentSize ; i++) {
		if (server->fds[i].revents == 0)
			continue;
		if (server->fds[i].revents != POLLIN) {
				printf("  Error! revents = %d\n", server->fds[i].revents);
				break;
			}
		if (server->fds[i].fd == server->socketServer) {
			printf("Listening socket\n");
			connect_new_client(server, nfds);
		} else {
			read_data(server, i, rc, *nfds);
		}
	}
	return true;
}

bool main_loop(server_t *server, int rc)
{
	nfds_t  nfds = 1;

	while (43) {
		printf("Waiting on poll\n");
		rc = poll(server->fds, nfds, TIMEOUT);
		if (rc < 0) {
			perror("Poll() failed");
			break;
		}
		if (rc == 0) {
			perror("Poll() timer out");
			break;
		}
		server->currentSize = (int)nfds;
		determine_who_is_talking(server, &nfds, rc);
	}
	return true;
}