#include "sub.h"
#include "keyValueStore.h"
#include "protocol.h"

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "utils.h"



// Create a server socket
int open_server_socket() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1) error("Can't open socket");
    printf("[+] Server socket created\n");
    return s;
}

// Bind socket to a port
int bind_to_port(int socket, int port) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(int)) == -1)
        error("Can't set socket option SO_REUSEADDR");

    int c = bind(socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (c == -1) error("Cannot bind to socket");

    printf("[+] Bound to port: %d\n", ntohs(server_addr.sin_port));
    return c;
}




// Format and send a message to the client
void printMessageToClient(char *com, char *key, char *value, int sockId) {
    char msg[1024];
    snprintf(msg, sizeof(msg), "Server: %s:%s:%s\r\n", com, key, value);
    say(sockId, msg);
}

// Disconnect a client from server
void disconnectFromServer(int sockId) {
    say(sockId, "[-]Disconnected from server\n");
    puts("Client disconnected from server\n");
    close(sockId);
    exit(0);
}

// Send startup message to client
int printStartingMessage(int sockId) {
    int m1 = say(sockId, "[+]Program started\r\n");
    int m2 = say(sockId, "[+]Connected to Server\r\n");
    int m3 = say(sockId, "[+]To exit the program, use the 'exit' command\r\n");
    int m4 = say(sockId, "[+]Client....\r\n");

    return (m1 != -1 && m2 != -1 && m3 != -1 && m4 != -1) ? 1 : -1;
}

// Handle PUT command
void performPUT(char *key, char *value, int sockId) {
    if (key && value) {
        int res = put(key, value);
        if (res == -1) {
            strcat(value, ":overrided");
        }
        printMessageToClient("PUT", key, value, sockId);
        say(sockId, "\n");
    } else {
        say(sockId, "Invalid PUT command\r\n");
    }
}

// Handle DEL command
void performDEL(char *key, int sockId) {
    if (key) {
        if (del(key) == 1) {
            printMessageToClient("DEL", key, "deleted", sockId);
        } else {
            say(sockId, "Key does not exist\r\n");
        }
    } else {
        say(sockId, "Invalid DEL command\r\n");
    }
}

// Handle GET command
void performGET(char *key, int sockId) {
    if (key) {
        char value[100] = {0};
        get(key, value);
        printMessageToClient("GET", key, value, sockId);
        say(sockId, "\n");
    } else {
        say(sockId, "Invalid GET command\r\n");
    }
}

