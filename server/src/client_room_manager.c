/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        client_room_manager
*/

#include "../include/server.h"

bool init_client_arr(server_t *server)
{
	for (int i = 0; i < 10; i++) {
		server->clients[server->nbclients].roomId[i] = -1;
	}
}

bool add_room_in_client_list(int id, client_t *client)
{
	if (client->nb_rooms >= 10)
		return false;
	client->roomId[client->nb_rooms] = id;
	client->nb_rooms++;
	return true;
}

bool delete_room_in_client_list(int id, client_t *client)
{
	bool found = false;
	for (int i = 0; i < client->nb_rooms; i++) {
		if (client->roomId[i] == id) {
			client->roomId[i] = -1;
			found = true;
		}
	}
	for (int i = 0; i < client->nb_rooms; i++) {
		if (client->roomId[i] == -1) {
			for (int j = i; j < client->nb_rooms; j++) {
				client->roomId[j] = client->roomId[j + 1];
			}
			i--;
			client->nb_rooms--;
		}
	}
	return found;
}

bool is_client_in_room(int id_room, client_t *client)
{
	for (int i = 0; i < client->nb_rooms; i++) {
		if (client->roomId[i] == id_room)
			return true;
	}
	return false;
}