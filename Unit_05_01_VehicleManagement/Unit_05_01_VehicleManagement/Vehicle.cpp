#include "Vehicle.h"
#include <iomanip>
#include <stdexcept>

int Vehicle::vehicleCount = 0;

bool Vehicle::isValidYear(int y) {
    return y >= 1886 && y <= 2100;
}

bool Vehicle::isValidMileage(double m) {
    return m >= 0.0;
}

Vehicle::Vehicle()
: make("Unknown"), model("Unknown"), year(2000), mileage(0.0) {
    ++vehicleCount;
    std::cout << "[Vehicle ctor] Created base Vehicle\n";
}

Vehicle::Vehicle(const std::string& mk, const std::string& md, int y, double m)
: make(mk), model(md), year(2000), mileage(0.0) {
    setYear(y);
    setMileage(m);
    ++vehicleCount;
    std::cout << "[Vehicle ctor] Created " << year << " " << make << " " << model << "\n";
}

Vehicle::~Vehicle() {
    --vehicleCount;
    std::cout << "[Vehicle dtor] Destroying Vehicle: " << year << " " << make << " " << model << "\n";
}

std::string Vehicle::getMake() const { return make; }
std::string Vehicle::getModel() const { return model; }
int Vehicle::getYear() const { return year; }
double Vehicle::getMileage() const { return mileage; }

void Vehicle::setMake(const std::string& mk) { make = mk; }
void Vehicle::setModel(const std::string& md) { model = md; }

void Vehicle::setYear(int y) {
    if (!isValidYear(y)) throw std::invalid_argument("Year must be in range 1886 to 2100");
    year = y;
}

void Vehicle::setMileage(double m) {
    if (!isValidMileage(m)) throw std::invalid_argument("Mileage cannot be negative");
    mileage = m;
}

int Vehicle::getVehicleCount() { return vehicleCount; }

void Vehicle::displayInfo() const {
    std::cout << year << " " << make << " " << model << " | Mileage: "
              << std::fixed << std::setprecision(0) << mileage << " km\n";
}

