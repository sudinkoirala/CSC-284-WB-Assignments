#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle {
private:
    double loadCapacity; // in tons

    static bool isValidCapacity(double c);

public:
    Truck();
    Truck(const std::string& make, const std::string& model, int year, double mileage,
          double loadCapacity);

    ~Truck() override;

    double getLoadCapacity() const;
    void setLoadCapacity(double c);

    void displayInfo() const override;
    double getFuelEfficiency() const override;
};

#endif

