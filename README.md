# C Web Server with Interactive API

<img width="1158" height="635" alt="image" src="https://github.com/user-attachments/assets/f03b554b-5206-4e00-a85f-fa306b411cec" />

<img width="1050" height="688" alt="image" src="https://github.com/user-attachments/assets/b6ad4122-94e9-453c-a669-4d9a951c3d0f" />

<img width="1200" height="861" alt="image" src="https://github.com/user-attachments/assets/be37d594-6dca-4a6f-99be-29a564d89ae3" />




A fully functional HTTP web server written in C using Winsock2. This project demonstrates low-level socket programming, manual HTTP parsing, routing, JSON response building, and integration of custom data structures (Dictionary + Binary Search Tree).

---

## Project Overview

This project implements a simple but structured HTTP server without using external frameworks. It handles TCP connections, parses HTTP requests, routes them to appropriate handlers, and returns HTML or JSON responses. Hey I tried my best.

The server also includes an interactive dashboard and a Python-based client for testing API endpoints.

---

## Architecture Overview

### System Design
```
┌─────────────────────────────────────────────────────┐
│                  MAIN APPLICATION                    │
│                    (test.c)                          │
│                                                       │
│  1. Server initialization                            │
│  2. Accept incoming connections                      │
│  3. Parse HTTP requests                              │
│  4. Route to handlers                                │
└─────────────────────────────────────────────────────┘
                          ↓
        ┌───────────────────────────────────┐
        │     HTTP REQUEST PARSER            │
        │                                    │
        │ parse_request_line()              │
        │ - Extract: method, path, query    │
        │ - String parsing with sscanf()    │
        └───────────────────────────────────┘
                          ↓
        ┌───────────────────────────────────┐
        │     ROUTE DISPATCHER               │
        │                                    │
        │ if (path == "/") → dashboard      │
        │ if (path == "/api/status") → ...  │
        │ if (path == "/api/time") → ...    │
        └───────────────────────────────────┘
                          ↓
        ┌───────────────────────────────────┐
        │     API HANDLERS                   │
        │     (HTTPHandler.c)                │
        │                                    │
        │ handle_dashboard()                 │
        │ handle_api_status()                │
        │ handle_api_time()                  │
        │ handle_api_store()                 │
        │ handle_api_retrieve()              │
        │ handle_api_stats()                 │
        │ handle_api_bst()                   │
        │ handle_not_found()                 │
        └───────────────────────────────────┘
                          ↓
        ┌───────────────────────────────────┐
        │  DATA STRUCTURES                   │
        │  (DataStructures/)                 │
        │                                    │
        │  Dictionary + BinarySearchTree    │
        │  - O(log n) lookups               │
        │  - Key-value storage              │
        └───────────────────────────────────┘
                          ↓
        ┌───────────────────────────────────┐
        │  RESPONSE BUILDERS                 │
        │                                    │
        │ send_json_response()              │
        │ send_html_response()              │
        │ - Build HTTP headers              │
        │ - Format JSON                     │
        │ - Send to client                  │
        └───────────────────────────────────┘
                          ↓
        ┌───────────────────────────────────┐
        │  LOW-LEVEL SOCKETS                │
        │  (Server.c)                       │
        │                                    │
        │ socket() → create socket          │
        │ bind() → bind to address          │
        │ listen() → wait for connections  │
        │ accept() → accept client          │
        │ recv() → receive data             │
        │ send() → send response            │
        │ closesocket() → cleanup           │
        └───────────────────────────────────┘
```

### Data Flow
```
                HTTP Client (Browser/Python)
                          ↓
          ┌───────────────────────────────────┐
          │ HTTP Request (TCP connection)     │
          │ GET /api/status HTTP/1.1          │
          │ Host: localhost:8080              │
          └───────────────────────────────────┘
                          ↓
        ┌─────────────────────────────────────┐
        │ Server accepts & parses request     │
        │ (test.c: parse_request_line)        │
        └─────────────────────────────────────┘
                          ↓
        ┌─────────────────────────────────────┐
        │ Router dispatches to handler        │
        │ Path="/api/status" → handle_api_... │
        └─────────────────────────────────────┘
                          ↓
        ┌─────────────────────────────────────┐
        │ Handler builds JSON response        │
        │ (HTTPHandler.c)                     │
        │ {"status":"running",...}            │
        └─────────────────────────────────────┘
                          ↓
        ┌─────────────────────────────────────┐
        │ Response sent to client             │
        │ HTTP 200 OK + JSON body             │
        └─────────────────────────────────────┘
                          ↓
            JSON received in browser/client
            Dashboard updates or Python parses

```

---


### Layers

1. Socket Layer (Server.c)

   * socket()
   * bind()
   * listen()
   * accept()
   * recv() / send()
   * closesocket()

2. HTTP Parsing (test.c)

   * Parses request line (METHOD PATH HTTP/VERSION)
   * Extracts query parameters
   * Routes request based on path

3. HTTP Handlers (HTTPHandler.c)

   * Builds JSON responses
   * Handles dashboard rendering
   * Tracks server statistics

4. Data Structures

   * Dictionary abstraction
   * Binary Search Tree for efficient lookups

---

## Features

* Custom HTTP server built in C
* Winsock2-based networking
* Manual request parsing
* REST-style API endpoints
* JSON response formatting
* Interactive browser dashboard
* Key-value storage using BST
* Python test client

---

## API Endpoints

| Endpoint      | Description            |
| ------------- | ---------------------- |
| /             | Dashboard UI           |
| /api/status   | Server status & uptime |
| /api/time     | Current system time    |
| /api/store    | Store key-value pair   |
| /api/retrieve | Retrieve stored value  |
| /api/stats    | Runtime metrics        |
| /api/bst      | BST debug info         |

---

## Build Instructions

### Requirements

* Windows 10/11
* GCC / MinGW
* Python 3.6+

### Compile

```
gcc test.c Server.c HTTPHandler.c \
DataStructures/Common/Node.c \
DataStructures/Dictionary/Dictionary.c \
DataStructures/Dictionary/Entry.c \
DataStructures/Trees/BinarySearchTree.c \
-o testserver.exe -lws2_32
```

### Run Server

```
.\testserver.exe
```

Open in browser:

```
http://localhost:8080
```

---

## Python Client

```
python client.py demo
```

Or interactive mode:

```
python client.py
```

---

## Technical Highlights

* Proper Winsock error handling using WSAGetLastError()
* Correct use of SOCKET_ERROR checks
* SO_REUSEADDR implementation
* Fixed uninitialized pointer dereference issues
* Resolved signature mismatches and duplicate definitions
* Clean separation of concerns

---

## Debugging & Fixes

Major issues resolved:

* Function signature mismatch in Dictionary.search()
* Uninitialized pointer in BinarySearchTree
* Duplicate destructor definition
* Port binding errors (10048, 10013)
* Incorrect error handling with perror()
* Type casting warnings for sockaddr_in

All compilation errors, runtime crashes, and warnings have been resolved.

---

## Future Improvements

* Multi-threaded or async support
* HTTPS via OpenSSL
* Improved HTTP/1.1 compliance
* Input validation and security hardening
* Logging & observability

---

