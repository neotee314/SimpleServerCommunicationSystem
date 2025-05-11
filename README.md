

# 🖧 Server Communication System

## 📝 Overview

This project is a server communication system that I built in C. It handles basic requests like `GET`, `DELETE`, and `PUT` from clients using socket programming. The server uses shared memory and semaphores to manage inter-process communication and avoid race conditions. It’s a simple but effective way to manage multiple client connections concurrently, making sure everything runs smoothly.

## 🔑 Key Concept

### 1️⃣ Shared Memory

Shared memory is like a big, shared space in the system where multiple processes can read from and write to. It’s faster than passing data through files or network protocols because everything happens locally in memory. I used shared memory to store data that the server processes and clients need to access concurrently.


### 2️⃣ Semaphores


Semaphores are like traffic lights for processes. They make sure that only one process can access the shared memory at a time. So, when one process is reading or writing data, others will have to wait until it’s done. This prevents multiple processes from messing with the data at the same time, which could lead to errors.

### 3️⃣ Race Conditions

A race condition happens when two or more processes try to access shared data at the same time, leading to unpredictable behavior or corrupted data. In this project, semaphores ensure that only one process can access shared memory at a time, preventing race conditions from happening.

### 4️⃣ Semaphore Operations

* **wait()**: This makes a process wait if the semaphore value is zero (meaning the resource is in use).
* **signal()**: This increases the semaphore value, allowing other processes to use the resource if it’s available.


## 🛠 Technologies

* 💻 **C**: I used C because it’s perfect for low-level socket programming and memory management.
* 📡 **Sockets**: TCP sockets are used for client-server communication.
* 🧠 **Shared Memory**: Enables faster and efficient inter-process communication.
* 🚦 **Semaphores**: Manage concurrent access to prevent race conditions.
* 🐳 **Docker**: Ensures the app runs anywhere consistently.

## 🔑 Key Concepts

### 1️⃣ Shared Memory

Shared memory is like a big, shared space in the system where multiple processes can read from and write to...

### 2️⃣ Semaphores

Semaphores are like traffic lights for processes...

### 3️⃣ Race Conditions

A race condition happens when two or more processes try to access shared data...

### 4️⃣ Semaphore Operations

* 🕒 **wait()**
* ✅ **signal()**

### 5️⃣ TCP/IP Sockets

The server and clients communicate via TCP sockets...

### 6️⃣ Client-Server Model

* The server listens...
* Clients send commands...
* Server processes and responds...

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

## 🐳 Docker Setup

1. **Build the Docker image**:

   ```bash
   docker build -t my_fantastic_key_value_server .
   ```

2. **Run the Docker container**:

   ```bash
   docker run -p 5678:5678 server-image
   ```

---

## ▶ Running the Server and Client

### 🖥 Server

To run the server:

```bash
./SimpleTCPKeyValueServer 5678
```

### 💬 Client

* **GET**:

  ```bash
  GET /resource
  ```
* **DELETE**:

  ```bash
  DEL /resource
  ```
* **PUT**:

  ```bash
  PUT /resource {data}
  ```

---

## 🔄 Example Workflow

1. **Start the server**
2. **Client connects**
3. **Server processes the request**

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

## 🏁 Conclusion

This project is a great learning tool for anyone interested in...

---

## ⚖ License

All rights reserved by the author, **Abolfazl Heidari**.

---

اگه دوست داشتی نسخه PDF‌ش رو هم برات بسازم. می‌خوای؟
