// server.cpp
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cstring>   // memset
#include <cstdlib>   // std::stoi

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  // close

// Defaults
constexpr const char* DEFAULT_IP   = "127.0.0.1";
constexpr uint16_t    DEFAULT_PORT = 54000;

std::vector<int> g_clients;
std::mutex g_clientsMutex;

// Broadcast a message from one client to all other connected clients.
void broadcastMessage(const std::string& msg, int senderSocket)
{
    std::lock_guard<std::mutex> lock(g_clientsMutex);

    for (int clientSock : g_clients)
    {
        if (clientSock == senderSocket) continue; // Don't echo back to sender
        ssize_t sent = send(clientSock, msg.c_str(), msg.size(), 0);
        if (sent < 0)
        {
            // Optional: log or handle send errors
        }
    }
}

// Per-client handler thread function.
void handleClient(int clientSocket)
{
    char buf[4096];

    while (true)
    {
        std::memset(buf, 0, sizeof(buf));
        ssize_t bytesRecv = recv(clientSocket, buf, sizeof(buf), 0);
        if (bytesRecv <= 0)
        {
            // Either client disconnected or error
            break;
        }

        std::string msg(buf, bytesRecv);
        broadcastMessage(msg, clientSocket);
    }

    // Cleanup: remove client from list and close socket
    {
        std::lock_guard<std::mutex> lock(g_clientsMutex);
        auto it = std::find(g_clients.begin(), g_clients.end(), clientSocket);
        if (it != g_clients.end())
        {
            g_clients.erase(it);
        }
    }

    close(clientSocket);
    std::cout << "Client disconnected: socket " << clientSocket << std::endl;
}

int main(int argc, char* argv[])
{
    std::string ip = DEFAULT_IP;
    uint16_t port = DEFAULT_PORT;

    if (argc >= 2)
    {
        ip = argv[1];  // Per assignment: no need to validate IP format
    }
    if (argc >= 3)
    {
        port = static_cast<uint16_t>(std::stoi(argv[2]));
    }

    std::cout << "Starting server on " << ip << ":" << port << std::endl;

    // Create listening socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cerr << "Can't create a socket" << std::endl;
        return 1;
    }

    // Allow quick reuse of port (useful during development)
    int opt = 1;
    setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in hint;
    std::memset(&hint, 0, sizeof(hint));
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)
    {
        std::cerr << "Can't bind to IP/port" << std::endl;
        close(listening);
        return 2;
    }

    if (listen(listening, SOMAXCONN) == -1)
    {
        std::cerr << "Can't listen" << std::endl;
        close(listening);
        return 3;
    }

    std::cout << "Server listening..." << std::endl;

    // Main accept loop – spawn a thread per client
    while (true)
    {
        sockaddr_in client;
        socklen_t clientSize = sizeof(client);
        int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
        if (clientSocket == -1)
        {
            std::cerr << "Problem with client connecting." << std::endl;
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(g_clientsMutex);
            g_clients.push_back(clientSocket);
        }

        std::cout << "New client connected: socket " << clientSocket << std::endl;

        std::thread t(handleClient, clientSocket);
        t.detach(); // Each client thread runs independently
    }

    // Normally unreachable in this assignment
    close(listening);
    return 0;
}
