#include <chrono>
#include <csignal>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

static volatile std::sig_atomic_t g_keepRunning = 1;

void handleSigInt(int) {
    g_keepRunning = 0;
}

int main(int argc, char* argv[]) {
    std::signal(SIGINT, handleSigInt);

    const size_t CHUNK_SIZE = 1024 * 1024; // 1 MB
    bool leakMode = false;

    // Usage:
    //   ./MemoryLeakDemo leak   -> intentionally leak
    //   ./MemoryLeakDemo        -> fixed version
    if (argc > 1 && std::string(argv[1]) == "leak") {
        leakMode = true;
    }

    std::vector<char*> keepAlive; // used only in leak mode
    keepAlive.reserve(1024);

    std::size_t seconds = 0;
    std::cout << (leakMode ? "[LEAK MODE]\n" : "[FIXED MODE]\n");
    std::cout << "Allocating about 1 MB every second. Press Ctrl+C to stop.\n";

    while (g_keepRunning) {
        if (leakMode) {
            // Intentionally leak
            char* chunk = new char[CHUNK_SIZE];
            std::memset(chunk, 0, CHUNK_SIZE);
            keepAlive.push_back(chunk); // never freed while running
        } else {
            // Fixed: allocate then free
            char* chunk = new char[CHUNK_SIZE];
            std::memset(chunk, 0, CHUNK_SIZE);

            // Important: comment out this line to reproduce the leak
            delete[] chunk; // proper cleanup
        }

        ++seconds;
        std::cout << "Seconds: " << seconds
                  << " | Total allocated so far: ~" << seconds << " MB"
                  << (leakMode ? " (held)" : " (freed)") << std::endl;

        std::this_thread::sleep_for(1s);
    }

    // Cleanup in case you stop leak mode
    for (char* p : keepAlive) {
        delete[] p;
    }

    std::cout << "Exiting.\n";
    return 0;
}

