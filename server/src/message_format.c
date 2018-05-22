/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        message_format
*/

#include "../include/server.h"


int get_message_lenght(char *error_code, char *username, char *fctname, char *error_name)
{
	int len = 0;

	len += (int)strlen(":localhost") + 1;
	if (error_code != NULL)
		len += (int)strlen(error_code) + 1;
	if (username != NULL)
		len += (int)strlen(username) + 1;
	if (fctname != NULL)
		len += (int)strlen(fctname) + 1;
	if (error_name != NULL)
		len += (int)strlen(error_name) + 1;
	return len;
}

char *create_response(char *error_code, char *username, char *fctname, char *error_name)
{
	char *message = malloc(sizeof(char) * (get_message_lenght(error_code, username, fctname, error_name)));

	message[0] = '\0';
	message = strcat(message, ":localhost ");
	if (error_code != NULL) {
		message = strcat(message, error_code);
		message = strcat(message, " ");

	}
	if (username != NULL) {
		message = strcat(message, username);
		message = strcat(message, " ");
	}
	if (fctname != NULL) {
		message = strcat(message, fctname);
		message = strcat(message, " ");
	}
	if (error_name != NULL) {
		message = strcat(message, ":");
		message = strcat(message, error_name);
	}
	message = strcat(message, "\n");
	return message;
}