#include <string.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "keyValueStore.h"
#include "utils.h"

static struct entry *data;
static int pointer = 0;
static int numberOfentries;

int createData(int length) {
    // Create shared memory
    int shID = shmget(IPC_PRIVATE, length * sizeof(struct entry), IPC_CREAT | 0777);
    if (shID < 0) {
        error("shared memory request error\n");
    }

    // Attach the shared memory to the process
    data = shmat(shID, NULL, 0);
    if ((int) data < 0) {
        error("attach error\n");
    }

    numberOfentries = length;
    return shID;
}

void detachData() {
    // Detach shared memory
    if (shmdt(data) < 0) {
        error("detach error\n");
    }
}

void sharedMemoryDelete(int shID) {
    // Remove shared memory
    if (shmctl(shID, IPC_RMID, 0) < 0) {
        error("shared memory remove error");
    }
}

int put(char *key, char *value) {
    // Copy the key and value to local memory for better processing
    char k[500], v[500];
    strcpy(k, key);
    trim(k);
    strcpy(v, value);
    trim(v);

    // Check if the key already exists
    for (int i = 0; i < numberOfentries; i++) {
        if (strcmp(data[i].key, k) == 0) {
            // If the key exists, update its value
            strcpy(data[i].value, v);
            return -1; // Update
        }
    }

    // Store the new key-value pair
    if (pointer < numberOfentries) {
        strcpy(data[pointer].key, k);
        strcpy(data[pointer].value, v);
        pointer++;
        return 1; // New entry
    }

    return 0; // Memory full
}

int get(char *key, char *res) {
    char k[30];
    strcpy(k, key);
    trim(k);

    // Search for the key
    for (int i = 0; i < numberOfentries; i++) {
        if (strcmp(data[i].key, k) == 0) {
            strcpy(res, data[i].value);
            return 1; // Key found
        }
    }

    strcpy(res, "key not exists");
    return -1; // Key not found
}

int del(char *key) {
    trim(key);

    // Search for the key and delete it
    for (int i = 0; i < pointer; i++) {
        if (strcmp(data[i].key, key) == 0) {
            // Shift data to delete the entry
            for (int j = i; j < pointer - 1; j++) {
                data[j] = data[j + 1];
            }
            pointer--;
            return 1; // Deletion successful
        }
    }

    return -1; // Key not found
}
