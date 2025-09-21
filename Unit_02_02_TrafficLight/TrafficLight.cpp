#include <iostream>
#include <array>
#include <string>
#include <limits>

/**
 * Models and simulates a traffic light cycling:
 * Red -> Green -> Yellow -> Red -> ...
 */
class TrafficLightSimulator {
public:
    // Light colors in the required order.
    enum class LightColor { Red = 0, Green = 1, Yellow = 2 };

    TrafficLightSimulator()
        : current_color_(LightColor::Red) {}  // Start at Red

    /**
     * Run the simulation for a given number of *cycles*.
     * One cycle = Red, Green, Yellow (3 steps).
     * Prints the color at each step.
     */
    void runCycles(int number_of_cycles) {
        const int steps = number_of_cycles * static_cast<int>(kStates.size());
        for (int i = 0; i < steps; ++i) {
            printCurrentColor();
            advance();
        }
    }

private:
    // Fixed state names in required order.
    static constexpr std::array<const char*, 3> kStates{"Red", "Green", "Yellow"};
    LightColor current_color_;

    void printCurrentColor() const {
        std::cout << kStates[static_cast<int>(current_color_)] << '\n';
    }

    // Move to the next color in the cycle.
    void advance() {
        int idx = static_cast<int>(current_color_);
        idx = (idx + 1) % static_cast<int>(kStates.size());
        current_color_ = static_cast<LightColor>(idx);
    }
};

int main() {
    std::cout << "Enter number of cycles to simulate (1 cycle = Red, Green, Yellow): ";

    int cycles;
    while (!(std::cin >> cycles) || cycles < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a non-negative integer for cycles: ";
    }

    TrafficLightSimulator simulator;
    simulator.runCycles(cycles);

    return 0;
}

