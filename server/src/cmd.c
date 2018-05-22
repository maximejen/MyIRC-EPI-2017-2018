/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        cmd
*/

#include "../include/server.h"

const char* ERR_NOSUCHCHANNEL = "ERR_NOSUCHCHANNEL\n";
const char* ERR_NOTONCHANNEL = "ERR_NOTONCHANNEL\n";
const char* ERR_NEEDMOREPARAMS = "ERR_NEEDMOREPARAMS\n";

bool list_channels(server_t *server, SOCKET socket)
{
	char *name;
	char *needle = NULL;

	if (count_nb_args(server->buffer) == 2) {
		needle = get_arg_value(server->buffer, 1);
		for (int i = 0; i < server->nbChannels; i++) {
			name = server->channels[i].roomName;
			if (name != NULL && (strstr(name, needle) != NULL)) {
				send(socket, name, strlen(name), 0);
				send(socket, "\n", 1, 0);
			}
		}
		return true;
	}
	for (int i = 0; i < server->nbChannels; i++) {
		name = server->channels[i].roomName;
		if (name != NULL) {
			send(socket, name, strlen(name), 0);
			send(socket, "\n", 1, 0);
		}
	}
	return true;
}

bool join_channel(server_t *server, SOCKET socket)
{
	client_t *client = get_client_by_socket(server, socket);

	if (count_nb_args(server->buffer) != 2)
		return send_error(ERR_NEEDMOREPARAMS, socket);
	char *name = get_arg_value(server->buffer, 1);
	if (name == NULL)
		return false;
	if (name[0] != '#')
		return send_error(create_response("476", NULL, "JOIN", "Bad channel mask"), socket);
	if (client->nb_rooms == 10)
		return send_error(create_response("405", NULL, name, "You have joined too many channels"), socket);
	name = substr(name, 1, (int)strlen(name));
	move_user_to_room(server, socket, name);
	list_users_in_channel(server, socket);
	send_to_all_clients(server, my_concat(get_client_name_by_socket(server, socket), " is connected"), get_room_id_by_name(server, name));
	return true;
}

bool disconnect(server_t *server, SOCKET socket)
{
	if (count_nb_args(server->buffer) != 2)
		return send_error(ERR_NEEDMOREPARAMS, socket);
	char *room = get_arg_value(server->buffer, 1);
	if (!room)
		return send_error(ERR_NOSUCHCHANNEL, socket);
	if (room[0] != '#')
		return send_error(create_response("476", NULL, "JOIN", "Bad channel mask"), socket);
	room = substr(room, 1, (int)strlen(room));
	int roomid = get_room_id_by_name(server, room);
	if (roomid == -1)
		return send_error(create_response("403", NULL, room, "No such channel"), socket);
	if (!delete_room_in_client_list(roomid, get_client_by_socket(server, socket)))
		return send_error(create_response("442", NULL, room, "You're not on that channel"), socket);
	send_to_all_clients(server, my_concat(get_client_name_by_socket(server, socket), " disconnected"), roomid);
	return true;
}

bool list_users_connected(server_t *server, SOCKET socket)
{
	for (int i = 0; i < server->nbclients; i++) {
		send(socket, server->clients[i].nickName, strlen(server->clients[i].nickName), 0);
		send(socket, " ", 1, 0);
	}
	send(socket, "\n", 1, 0);
	return true;
}

bool list_users_in_channel(server_t *server, SOCKET socket)
{
	if (count_nb_args(server->buffer) != 2)
		return false;
	char *name =  get_arg_value(server->buffer, 1);
	name = substr(name, 1, (int)strlen(name));

	int id = get_room_id_by_name(server, name);

	for (int i = 0; i < server->nbclients; i++) {
		if (is_client_in_room(id, &server->clients[i])) {
			send(socket, server->clients[i].nickName, strlen(server->clients[i].nickName), 0);
			send(socket, " ", 1, 0);
		}
	}
	send(socket, "\n", 1, 0);
	return true;
}

