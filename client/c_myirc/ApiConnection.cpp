/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** ApiConnection.cpp
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <zconf.h>
#include <arpa/inet.h>
#include <iostream>
#include <sys/poll.h>
#include "ApiConnection.hpp"
#include "../../server/include/server.h"

ApiConnection::ApiConnection()
{
}

ApiConnection::~ApiConnection()
{
	close(this->sock);
}

bool ApiConnection::connectToServer(const std::string &ip, int port)
{
	struct protoent *pe;
	struct sockaddr_in s{};

	if (!(pe = getprotobyname("TCP")))
		return false;
	this->sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	s.sin_family = AF_INET;
	s.sin_port = htons((uint16_t)port);
	s.sin_addr.s_addr = inet_addr(ip.c_str());
	if (this->sock == -1 ||
		connect(this->sock, (const struct sockaddr *)&s, sizeof(s)) !=
			0) {
		close(this->sock);
		return false;
	}
	this->port = port;
	this->ip = ip;
	return true;
}

const std::string &ApiConnection::sendCommand(const std::string &command)
{
	std::string ret;
	struct pollfd fds[1];
	nfds_t nfds = 1;
	int rc;
	char result[2000] = {0};

	dprintf(this->sock, "%s\n", command.c_str());
	rc = poll(fds, nfds, 1);
	if (rc < 0) {
		perror("Poll() failed");
	} else if (rc > 0) {
		rc = static_cast<int>(read(this->sock, result, 1999));
		if (rc > 0)
			ret += result;
	}
	return ret;
}
