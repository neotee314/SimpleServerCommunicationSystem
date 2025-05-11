#include <string.h>
#include <stdio.h>
#include "protocol.h"
#include "keyValueStore.h"
#include "utils.h"

void process_command(char *input, int client_socket) {
    trim(input);
    char *cmd = strtok(input, ":");
    if (!cmd) {
        say(client_socket, "Invalid command\n");
        return;
    }

    if (strcmp(cmd, "PUT") == 0) {
        char *key = strtok(NULL, ":");
        char *value = strtok(NULL, ":");
        if (!key || !value) {
            say(client_socket, "PUT needs key and value\n");
            return;
        }
        int r = put(key, value);
        if (r == 1) say(client_socket, "OK: entry added\n");
        else if (r == -1) say(client_socket, "OK: entry updated\n");
        else say(client_socket, "Error: memory full\n");

    } else if (strcmp(cmd, "GET") == 0) {
        char *key = strtok(NULL, ":");
        if (!key) {
            say(client_socket, "GET needs key\n");
            return;
        }
        char res[500];
        int r = get(key, res);
        say(client_socket, res);
        say(client_socket, "\n");

    } else if (strcmp(cmd, "DEL") == 0) {
        char *key = strtok(NULL, ":");
        if (!key) {
            say(client_socket, "DEL needs key\n");
            return;
        }
        int r = del(key);
        if (r == 1) say(client_socket, "OK: deleted\n");
        else say(client_socket, "Key not found\n");

    } else {
        say(client_socket, "Unknown command\n");
    }
}
