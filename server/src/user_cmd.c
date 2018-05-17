/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        user_cmd
*/

#include "../include/server.h"

bool can_use_nickname(server_t *server, char *name)
{
	char *tmp;
	for (int i = 0; i < server->nbclients; i++) {
		tmp = server->clients[i].nickName;
		if (tmp != NULL) {
			if (strcmp(tmp, name) == 0)
				return false;
		}
	}
	return true;
}

bool set_user_name(server_t *server, SOCKET socket)
{
	printf("Changing name\n");
	if (count_nb_args(server->buffer) != 2)
		return false;
	char *name = get_arg_value(server->buffer, 1);
	if (!can_use_nickname(server, name))
		return send_error( create_response("433", NULL, name, "Nickname is already in use"), socket);
	client_t *client = get_client_by_socket(server, socket);
	client->nickName = strdup(name);
	printf("Name changed to %s\n", name);
	return true;
}