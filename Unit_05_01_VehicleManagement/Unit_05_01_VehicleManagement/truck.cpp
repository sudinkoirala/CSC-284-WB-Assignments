#include "truck.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

bool Truck::isValidCapacity(double c) { return c >= 0.0 && c <= 100.0; }

Truck::Truck()
: Vehicle(), loadCapacity(1.0) {
    std::cout << "[Truck ctor] Default Truck created\n";
}

Truck::Truck(const std::string& mk, const std::string& md, int y, double m, double cap)
: Vehicle(mk, md, y, m), loadCapacity(1.0) {
    setLoadCapacity(cap);
    std::cout << "[Truck ctor] Truck created\n";
}

Truck::~Truck() {
    std::cout << "[Truck dtor] Destroying Truck: " << year << " " << make << " " << model << "\n";
}

double Truck::getLoadCapacity() const { return loadCapacity; }

void Truck::setLoadCapacity(double c) {
    if (!isValidCapacity(c)) throw std::invalid_argument("Load capacity must be 0 to 100 tons");
    loadCapacity = c;
}

double Truck::getFuelEfficiency() const {
    // Simple sample model for trucks
    double base = 8.0; // km/l baseline
    base -= loadCapacity * 0.2;
    base -= (mileage / 100000.0) * 1.5;
    if (base < 2.0) base = 2.0;
    return base;
}

void Truck::displayInfo() const {
    Vehicle::displayInfo();
    std::cout << "Type: Truck | Load Capacity: " << std::fixed << std::setprecision(0)
              << loadCapacity << " tons\n";
    std::cout << "Fuel Efficiency: " << std::fixed << std::setprecision(2)
              << getFuelEfficiency() << " km/l\n\n";
}

