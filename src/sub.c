// sub.c
#include "sub.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int open_server_socket() {
    // Opens a server socket using IPv4 (AF_INET) and TCP (SOCK_STREAM)
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error opening socket");
        exit(1);
    }
    return server_socket;
}

int bind_to_port(int server_socket, int port) {
    // Binds the server socket to a specified port and IP address (INADDR_ANY)
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    // Binds the socket to the port, if it fails, returns -1
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding to port");
        return -1;
    }
    return 0;
}

void performGET(char *data, int client_socket) {
    // Handles the GET request from the client and sends a response
    char response[] = "This is the GET response.";
    send(client_socket, response, strlen(response), 0);
}

void performDEL(char *data, int client_socket) {
    // Handles the DELETE request from the client and sends a response
    char response[] = "This is the DEL response.";
    send(client_socket, response, strlen(response), 0);
}

void performPUT(char *data, char *value, int client_socket) {
    // Handles the PUT request from the client and sends a response
    char response[] = "This is the PUT response.";
    send(client_socket, response, strlen(response), 0);
}

void disconnetFormServer(int client_socket) {
    // Closes the connection with the client
    close(client_socket);
}

int printStartingMessage(int port) {
    // Prints the starting message indicating the server is running on the given port
    printf("Server started on port %d\n", port);
    return 0;
}

void printMessageToClient(char *message, char *address, char *port, int client_socket) {
    // Constructs and sends a message to the client, including the server address and port
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Message from %s:%s - %s", address, port, message);
    send(client_socket, buffer, strlen(buffer), 0);
}

void communicate(int client_socket) {
    // Main function for handling communication with the client
    char buffer[1024];
    int n;

    // Receives a message from the client
    memset(buffer, 0, sizeof(buffer));
    n = recv(client_socket, buffer, sizeof(buffer), 0);
    if (n < 0) {
        perror("Error reading from socket");
        exit(1);
    }

    // Process the client request based on the command received
    if (strncmp(buffer, "GET", 3) == 0) {
        performGET(buffer, client_socket);  // Calls GET handler
    } else if (strncmp(buffer, "DEL", 3) == 0) {
        performDEL(buffer, client_socket);  // Calls DELETE handler
    } else if (strncmp(buffer, "PUT", 3) == 0) {
        performPUT(buffer, buffer + 4, client_socket);  // Calls PUT handler
    } else {
        // If an unknown command is received, sends an error message
        char error_message[] = "Unknown command.";
        send(client_socket, error_message, strlen(error_message), 0);
    }
}
