#include "LogAnalyzer.h"
#include <fstream>
#include <iostream>
#include <algorithm>

int LogAnalyzer::countOccurrences(const std::string& text, const std::string& needle) {
    if (needle.empty()) return 0;
    int count = 0;
    std::size_t pos = 0;
    while ((pos = text.find(needle, pos)) != std::string::npos) {
        ++count;
        pos += needle.size();
    }
    return count;
}

void LogAnalyzer::analyzeFile(const std::string& filename, const std::vector<std::string>& keywords) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::cout << "Processing: " << filename << std::endl;

    std::string line;
    while (std::getline(file, line)) {
        for (const auto& kw : keywords) {
            int hits = countOccurrences(line, kw);
            if (hits > 0) {
                std::lock_guard<std::mutex> lock(mtx_);
                keywordCounts_[kw] += hits;
            }
        }
    }
}

void LogAnalyzer::printSummary() const {
    std::cout << "\n--- Keyword Summary ---\n";

    const std::vector<std::string> order = { "[WARN]", "[ERROR]", "[FATAL]", "[INFO]", "[DEBUG]", "[TRACE]" };

    std::for_each(order.begin(), order.end(), [this](const std::string& k){
        int value = 0;
        {
            std::lock_guard<std::mutex> lock(mtx_);
            auto it = keywordCounts_.find(k);
            if (it != keywordCounts_.end()) value = it->second;
        }
        std::string label = k;
        label.erase(std::remove(label.begin(), label.end(), '['), label.end());
        label.erase(std::remove(label.begin(), label.end(), ']'), label.end());
        std::cout << label << ": " << value << "\n";
    });

    std::cout << "\n[\"WARN\", \"ERROR\", \"FATAL\", \"INFO\", \"DEBUG\", \"TRACE\"\n";
    std::cout << "-----------------------\n";
}

