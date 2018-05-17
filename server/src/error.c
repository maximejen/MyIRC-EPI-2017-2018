/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        error
*/

#include "../include/server.h"

bool send_error(const char* error, SOCKET socket)
{
	send(socket, error, strlen(error), 0);
	return false;
}