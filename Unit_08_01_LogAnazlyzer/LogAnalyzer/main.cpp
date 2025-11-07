#include "LogAnalyzer.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <log_directory>\n";
        return 1;
    }

    std::string folderPath = argv[1];
    LogAnalyzer analyzer;

    // Exact keywords required by assignment
    std::vector<std::string> keywords = {"[WARN]", "[ERROR]", "[FATAL]", "[INFO]", "[DEBUG]", "[TRACE]"};

    std::vector<std::thread> threads;
    std::cout << "Analyzing folder: " << folderPath << "\n\n";

    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".log") {
                const std::string filename = entry.path().string();
                threads.emplace_back([&analyzer, &keywords, filename](){
                    analyzer.analyzeFile(filename, keywords);
                });
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
        return 2;
    }

    for (auto& t : threads) t.join();

    analyzer.printSummary();

    std::cout << "\nAnalysis complete. Processed " << threads.size() << " files.\n";
    return 0;
}

