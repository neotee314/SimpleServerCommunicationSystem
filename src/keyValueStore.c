#include <string.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "keyValueStore.h"
#include "utils.h"

static struct entry *data;
static int pointer = 0;
static int numberOfentries;

int createData(int length) {
    int shID = shmget(IPC_PRIVATE, length * sizeof(struct entry), IPC_CREAT | 0777);
    if (shID < 0) error("shared memory request error\n");
    data = shmat(shID, NULL, 0);
    if ((int)data < 0) error("attach error\n");
    numberOfentries = length;
    return shID;
}

void detachData() {
    if (shmdt(data) < 0) error("detach error\n");
}

void sharedMemoryDelete(int shID) {
    if (shmctl(shID, IPC_RMID, 0) < 0) error("shared memory remove error");
}

int put(char *key, char *value) {
    trim(key); trim(value);
    for (int i = 0; i < pointer; i++) {
        if (strcmp(data[i].key, key) == 0) {
            strcpy(data[i].value, value);
            return -1; // update
        }
    }
    if (pointer < numberOfentries) {
        strcpy(data[pointer].key, key);
        strcpy(data[pointer].value, value);
        pointer++;
        return 1; // new entry
    }
    return 0; // memory full
}

int get(char *key, char *res) {
    trim(key);
    for (int i = 0; i < pointer; i++) {
        if (strcmp(data[i].key, key) == 0) {
            strcpy(res, data[i].value);
            return 1;
        }
    }
    strcpy(res, "key not exists");
    return -1;
}

int del(char *key) {
    trim(key);
    for (int i = 0; i < pointer; i++) {
        if (strcmp(data[i].key, key) == 0) {
            for (int j = i; j < pointer - 1; j++) {
                data[j] = data[j + 1];
            }
            pointer--;
            return 1;
        }
    }
    return -1;
}
