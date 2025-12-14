// Basic ncurses chat client
#include <ncurses.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <cstring>

// receives messages from server
void receiveLoop(int sock) {
    char buffer[1024];
    while (true) {
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        printw("%s", buffer);
        refresh();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server.sin_addr);

    connect(sock, (sockaddr*)&server, sizeof(server));

    // send username if provided
    if (argc >= 4)
        send(sock, argv[3], strlen(argv[3]), 0);
    else
        send(sock, "\n", 1, 0);

    initscr();
    cbreak();
    noecho();

    std::thread(receiveLoop, sock).detach();

    char input[512];
    while (true) {
        getstr(input);
        send(sock, input, strlen(input), 0);
        send(sock, "\n", 1, 0);
        if (strcmp(input, ".EXIT") == 0) break;
    }

    endwin();
    close(sock);
    return 0;
}
