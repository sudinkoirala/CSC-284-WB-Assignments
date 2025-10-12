#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
private:
    int numDoors;
    bool isElectric;

    static bool isValidDoors(int d);

public:
    Car();
    Car(const std::string& make, const std::string& model, int year, double mileage,
        int numDoors, bool isElectric);

    ~Car() override;

    int getNumDoors() const;
    bool getIsElectric() const;

    void setNumDoors(int d);
    void setIsElectric(bool e);

    void displayInfo() const override;
    double getFuelEfficiency() const override;
};

#endif

