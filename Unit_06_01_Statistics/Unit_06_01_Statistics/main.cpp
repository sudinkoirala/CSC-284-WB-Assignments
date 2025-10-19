#include <iostream>
#include "Statistics.h"

int main() {
    try {
        // Test free functions
        std::vector<int> ints = {10, 20, 30, -5, 42};
        std::vector<double> doubles = {3.14, 2.71, 4.5, -1.0, 10.0};

        std::cout << "Using free functions:\n";
        std::cout << "Ints    -> Min: " << getMin(ints)
                  << ", Max: " << getMax(ints)
                  << ", Avg: " << getAverage(ints) << "\n";

        std::cout << "Doubles -> Min: " << getMin(doubles)
                  << ", Max: " << getMax(doubles)
                  << ", Avg: " << getAverage(doubles) << "\n\n";

        // Test class template
        Statistics<int> intStats;
        intStats.addValue(10);
        intStats.addValue(20);
        intStats.addValue(30);

        Statistics<double> doubleStats;
        doubleStats.addValue(3.14);
        doubleStats.addValue(2.71);
        doubleStats.addValue(4.5);

        std::cout << "Using class template:\n";
        std::cout << "Int Stats: Min = " << intStats.getMin()
                  << ", Max = " << intStats.getMax()
                  << ", Avg = " << intStats.getAverage() << "\n";

        std::cout << "Double Stats: Min = " << doubleStats.getMin()
                  << ", Max = " << doubleStats.getMax()
                  << ", Avg = " << doubleStats.getAverage() << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}

