#include "Fleet.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

Fleet::Fleet() {
    std::cout << "[Fleet ctor] New Fleet created\n";
}

Fleet::~Fleet() {
    std::cout << "[Fleet dtor] Deleting all vehicles in Fleet\n";
    for (Vehicle* v : vehicles) {
        delete v; // virtual destructor chain will run
    }
    vehicles.clear();
}

void Fleet::addVehicle(Vehicle* v) {
    if (!v) throw std::invalid_argument("Cannot add null vehicle");
    vehicles.push_back(v);
}

void Fleet::displayAllVehicles() const {
    std::cout << "\n--- Fleet Vehicles ---\n";
    for (const Vehicle* v : vehicles) {
        v->displayInfo(); // polymorphic call
    }
}

double Fleet::getAverageEfficiency() const {
    if (vehicles.empty()) return 0.0;
    double sum = 0.0;
    for (const Vehicle* v : vehicles) {
        sum += v->getFuelEfficiency(); // polymorphic call
    }
    return sum / vehicles.size();
}

