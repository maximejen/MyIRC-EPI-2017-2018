/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        channels
*/

#include "../include/server.h"

bool move_user_to_room(server_t *server, SOCKET socket, char *roomName)
{
	client_t *client = get_client_by_socket(server, socket);
	int room_id = get_room_id_by_name(server, roomName);

	if (room_id == ERROR) {
		printf("Creating new room\n");
		room_id = init_new_channel(server, strdup(roomName));
	}
	add_room_in_client_list(room_id, client);
}

int init_new_channel(server_t *server, char *name)
{
	printf("New room : %s avec id : %d\n", name, server->nbChannels);
	int id = server->nbChannels;
	server->channels[id].id = id;
	server->channels[id].roomName = strdup(name);
	server->channels[id].nbCLient = 0;
	server->channels[id].status = ACTIVE;
	server->nbChannels++;
	return id;
}

int get_room_id_by_name(server_t *server, char *name)
{
	printf("nb channels : %d\n", server->nbChannels);
	for (int i = 0; i < server->nbChannels; i++) {
		printf("Channel name : %s\n", server->channels[i].roomName);
		if (strcmp(server->channels[i].roomName, name) == 0)
			return server->channels[i].id;
	}
	return -1;
}

char* get_room_name_by_id(server_t *server, int id)
{
	for (int i = 0; i < server->nbChannels; i++) {
		if (server->channels[i].id == id)
			return server->channels[i].roomName;
	}
	return (NULL);
}