/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        channels
*/

#include "../include/server.h"

bool move_user_to_another_room(server_t *server)
{

}

bool init_new_channel(server_t *server, char *name)
{
	int id = server->nbChannels;
	server->channels[id].id = id;
	server->channels[id].roomName = strdup(name);
	server->channels[id].nbCLient = 0;
	server->channels[id].status = ACTIVE;
	server->nbChannels++;
}

int get_room_id_by_name(server_t *server, char *name)
{
	for (int i = 0; i < server->nbChannels; i++) {
		if (strcmp(server->channels[i].roomName, name) == 0)
			return server->channels[i].id;
	}
	return 0;
}

char* get_room_name_by_id(server_t *server, int id)
{
	for (int i = 0; i < server->nbChannels; i++) {
		if (server->channels[i].id == id)
			return server->channels[i].roomName;
	}
	return (NULL);
}