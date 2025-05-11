// utils.h
#ifndef UTILS_H
#define UTILS_H

void error(char *msg);
void trim(char *s);
int say(int client_socket, char *s);
int read_in(int socket_client, char *buf, int len);

#endif
