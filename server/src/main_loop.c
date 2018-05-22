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
	char *resp = create_response("020", NULL, " * ", "Please wait while we process your connection.");

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
		server->clients[server->nbclients].sockCLient = newSock;
		init_client_arr(server);
		server->clients[server->nbclients].nb_rooms = 0;
		server->clients[server->nbclients].nickName = NULL;
		server->nbclients++;
		send(newSock, resp, strlen(resp), 0);
	}
	return true;
}

bool is_valid_request(server_t *server)
{
	if (strlen(server->buffer) == 2) {
		if (server->buffer[0] == '\r' && server->buffer[1] == '\n')
			return false;
	}
	return true;
}


bool read_data(server_t *server, int i, int rc, nfds_t nfds)
{
	int len = 0;

	printf("Desciptor %d is readable\n", server->fds[i].fd);
	memset(server->buffer, 0, BUFFERSIZE);
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
	printf("Size : %d\n", (int)strlen(server->buffer));
	if (is_valid_request(server))
		execute_cmd(server, server->fds[i].fd);
	memset(server->buffer, 0, BUFFERSIZE);
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