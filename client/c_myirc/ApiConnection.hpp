/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** ApiConnection.hpp
*/

#ifndef PLAZZA_APICONNECTION_HPP
#define PLAZZA_APICONNECTION_HPP

#include <string>
#include <pthread.h>

class ApiConnection {
public:
	ApiConnection(const std::string &ip, int port);
	~ApiConnection();
	bool connectToServer(const std::string &ip, int port);
	const std::string &sendCommand(const std::string &command);

private:
	int sock;
	int port;
	std::string ip;
};


#endif //PLAZZA_APICONNECTION_HPP
