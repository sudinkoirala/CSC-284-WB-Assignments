# CSC-284-WB – Unit 12 Chatroom
**Instructor:** Pradeep Selvakumar  
**Student:** Sudin Koirala  

## Assignment Summary
This project extends the previous multi-client chatroom assignment by adding
support for multiple chat rooms and usernames. The goal of this unit was to
practice object-oriented design while managing shared state across multiple
threads using standard C++ tools.

When a client connects, they are automatically placed into a default **Lobby**
room. From there, users may create rooms, join existing rooms, list available
rooms, and exchange messages with other users in the same room.

---

## Supported Client Commands
- `.CREATE_ROOM <room_name>` – Creates a new room on the server  
- `.JOIN_ROOM <room_name>` – Leaves the current room and joins another  
- `.LIST_ROOMS` – Displays all active rooms  
- `.EXIT` – Disconnects from the server  

Any input that does not begin with a command is treated as a chat message and
is broadcast only to users in the same room.

---

## Design Explanation
The server is structured using three main classes: **User**, **Room**, and
**ChatServer**. Each connected client is represented by a User object, which
tracks the user’s socket, username, and current room. Rooms are responsible
for maintaining a list of users and broadcasting messages only within that
room.

The ChatServer class coordinates all connections, parses client commands, and
manages shared data structures such as the room list and active users. Mutexes
are used to protect shared resources and avoid race conditions when multiple
clients interact with the server at the same time.

This design keeps responsibilities separated and makes the code easier to
extend and debug.

---

## Compilation Instructions

**Server**
```
g++ *.cpp -pthread -o server
```

**Client**
```
g++ client.cpp -lncurses -pthread -o client
```

---

## Notes
The ncurses client intentionally focuses on basic input and output. While the
interface does not maintain a visual room list, rooms can be queried at any
time using the `.LIST_ROOMS` command, as discussed in class.
