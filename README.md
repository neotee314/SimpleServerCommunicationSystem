# 🖧 Server Communication System

## 📝 Overview

This project is a server communication system that I built in C. It handles basic requests like `GET`, `DELETE`, and `PUT` from clients using socket programming. The server uses shared memory and semaphores to manage inter-process communication and avoid race conditions. It’s a simple but effective way to manage multiple client connections concurrently, making sure everything runs smoothly.

## 🔑 Key Concepts

### 1️⃣ Shared Memory

Shared memory is like a big, shared space in the system where multiple processes can read from and write to. It’s faster than passing data through files or network protocols because everything happens locally in memory. I used shared memory to store data that the server processes and clients need to access concurrently.

### 2️⃣ Semaphores

Semaphores are like traffic lights for processes. They make sure that only one process can access the shared memory at a time. So, when one process is reading or writing data, others will have to wait until it’s done. This prevents multiple processes from messing with the data at the same time, which could lead to errors.

### 3️⃣ Race Conditions

A race condition happens when two or more processes try to access shared data at the same time, leading to unpredictable behavior or corrupted data. In this project, semaphores ensure that only one process can access shared memory at a time, preventing race conditions from happening.

### 4️⃣ Semaphore Operations

* **wait()**: This makes a process wait if the semaphore value is zero (meaning the resource is in use).
* **signal()**: This increases the semaphore value, allowing other processes to use the resource if it’s available.

### 5️⃣ TCP/IP Sockets

The server and clients communicate via TCP sockets.

### 6️⃣ Client-Server Model

* The server listens on a specific port for incoming client connections.
* Clients send commands (e.g., `GET`, `PUT`, `DELETE`) to the server.
* The server processes the commands and responds to the client.

---

## 🛠 Technologies

* 💻 **C**: I used C because it’s perfect for low-level socket programming and memory management.
* 📡 **Sockets**: TCP sockets are used for client-server communication.
* 🧠 **Shared Memory**: Enables faster and efficient inter-process communication.
* 🚦 **Semaphores**: Manage concurrent access to prevent race conditions.
* 🐳 **Docker**: Ensures the app runs anywhere consistently.

---

## ⚙ Setup Instructions

### 🔧 Prerequisites

* 🛠 **C Compiler**
* 🐳 **Docker**

### 📥 Installation

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

   ```bash
   ./SimpleTCPKeyValueServer 5678
   ```

---

### 🐳 Docker Setup

1. **Build the Docker Image**:

   To build the Docker image for the `SimpleTCPKeyValueServer`, run the following command:

   ```bash
   docker build -t my_fantastic_key_value_server .
   ```

   This command creates a Docker image from the Dockerfile in the current directory and tags it as `my_fantastic_key_value_server`.

2. **Run the Docker Container**:

   To run the Docker container and map port `5678` in the container to port `5678` on your host, run:

   ```bash
   docker run -it my_fantastic_key_value_server  
   ```

   Now, the server is running on port `5678` of your host and will listen to any requests sent to the container.

---

## ▶ Running the Server and Client

### 🖥 Server

To run the TCP server locally, execute the following command:

```bash
./SimpleTCPKeyValueServer 5678
```

When the server is running, it will show a message like:

```
[+] Server listening on port 5678
```

### 🌐 Connecting to the Server with Telnet

Once the server is running, you can connect to it using Telnet. Open a terminal and run:

```bash
telnet localhost 5678
```

Once connected, you'll see a welcome message like:

```
[+] Connected to Server
[+] To exit the program, use the 'exit' command
```

Then, you can interact with the server by using commands like:

* **GET**:

  ```bash
  GET Key1
  ```

* **DELETE**:

  ```bash
  DEL key1
  ```

* **PUT**:

  ```bash
  PUT key1 value1
  ```

---

## 🗂 File Structure

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

* 🧠 **sub.c**: Server logic
* 📡 **client.c**: Client code
* 🧰 **Makefile**: Build automation
* 🐳 **Dockerfile**: For containerization

---



## ⚙️ CLion Integration with Docker Toolchain

You can use **JetBrains CLion** to build and run the project inside a Docker container by following these steps:

### 1️⃣ Add Docker to CLion

1. Go to

   ```
   File > Settings > Build, Execution, Deployment > Docker
   ```
2. Click on ➕ and choose:

   * Type: **Docker for Windows** or **Unix Socket**, depending on your OS.
3. Click `Test Connection` — it should turn green if everything is okay.

---

### 2️⃣ Configure a Remote Toolchain

1. Go to

   ```
   File > Settings > Build, Execution, Deployment > Toolchains
   ```
2. Click ➕ and create a new toolchain.
3. Set the toolchain type to **Remote Host via Docker**.
4. Choose your image (e.g., `my_fantastic_key_value_server`).
5. Set the paths:

   * **CMake**: `/opt/cmake/bin/cmake`
   * **C Compiler**: `gcc`
   * **C++ Compiler**: `g++`
   * **Make**: `make`

Click **Test Toolchain** to make sure everything works.

---

### 3️⃣ Configure CMake Profile

1. Go to

   ```
   File > Settings > Build, Execution, Deployment > CMake
   ```
2. In your active profile, set **Toolchain** to the one you just created (e.g., `Docker-GCC`).
3. Apply the changes.

---

### ✅ Run and Debug

Now you can build and run the project directly in Docker by clicking the Run ▶️ button in CLion. The code will be mounted inside the container, compiled with the remote toolchain, and executed there.

---

## 🧑‍💻 Example Workflow

Here’s how the interaction with the server will look like when running it with Telnet:

1. **Start the server** by running the command:

   ```bash
   docker run -it my_fantastic_key_value_server  
   ```

   The server will output:

   ```
   [+] Server listening on port 5678
   ```

2. **Connect using Telnet**:

   ```bash
   telnet 127.0.0.1 5678
   ```

   You'll see the following messages:

   ```
   [+] Program started
   [+] Connected to Server
   [+] To exit the program, use the 'exit' command
   [+] Client....
   ```

3. **Interact with the server**:

    * **Send a GET request for a non-existent key**:

      ```bash
      GET key1
      ```

      Server response:

      ```
      Server: GET:key1:key not exists
      ```

    * **Store a key-value pair using PUT**:

      ```bash
      PUT key1 value1
      ```

      Server response:

      ```
      Server: PUT:key1:value1
      ```

    * **Retrieve the stored key-value pair**:

      ```bash
      GET key1
      ```

      Server response:

      ```
      Server: GET:key1:value1
      ```

    * **Delete the key**:

      ```bash
      DEL key1
      ```

      Server response:

      ```
      Server: DEL:key1:deleted
      ```

    * **Try to retrieve the deleted key**:

      ```bash
      GET key1
      ```

      Server response:

      ```
      Server: GET:key1:key not exists
      ```
---

## 🏁 Conclusion

This project is a great learning tool for anyone interested in understanding server-client communication, socket programming, and concurrent process management using semaphores and shared memory.

---
## ⚖ License

All rights reserved by the author, **Abolfazl Heidari**.

---