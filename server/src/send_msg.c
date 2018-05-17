/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        send_msg
*/

#include "../include/server.h"

char *get_message(server_t *server, char *nickname)
{
	int i;
	char *message = malloc(sizeof(char) * (strlen(server->buffer) + (strlen(nickname))));
	char *tmp;
	for (i = 0; server->buffer[i] != '\0'; i++) {
		if (server->buffer[i] == ':')
			break;
	}
	message[0] = 0;
	tmp = substr(server->buffer, i + 1, (int)strlen(server->buffer) - 2);
	tmp = delete_useles_char('\r', tmp);

	message = strcat(message, nickname);
	message = strcat(message, " : ");
	message = strcat(message, tmp);
	if (server->buffer[i] == 0)
		message = get_arg_value(server->buffer, 2);
	return message;
}

bool send_to_channel(server_t *server, char *channel, int socket)
{
	channel = substr(channel, 1, (int)strlen(channel));
	int id_channel = get_room_id_by_name(server, channel);

	if (!is_client_in_room(id_channel, get_client_by_socket(server, socket)))
		return send_error(create_response("404", NULL, channel, "Cannot send to channel"), socket);
	char * nickname = get_client_name_by_socket(server, socket);

	send_to_all_clients(server, get_message(server, nickname), id_channel);
	return true;
}

bool send_message_to_another_client_or_channel(server_t *server, SOCKET socket)
{
	if (count_nb_args(server->buffer) < 3)
		return false;
	char *nickname = get_arg_value(server->buffer, 1);
	if (nickname[0] == '#')
		send_to_channel(server, nickname, socket);
	else
		send_private_message(server, get_message(server, get_client_name_by_socket(server, socket)), nickname);
	return true;
}