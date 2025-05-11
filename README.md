# Server Communication System

## Overview

 This project is a server communication system that I built in C. It handles basic requests like `GET`, `DELETE`, and `PUT` from clients using socket programming. The server uses shared memory and semaphores to manage inter-process communication and avoid race conditions. It’s a simple but effective way to manage multiple client connections concurrently, making sure everything runs smoothly.

## Features

* **Server Communication**: The server listens for incoming requests via TCP/IP sockets and sends responses.
* **Request Handling**: Supports `GET`, `DELETE`, and `PUT` requests.
* **Shared Memory**: Uses shared memory to allow different processes to access and modify data.
* **Semaphores**: Semaphores ensure that multiple processes don't mess with the shared memory at the same time.
* **Race Conditions Handling**: Prevents data corruption and unpredictable behavior by managing concurrent access to shared resources.
* **Dockerized**: The project is fully Dockerized for easy deployment anywhere.

## Technologies

* **C**: I used C because it’s perfect for low-level socket programming and memory management.
* **Sockets**: TCP sockets are used for client-server communication. They ensure reliable data transfer.
* **Shared Memory**: This allows multiple processes to read and write to the same block of memory, making it faster and more efficient.
* **Semaphores**: I used semaphores to make sure only one process can access shared memory at a time, so nothing goes wrong when multiple processes try to read/write at once.
* **Docker**: The app is Dockerized, meaning it can run in any environment with Docker, making deployment much simpler.

## Key Concepts

### 1. Shared Memory

Shared memory is like a big, shared space in the system where multiple processes can read from and write to. It’s faster than passing data through files or network protocols because everything happens locally in memory. I used shared memory to store data that the server processes and clients need to access concurrently.

### 2. Semaphores

Semaphores are like traffic lights for processes. They make sure that only one process can access the shared memory at a time. So, when one process is reading or writing data, others will have to wait until it’s done. This prevents multiple processes from messing with the data at the same time, which could lead to errors.

### 3. Race Conditions

A race condition happens when two or more processes try to access shared data at the same time, leading to unpredictable behavior or corrupted data. In this project, semaphores ensure that only one process can access shared memory at a time, preventing race conditions from happening.

### 4. Semaphore Operations

* **wait()**: This makes a process wait if the semaphore value is zero (meaning the resource is in use).
* **signal()**: This increases the semaphore value, allowing other processes to use the resource if it’s available.

### 5. TCP/IP Sockets

The server and clients communicate via TCP sockets. TCP ensures that data is reliably transferred between the client and server. The server listens on a specific port, waiting for incoming connections. Once a client connects, the server processes their request and sends back a response.

### 6. Client-Server Model

* The server listens on a specified port, waiting for client connections.
* Once a client connects, they can send commands like `GET`, `DELETE`, or `PUT` to interact with the server.
* The server processes the request and sends an appropriate response back to the client.

---

## Setup Instructions

### Prerequisites

* **C Compiler**: Make sure you have a C compiler like `gcc` or `clang`.
* **Docker**: Docker is required to run the application in a container.

### Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/neotee314/server-communication-system.git
   cd server-communication-system
   ```

2. **Compile the code**:

   ```bash
   gcc sub.c -o server -lpthread
   ```

3. **Run the server**:
   Start the server with the port number of your choice:

   ```bash
   ./SimpleTCPKeyValueServer 5678
   ```

   The server will start and wait for client connections.

---

## Docker Setup

I’ve also Dockerized the app, so it’s easy to run anywhere with Docker installed.

1. **Build the Docker image**:

   ```bash
   docker build -t my_fantastic_key_value_server .
   ```

2. **Run the Docker container**:

   ```bash
   docker run -p 5678:5678 server-image
   ```

This will start the server inside a Docker container, mapping port 8080 on your machine to port 8080 in the container. Now you can connect to the server from your client.

---

## Running the Server and Client

### Server

To run the server:

1. Provide a port number when starting the server:

   ```bash
   ./SimpleTCPKeyValueServer 5678
   ```

2. The server will now be ready to accept client connections.

### Client

The client can send requests to the server like so:

* **GET Request**:

  ```bash
  GET /resource
  ```
* **DELETE Request**:

  ```bash
  DEL /resource
  ```
* **PUT Request**:

  ```bash
  PUT /resource {data}
  ```

---

## Example Workflow

1. **Start the server**:
   You start the server by running it on a specified port, like 8080.

2. **Client connects**:
   A client connects to the server and sends one of the following requests:

    * `GET`: Requests information from the server.
    * `DELETE`: Deletes a resource from the server.
    * `PUT`: Updates a resource or adds a new one to the server.

3. **Server processes the request**:
   The server will process the client’s request, and respond with a message such as:

    * `GET`: "This is the GET response."
    * `DELETE`: "This is the DEL response."
    * `PUT`: "This is the PUT response."

---

## File Structure

```text
.
├── CMakeLists.txt
├── Dockerfile
├── README.md
├── Makefile
├── client.c
├── include
│   ├── keyValueStore.h
│   ├── main.h
│   ├── protocol.h
│   ├── sub.h
│   └── utils.h
└── src
    ├── keyValueStore.c
    ├── main.c
    ├── protocol.c
    ├── sub.c
    └── utils.c

```

* **sub.c**: This file contains the server logic for handling requests, sockets, and shared memory.
* **sub.h**: Header file with function declarations.
* **client.c**: Basic client implementation to send requests to the server.
* **Makefile**: A simple Makefile to build the server application.
* **Dockerfile**: The Dockerfile that makes the project easy to run inside a container.

---

## Conclusion

This server communication system I created is a simple yet effective way to learn about socket programming, inter-process communication, shared memory, semaphores, and handling race conditions. It also shows how to deploy a C application using Docker for easier scalability and portability.

---



