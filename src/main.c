#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>

#include "keyValueStore.h"
#include "utils.h"
#include "sub.h"

int server_socket;
int shID;

void handle_shutdown(int sig) {
    if (server_socket) close(server_socket);
    sharedMemoryDelete(shID);
    printf("\n[+] Server shut down.\n");
    exit(0);
}

int main() {
    signal(SIGINT, handle_shutdown);

    shID = createData(100);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) error("Socket creation failed");

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5678);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        error("Bind failed");

    if (listen(server_socket, 10) < 0) error("Listen failed");

    printf("[+] Server listening on port 5678\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &len);
        if (client_socket < 0) error("Accept failed");

        if (fork() == 0) {
            close(server_socket);
            communicate(client_socket);
            detachData();
            exit(0);
        }
        close(client_socket);
    }

    return 0;
}
