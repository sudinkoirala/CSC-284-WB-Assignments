#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"

class Motorcycle : public Vehicle {
private:
    bool hasSidecar;

public:
    Motorcycle();
    Motorcycle(const std::string& make, const std::string& model, int year, double mileage,
               bool hasSidecar);

    ~Motorcycle() override;

    bool getHasSidecar() const;
    void setHasSidecar(bool s);

    void displayInfo() const override;
    double getFuelEfficiency() const override;
};

#endif

