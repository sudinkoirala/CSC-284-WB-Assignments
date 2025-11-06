#ifndef LOG_ANALYZER_H
#define LOG_ANALYZER_H

#include <string>
#include <vector>
#include <map>
#include <mutex>

class LogAnalyzer {
public:
    void analyzeFile(const std::string& filename, const std::vector<std::string>& keywords);
    void printSummary() const;

private:
    static int countOccurrences(const std::string& text, const std::string& needle);

    mutable std::mutex mtx_;
    std::map<std::string, int> keywordCounts_;
};

#endif // LOG_ANALYZER_H

