# 🌐HTTP Server in C (WinSock2 - Windows)

This is a HTTP server written in C using Windows sockets (Winsock2). It accepts client connections and responds with a static HTML page.
---

## 🔧 Requirements

- Windows OS
- [MSYS2](https://www.msys2.org/) installed

## 🛠 Build Instructions

1. Open the **MSYS2 MinGW 64-bit shell**.
2. Make sure GCC and required tools are installed:
   ```
   pacman -Syu
   pacman -S mingw-w64-x86_64-gcc
   ```

3. Clone this repository (if not already):

   ```
   git clone https://github.com/your-username/your-repo-name.git
   cd your-repo-name
   ```
4. Compile the server:

   ```
   gcc test.c Server.c HTTPRequest.c -o server.exe -lws2_32
   ```

## 🚀 Run the Server

```
./server.exe
```

You should see:

```
====== WAITING FOR CONNECTION ======
```

## 📬 Test with Python

You can test the server using the Python script:


## 📄 Files

* `Server.c` / `Server.h` – Socket setup and listener
* `HTTPRequest.c` – Basic HTTP parsing (optional)
* `test.c` – Entry point

---


