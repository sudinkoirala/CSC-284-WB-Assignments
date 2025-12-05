# Unit 11 — Multi-Client Chatroom (CSC-284 Capstone Project)

This project implements a fully functional **multi-client chat server** and two different clients:

1. **Basic Console Client**
2. **Ncurses Terminal UI Client**

The goal is to extend networking skills from previous units and integrate them into a real-time chat application.

---

##  Folder Structure

```text
Unit11_Chatroom/
    Server/
        server.cpp
    Client/
        client.cpp
        curses_client.cpp
    README.md
```

Only this folder is graded for **Unit 11**.

---

##  Part 1 — Multi-Client Chat Server

### Features
- Accepts **multiple simultaneous clients**
- Spawns a **thread per client**
- Broadcasts messages to all other connected clients
- Removes disconnected clients cleanly
- Thread-safe shared client list using `std::mutex`
- Supports command-line argument forms:

```bash
./server
./server <ip>
./server <ip> <port>
```

Default IP: `127.0.0.1`  
Default Port: `54000`

### Build & Run

```bash
cd Unit11_Chatroom/Server
g++ -std=c++17 server.cpp -o server -pthread
./server
```

---

##  Part 2 — Basic Console Client

### Features
- Connects to the server using the same IP/port defaults
- Sends lines typed by the user
- Background `recv` thread prints incoming messages
- Supports:

```bash
./client
./client <ip>
./client <ip> <port>
```

### Build & Run

```bash
cd Unit11_Chatroom/Client
g++ -std=c++17 client.cpp -o client -pthread
./client
```

Type `/quit` to close the client cleanly.

---

##  Part 3 — Ncurses Chat UI Client

### Features
- Message window + input box UI
- Background network thread pushes messages into the ncurses message window
- Non-blocking input for smooth typing
- Clean shutdown and curses cleanup
- Uses same argument format as the basic client:

```bash
./curses_client
./curses_client <ip>
./curses_client <ip> <port>
```

### Build (requires ncurses)

```bash
cd Unit11_Chatroom/Client
g++ -std=c++17 curses_client.cpp -o curses_client -pthread -lncurses
```

### Run

```bash
./curses_client
```

---

##  Running Everything Together

Open three separate terminals:

**Terminal 1 — Server**
```bash
cd Unit11_Chatroom/Server
./server
```

**Terminal 2 — UI Client**
```bash
cd Unit11_Chatroom/Client
./curses_client
```

**Terminal 3 — Another Client**
```bash
cd Unit11_Chatroom/Client
./client
```

Messages now broadcast in real time across all connected clients.

---

##  Clean Shutdown

- Type `/quit` in either client to exit gracefully.
- The server will remove the disconnected client automatically.
- The ncurses client:
  - Ends the network thread
  - Closes the socket
  - Calls `endwin()` to restore the terminal

---

##  Notes for Assignment Requirements


The code is structured so it can be reused and extended in future capstone units.

---

##  Student & Course Info

- **Student:** Sudeen Koirala  
- **Course:** CSC-284-WB
- **Assignment:** Unit 11 — Chatroom Server and Client  
- **Instructor:** Professor Pradeep Selvakumar
