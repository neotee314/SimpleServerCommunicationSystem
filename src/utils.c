// utils.c
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

// Print error message and terminate the program
void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}


// Remove leading and trailing whitespace characters
void trim(char *s) {
    int count = 0;
    while (s[count] == ' ' || s[count] == '\t' || s[count] == '\n' || s[count] == '\r')
        count++;

    if (count > 0) {
        memmove(s, s + count, strlen(s + count) + 1);
    }

    int i = strlen(s) - 1;
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r'))
        i--;

    s[i + 1] = '\0';
}

// Send a string to a socket
int say(int client_socket, char *s) {
    int result = send(client_socket, s, strlen(s), 0);
    if (result == -1)
        fprintf(stderr, "Error talking to client: %s\n", strerror(errno));
    return result;
}


// Read input from client until '\n' is encountered
int read_in(int socket_client, char *buf, int len) {
    char *s = buf;
    int slen = len;
    int c = recv(socket_client, s, slen, 0);

    while (c > 0 && s[c - 1] != '\n') {
        s += c;
        slen -= c;
        c = recv(socket_client, s, slen, 0);
    }

    if (c < 0) return c;
    else if (c == 0) buf[0] = '\0';
    else s[c - 1] = '\0';

    return len - slen;
}


