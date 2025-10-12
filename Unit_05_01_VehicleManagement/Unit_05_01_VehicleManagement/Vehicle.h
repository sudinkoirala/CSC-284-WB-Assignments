#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>

class Vehicle {
protected:
    std::string make;
    std::string model;
    int year;
    double mileage;

    // Validation helpers
    static bool isValidYear(int y);
    static bool isValidMileage(double m);

public:
    static int vehicleCount;

    // Constructors
    Vehicle();
    Vehicle(const std::string& make, const std::string& model, int year, double mileage);

    // Virtual destructor
    virtual ~Vehicle();

    // Accessors
    std::string getMake() const;
    std::string getModel() const;
    int getYear() const;
    double getMileage() const;

    // Mutators with validation
    void setMake(const std::string& mk);
    void setModel(const std::string& md);
    void setYear(int y);
    void setMileage(double m);

    // Static accessor
    static int getVehicleCount();

    // Polymorphic interface
    virtual void displayInfo() const;
    virtual double getFuelEfficiency() const = 0;
};

#endif

