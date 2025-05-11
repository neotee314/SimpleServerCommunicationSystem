#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

struct entry {
    char key[500];
    char value[500];
};

int createData(int length);
void detachData();
void sharedMemoryDelete(int shID);
int put(char *key, char *value);
int get(char *key, char *res);
int del(char *key);

#endif
