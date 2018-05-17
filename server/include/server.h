/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
**        No file there, just an epitech header example
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SOCKET int
#define TIMEOUT 3 * 60 * 1000 //mdr c'est plus simple pour compter
#define MAXCLIENT 200
#define BUFFERSIZE 1000
#define MAXROOM 200
#define ERROR -1

enum Status {
	NONE,		//Used when connecting
	UNACTIVE,
	ACTIVE
};

typedef struct client_s
{
	int roomId[10];
	int nb_rooms;
	int current_room;
	SOCKET sockCLient; //can be used as id do not modify
	char *nickName;
}		client_t;

typedef struct channel_s
{
	int id;
	char *roomName;
	enum Status status;
	int nbCLient;

}		channel_t;

typedef struct server_s
{
	SOCKET socketServer;
	char   buffer[BUFFERSIZE];
	int currentSize;
	struct pollfd fds[MAXCLIENT];
	channel_t channels[MAXROOM];
	client_t clients[MAXCLIENT];
	int nbChannels;
	int nbclients;

}	server_t;

void create_server(int port, server_t*);

/*
 * main_loop.c
 */
bool main_loop(server_t *server, int rc);


/*
 * Connexion.c
 */
bool close_connexion(server_t *server, int id);
bool close_all_connexion(server_t *server, int nfds);
bool compress_array(server_t *server, int nfds);

/*
 * client.c
 */
SOCKET get_client_socket_by_name(server_t *server, char *name);
client_t *get_client_by_socket(server_t *server, SOCKET socket);
char *get_client_name_by_socket(server_t *server, SOCKET socket);
bool compress_client_array(server_t *server, int socket);
int *get_client_roomid_by_socket(server_t *server, SOCKET socket);

/*
 * channel.c
 */
int get_room_id_by_name(server_t *server, char *name);
bool move_user_to_room(server_t *server, SOCKET socket, char *roomName);
int init_new_channel(server_t *server, char *name);
bool compress_client_array(server_t *server, int socket);
int get_room_id_by_name(server_t *server, char *name);

/*
 * parse_arg.c
 */
int count_nb_args(char *msg);
char *get_arg_value(char *arg, int pos);
char *substr(char *src, int pos, int len);
char *delete_useles_char(char c, char *str);

/*
 * broadcast.c
 */
bool send_to_all_clients(server_t *server, char *messsage, int id_room);
bool send_private_message(server_t *server, char *message, char *name_to_send);

/*
 * cmd_manager.c
 */
bool is_cmd(server_t *server);

/*
 * user_cmd.c
 */
bool set_user_name(server_t *server, SOCKET socket);
bool execute_cmd(server_t *server, SOCKET sender);

/*
 * cmd.c
 */
bool list_channels(server_t *server, SOCKET socket);
bool join_channel(server_t *server, SOCKET socket);
bool disconnect(server_t *server, SOCKET socket);
bool list_users_connected(server_t *server, SOCKET socket);
bool send_message_to_another_client_or_channel(server_t *server, SOCKET socket);
bool list_users_in_channel(server_t *server, SOCKET socket);

/*
 * client_room_manager.c
 */
bool init_client_arr(server_t *server);
bool add_room_in_client_list(int id, client_t *client);
bool delete_room_in_client_list(int id, client_t *client);
bool is_client_in_room(int id_room, client_t *client);

/*
 * error.c
 */
bool send_error(const char* error, SOCKET socket);

/*
 * message_format.c
 */
char *create_response(char *error_code, char *username, char *fctname, char *error_name);


#endif //SERVER_H_
