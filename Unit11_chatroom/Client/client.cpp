// client.cpp (basic, non-curses)
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <cstring>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

constexpr const char* DEFAULT_IP   = "127.0.0.1";
constexpr uint16_t    DEFAULT_PORT = 54000;

// Background thread: receive messages from server and print them.
void receiveLoop(int sock, std::atomic<bool>& running)
{
    char buf[4096];

    while (running)
    {
        std::memset(buf, 0, sizeof(buf));
        ssize_t bytesRecv = recv(sock, buf, sizeof(buf), 0);
        if (bytesRecv <= 0)
        {
            std::cout << "\nDisconnected from server." << std::endl;
            running = false;
            break;
        }

        std::string msg(buf, bytesRecv);
        std::cout << "\n[Server]: " << msg << std::endl;
        std::cout << "> " << std::flush;
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
    std::thread receiver(receiveLoop, sock, std::ref(running));

    std::cout << "Connected to " << ip << ":" << port << std::endl;
    std::cout << "Type messages and press Enter to send. Type /quit to exit." << std::endl;

    std::string input;
    std::cout << "> " << std::flush;
    while (running && std::getline(std::cin, input))
    {
        if (input == "/quit")
        {
            running = false;
            break;
        }

        if (!input.empty())
        {
            send(sock, input.c_str(), input.size(), 0);
        }

        std::cout << "> " << std::flush;
    }

    running = false;
    shutdown(sock, SHUT_RDWR);
    close(sock);

    if (receiver.joinable())
        receiver.join();

    return 0;
}
