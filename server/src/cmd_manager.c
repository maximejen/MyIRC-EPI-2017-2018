/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        cmd_manager
*/

#include "../include/server.h"

const char* CMD[9] = {
	"NICK",
	"LIST",
	"JOIN",
	"PART",
	"USERS",
	"NAMES",
	"PRIVMSG",
	"ACCEPT_FILE",
	NULL
};


bool is_cmd(server_t *server)
{
	for (int i = 0; CMD[i] != NULL; i++) {
		if (strncasecmp(CMD[i], server->buffer, strlen(CMD[i])) == 0)
			return true;
	}
	return false;
}

int get_cmd_position(server_t *server)
{

	for (int i = 0; CMD[i] != NULL; i++) {
		if (strncasecmp(CMD[i], server->buffer, strlen(CMD[i])) == 0)
			return i;
	}
	return -1;
}

bool can_send_message(server_t *server, SOCKET sender, int pos)
{
	if (pos == 0)
		return true;
	char *cmd = get_arg_value(server->buffer, 0);
	if (get_client_name_by_socket(server, sender) == NULL)
		return send_error(create_response("451", NULL, cmd, "You must finish connecting with another nickname first."), sender);
	return true;
}

bool execute_cmd(server_t *server, SOCKET sender)
{
	int pos = get_cmd_position(server);
	printf("pos : %d\n", pos);
	if (!can_send_message(server, sender, pos))
		return false;
	if (pos == -1) {
		printf("error: %s\n", server->buffer);
		return send_error( create_response("421", get_client_name_by_socket(server, sender), NULL, "Unknown command"), sender);
	}
	bool (*func_ptr_array[9]) (server_t *, SOCKET);
	func_ptr_array[0] = &set_user_name;
	func_ptr_array[1] = &list_channels;
	func_ptr_array[2] = &join_channel;
	func_ptr_array[3] = &disconnect;
	func_ptr_array[4] = &list_users_connected;
	func_ptr_array[5] = &list_users_in_channel;
	func_ptr_array[6] = &send_message_to_another_client_or_channel;

	bool ret = (*func_ptr_array[pos])(server, sender);
	return ret;
}