// curses_client.cpp
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include <cstring>
#include <cstdlib>
#include <chrono>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <ncurses.h>

constexpr const char* DEFAULT_IP   = "127.0.0.1";
constexpr uint16_t    DEFAULT_PORT = 54000;

// Thread-safe queue for messages coming from the network thread into the UI.
std::queue<std::string> g_incomingMessages;
std::mutex g_queueMutex;

// Background thread: receive network messages and push into queue.
void networkReceiveLoop(int sock, std::atomic<bool>& running)
{
    char buf[4096];

    while (running)
    {
        std::memset(buf, 0, sizeof(buf));
        ssize_t bytesRecv = recv(sock, buf, sizeof(buf), 0);
        if (bytesRecv <= 0)
        {
            // Server closed or error
            {
                std::lock_guard<std::mutex> lock(g_queueMutex);
                g_incomingMessages.push("*** Disconnected from server ***");
            }
            running = false;
            break;
        }

        std::string msg(buf, bytesRecv);
        {
            std::lock_guard<std::mutex> lock(g_queueMutex);
            g_incomingMessages.push(msg);
        }
    }
}

int main(int argc, char* argv[])
{
    std::string ip = DEFAULT_IP;
    uint16_t port = DEFAULT_PORT;

    if (argc >= 2)
    {
        ip = argv[1];
    }
    if (argc >= 3)
    {
        port = static_cast<uint16_t>(std::stoi(argv[2]));
    }

    // --- Create and connect socket ---
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        std::cerr << "Can't create socket" << std::endl;
        return 1;
    }

    sockaddr_in hint;
    std::memset(&hint, 0, sizeof(hint));
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

    if (connect(sock, (sockaddr*)&hint, sizeof(hint)) == -1)
    {
        std::cerr << "Can't connect to server" << std::endl;
        close(sock);
        return 2;
    }

    std::atomic<bool> running(true);
    std::thread receiver(networkReceiveLoop, sock, std::ref(running));

    // --- Initialize curses UI ---
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int height, width;
    getmaxyx(stdscr, height, width);

    int inputHeight = 3;
    int msgHeight   = height - inputHeight;

    WINDOW* msgWin   = newwin(msgHeight, width, 0, 0);
    WINDOW* inputWin = newwin(inputHeight, width, msgHeight, 0);

    scrollok(msgWin, TRUE);
    box(msgWin, 0, 0);
    box(inputWin, 0, 0);

    mvwprintw(msgWin, 0, 2, " Messages ");
    mvwprintw(inputWin, 0, 2, " Input (/quit to exit) ");

    wrefresh(msgWin);
    wrefresh(inputWin);

    // Non-blocking input so UI can also process messages
    nodelay(inputWin, TRUE);

    std::string currentInput;
    int ch;

    while (running)
    {
        // --- Handle incoming messages from server ---
        {
            std::lock_guard<std::mutex> lock(g_queueMutex);
            while (!g_incomingMessages.empty())
            {
                const std::string& line = g_incomingMessages.front();
                // Print inside the message window's border and let it scroll
                wmove(msgWin, getmaxy(msgWin) - 2, 1);
                wprintw(msgWin, "%s\n", line.c_str());
                box(msgWin, 0, 0);
                mvwprintw(msgWin, 0, 2, " Messages ");
                wrefresh(msgWin);

                g_incomingMessages.pop();
            }
        }

        // --- Handle user input ---
        ch = wgetch(inputWin);
        if (ch != ERR)
        {
            if (ch == '\n' || ch == '\r')
            {
                // Enter pressed – send message
                if (!currentInput.empty())
                {
                    if (currentInput == "/quit")
                    {
                        running = false;
                        break;
                    }

                    send(sock, currentInput.c_str(), currentInput.size(), 0);
                    currentInput.clear();
                }

                // Clear input line
                werase(inputWin);
                box(inputWin, 0, 0);
                mvwprintw(inputWin, 0, 2, " Input (/quit to exit) ");
                wrefresh(inputWin);
            }
            else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
            {
                if (!currentInput.empty())
                    currentInput.pop_back();

                // Redraw input line
                werase(inputWin);
                box(inputWin, 0, 0);
                mvwprintw(inputWin, 0, 2, " Input (/quit to exit) ");
                mvwprintw(inputWin, 1, 1, "%s", currentInput.c_str());
                wrefresh(inputWin);
            }
            else if (isprint(ch))
            {
                currentInput.push_back(static_cast<char>(ch));
                mvwprintw(inputWin, 1, 1, "%s", currentInput.c_str());
                wrefresh(inputWin);
            }
        }

        // Tiny sleep to avoid maxing CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // --- Clean shutdown ---
    running = false;
    shutdown(sock, SHUT_RDWR);
    close(sock);

    if (receiver.joinable())
        receiver.join();

    delwin(msgWin);
    delwin(inputWin);
    endwin();

    return 0;
}
