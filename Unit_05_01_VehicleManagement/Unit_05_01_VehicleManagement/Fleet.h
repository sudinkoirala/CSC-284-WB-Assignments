#ifndef FLEET_H
#define FLEET_H

#include <vector>
#include "Vehicle.h"

class Fleet {
private:
    std::vector<Vehicle*> vehicles;

public:
    Fleet();
    ~Fleet(); // must delete owned Vehicle*

    void addVehicle(Vehicle* v);
    void displayAllVehicles() const;
    double getAverageEfficiency() const;

    // Prevent copy to avoid double delete
    Fleet(const Fleet&) = delete;
    Fleet& operator=(const Fleet&) = delete;
};

#endif

