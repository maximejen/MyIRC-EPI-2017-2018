/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017
** File description:
**        parse_arg
*/

#include "../include/server.h"

int count_nb_args(char *msg)
{
	int i = 1;

	strtok(strdup(msg), " \n\r");
	while ((strtok(NULL, " \n\0\r")) != NULL) {
		i++;
	}
	return i;
}

char *delete_useles_char(char c, char *str)
{
	if (!str)
		return NULL;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == c) {
			str[i] = '\0';
			return str;
		}
	}
	return str;
}

char *get_arg_value(char *arg, int pos)
{

	char **arr = malloc(sizeof(char *) * 10);
	int i = 1;

	arr[0] = strtok(strdup(arg), " \n\r:");
	while ((arr[i] = strtok(NULL, " \n\0\r:")) != NULL && i < 9) {
		i++;
	}
	arr[i] = NULL;
	if (pos > i) {
		return NULL;
	}
	return delete_useles_char('\r', arr[pos]);
}

char *substr(char *src, int pos, int len)
{
	char *dest = NULL;
	if (len>0) {
		dest = calloc(len+1, 1);
		if (NULL != dest) {
			strncat(dest, src+pos, len);
		}
	}
	return dest;
}

char *my_concat(char *str1, char *str2)
{
	char *newstr = malloc(sizeof(char) * (strlen(str1) + strlen(str2)));

	newstr[0] = 0;
	newstr = strcat(newstr, str1);
	newstr = strcat(newstr, str2);
	return newstr;
}