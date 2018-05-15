/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** main
*/

#include "../include/server.h"

const char* HELP = "USAGE: ./server port\n";

void init_struct(server_t *server)
{
	server->currentSize = 0;
	server->nbChannels = 0;
	server->channels[0].nbCLient = 0;
	server->channels[0].roomName = NULL;
	server->channels[0].id = server->nbChannels;
	server->channels[0].status = NONE;
	server->nbChannels++;
}

int main(int ac, char **av)
{
	server_t server;
	if (ac != 2) {
		printf("%s", HELP);
		return (84);
	}
	init_struct(&server);
	create_server(atoi(av[1]), &server);

}