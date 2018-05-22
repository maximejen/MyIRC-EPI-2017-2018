/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        broadcast
*/

#include "../include/server.h"

bool send_to_all_clients(server_t *server, char *messsage, int id_room)
{
	for (int i = 0; i < server->nbclients; i++) {
		for (int j = 0; j < server->clients[i].nb_rooms; j++) {
			if (server->clients[i].roomId[j] == id_room) {
				send(server->clients[i].sockCLient, messsage, strlen(messsage), 0);
				send(server->clients[i].sockCLient, "\n", 1, 0);
			}

		}
	}
	return true;
}

bool send_private_message(server_t *server, char *message, char *name_to_send)
{
	SOCKET to_send = get_client_socket_by_name(server, name_to_send);

	send(to_send, message, strlen(message), 0);
	send(to_send, "\n", 1, 0);
	return true;
}