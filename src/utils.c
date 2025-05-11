// utils.c
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void error(char *msg) {
    perror(msg);
    exit(1);
}

void trim(char *s) {
    // پیاده‌سازی تابع
}

int say(int client_socket, char *s) {
    return send(client_socket, s, strlen(s), 0);
}

int read_in(int socket_client, char *buf, int len) {
    return recv(socket_client, buf, len, 0);
}
