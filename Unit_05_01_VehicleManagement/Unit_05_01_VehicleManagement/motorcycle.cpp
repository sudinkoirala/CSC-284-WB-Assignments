#include "motorcycle.h"
#include <iostream>
#include <iomanip>

Motorcycle::Motorcycle()
: Vehicle(), hasSidecar(false) {
    std::cout << "[Motorcycle ctor] Default Motorcycle created\n";
}

Motorcycle::Motorcycle(const std::string& mk, const std::string& md, int y, double m, bool sidecar)
: Vehicle(mk, md, y, m), hasSidecar(sidecar) {
    std::cout << "[Motorcycle ctor] Motorcycle created\n";
}

Motorcycle::~Motorcycle() {
    std::cout << "[Motorcycle dtor] Destroying Motorcycle: " << year << " " << make << " " << model << "\n";
}

bool Motorcycle::getHasSidecar() const { return hasSidecar; }
void Motorcycle::setHasSidecar(bool s) { hasSidecar = s; }

double Motorcycle::getFuelEfficiency() const {
    double base = 30.0; // km/l baseline
    if (hasSidecar) base -= 5.0;
    base -= (mileage / 100000.0) * 1.0;
    if (base < 10.0) base = 10.0;
    return base;
}

void Motorcycle::displayInfo() const {
    Vehicle::displayInfo();
    std::cout << "Type: Motorcycle | Sidecar: " << (hasSidecar ? "Yes" : "No") << "\n";
    std::cout << "Fuel Efficiency: " << std::fixed << std::setprecision(2)
              << getFuelEfficiency() << " km/l\n\n";
}

