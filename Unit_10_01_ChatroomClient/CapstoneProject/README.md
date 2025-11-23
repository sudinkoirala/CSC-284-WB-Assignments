# Unit10_ChatroomClient

Capstone Project - Initial Chatroom Client UI (Text-based, ncurses)

## Description

This program implements the initial user interface for a chatroom client using **ncurses** on macOS.

Features:
- Header / title bar at the top (`Advanced C++ Chat Client - Demo UI`)
- Message area that can scroll (PageUp / PageDown)
- Room list sidebar (General, Sports, Programming, Random) with highlighted selection (Up/Down arrows)
- Single-line input area at the bottom where you can type
- Press **Enter** to add your typed text as a placeholder chat message
- Press **q** to quit

## Requirements

- C++17 or later
- ncurses library installed (typically already available on macOS)

## How to Compile on macOS

From inside this folder (`Unit10_ChatroomClient`), run:

```bash
g++ -std=c++17 main.cpp -lncurses -o chat_client
```

If compilation succeeds, run:

```bash
./chat_client
```

## Basic Controls

- **Up / Down arrows**: Change the selected room in the room list
- **PageUp / PageDown**: Scroll through messages
- **Type keys**: Add characters to the input line
- **Backspace**: Delete last character in the input line
- **Enter**: Add the current input as a new message (placeholder)
- **q**: Quit the program

