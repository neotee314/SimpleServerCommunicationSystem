#ifndef SUB_H
#define SUB_H
#define BUFFER_SIZE 2048


// Open a TCP server socket
int open_server_socket();

// Bind a socket to the given port
int bind_to_port(int socket, int port);

// Send a formatted message to the client
void printMessageToClient(char *com, char *key, char *value, int sockId);

// Gracefully disconnect a client from the server
void disconnectFromServer(int sockId);

// Send initial welcome message to client
int printStartingMessage(int sockId);

// Handle PUT command
void performPUT(char *key, char *value, int sockId);

// Handle DEL command
void performDEL(char *key, int sockId);

// Handle GET command
void performGET(char *key, int sockId);

// Main function to handle communication with client
void communicate(int client_socket);

#endif // SUB_H
