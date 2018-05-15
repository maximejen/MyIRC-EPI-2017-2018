/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** create_server
*/

#include "../include/server.h"

const char* HOSTNAME = "127.0.0.1";

int bind_server(int rc, SOCKET sockserver, int port)
{
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(HOSTNAME);
	addr.sin_port = htons((uint16_t)port);
	rc = bind(sockserver, (struct sockaddr*)&addr, sizeof(addr));
	if (rc < 0) {
		perror("bind() failed");
		close(sockserver);
		exit(-1);
	}
	rc = listen(sockserver, 120);
	if (rc < 0) {
		perror("listen() failed");
		close(sockserver);
		exit(-1);
	}
	return (rc);
}

bool init_poll_struct(server_t *server, SOCKET socketserver)
{
	memset(server->fds, 0, sizeof(server->fds));
	server->fds[0].fd = socketserver;
	server->fds[0].events = POLLIN;
}

void create_server(int port, server_t *server)
{
	SOCKET sockserver;
	int rc;
	int on = 1;
	printf("Connecting on port : %d\n", port);
	sockserver = socket(AF_INET, SOCK_STREAM, 0);
	if (sockserver < 0) {
		perror("Socket() failed");
		exit(-1);
	}
	rc = setsockopt(sockserver, SOL_SOCKET, SO_REUSEADDR, (char*)&on,
			sizeof(on));
	if (rc < 0) {
		perror("setsockopt() failed");
		close(sockserver);
		exit(-1);
	}
	rc = ioctl(sockserver, FIONBIO, (char *)&on);
	if (rc < 0) {
		perror("ioctl() failed");
		close(sockserver);
		exit(-1);
	}
	rc = bind_server(rc, sockserver, port);
	init_poll_struct(server, sockserver);
	server->socketServer = sockserver;
	main_loop(server, rc);
}

