#ifndef SUB_H
#define SUB_H

int open_server_socket();
int bind_to_port(int, int);
void performGET(char *, int);
void performDEL(char *, int);
void performPUT(char *, char *, int);
void disconnetFormServer(int);
int printStartingMessage(int);
void printMessageToClient(char *, char *, char *, int);
void communicate(int client_socket);

#endif
