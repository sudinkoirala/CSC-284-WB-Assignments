#include <iostream>
#include <iomanip>
#include "Fleet.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"

int main() {
    std::cout << "Vehicle Management System\n";
    std::cout << "--------------------------\n\n";

    Fleet fleet;

    // Create vehicles dynamically
    Vehicle* v1 = new Car("Toyota", "Corolla", 2020, 20000, 4, false);
    Vehicle* v2 = new Truck("Volvo", "FH16", 2018, 80000, 18);
    Vehicle* v3 = new Motorcycle("Honda", "CBR600", 2021, 5000, false);
    Vehicle* v4 = new Car("Tesla", "Model 3", 2022, 15000, 4, true);

    // Add to fleet
    fleet.addVehicle(v1);
    fleet.addVehicle(v2);
    fleet.addVehicle(v3);
    fleet.addVehicle(v4);

    // Display all
    fleet.displayAllVehicles();

    // Show totals
    std::cout << "Total vehicles: " << Vehicle::getVehicleCount() << "\n";
    std::cout << "Average fuel efficiency: " << std::fixed << std::setprecision(2)
              << fleet.getAverageEfficiency() << " km/l\n\n";

    std::cout << "Program ending... destructors will now be called automatically.\n";
    return 0;
}

