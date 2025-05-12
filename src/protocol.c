#include <string.h>
#include <stdio.h>
#include "protocol.h"
#include "keyValueStore.h"
#include "sub.h"
#include "utils.h"

// Handle communication with client
void communicate(int client_socket) {
    if (printStartingMessage(client_socket) != -1) {
        while (1) {
            char buf[BUFFER_SIZE];
            read_in(client_socket, buf, sizeof(buf));

            char *cmd = strtok(buf, " ");
            char *key = strtok(NULL, " ");
            char *value = strtok(NULL, "");

            if (key) trim(key);
            if (value) trim(value);

            if (cmd && strncasecmp(cmd, "put", 3) == 0) {
                performPUT(key, value, client_socket);
            } else if (cmd && strncasecmp(cmd, "del", 3) == 0) {
                performDEL(key, client_socket);
            } else if (cmd && strncasecmp(cmd, "get", 3) == 0) {
                performGET(key, client_socket);
            } else if (cmd && strncasecmp(cmd, "exit", 4) == 0) {
                disconnectFromServer(client_socket);
            } else {
                say(client_socket, "Unknown command\r\n");
            }
        }
    }
}
