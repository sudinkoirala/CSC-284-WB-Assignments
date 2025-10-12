#include "car.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

bool Car::isValidDoors(int d) { return d >= 1 && d <= 6; }

Car::Car()
: Vehicle(), numDoors(4), isElectric(false) {
    std::cout << "[Car ctor] Default Car created\n";
}

Car::Car(const std::string& mk, const std::string& md, int y, double m,
         int doors, bool electric)
: Vehicle(mk, md, y, m), numDoors(4), isElectric(false) {
    setNumDoors(doors);
    setIsElectric(electric);
    std::cout << "[Car ctor] Car created\n";
}

Car::~Car() {
    std::cout << "[Car dtor] Destroying Car: " << year << " " << make << " " << model << "\n";
}

int Car::getNumDoors() const { return numDoors; }
bool Car::getIsElectric() const { return isElectric; }

void Car::setNumDoors(int d) {
    if (!isValidDoors(d)) throw std::invalid_argument("Doors must be between 1 and 6");
    numDoors = d;
}

void Car::setIsElectric(bool e) { isElectric = e; }

double Car::getFuelEfficiency() const {
    // Simple sample model
    if (isElectric) return 0.0; // using sample output convention
    double base = 15.0; // km/l
    // light tweak: fewer doors slightly better, more mileage slightly worse
    base += (4 - numDoors) * 0.5;
    base -= (mileage / 100000.0) * 1.0;
    if (base < 5.0) base = 5.0;
    return base;
}

void Car::displayInfo() const {
    Vehicle::displayInfo();
    std::cout << "Type: Car | Doors: " << numDoors
              << " | Electric: " << (isElectric ? "Yes" : "No") << "\n";
    std::cout << "Fuel Efficiency: " << std::fixed << std::setprecision(2)
              << getFuelEfficiency() << " km/l\n\n";
}

