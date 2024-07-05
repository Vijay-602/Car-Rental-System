#ifndef CAR_H
#define CAR_H

#include <string>
#include <iostream>

class Car {
private:
    std::string carID;
    std::string model;
    bool isAvailable;
    int condition; // Car condition, 0 to 100
    std::string rentalTimestamp; 
    std::string renterID; // ID of the person who rents the car

public:
    Car(const std::string& carID, const std::string& model, bool isAvailable = true, int condition = 100);

    // Getters and setters
    std::string getCarID() const;
    std::string getModel() const;
    bool getAvailability() const;
    int getCondition() const;
    std::string getRentalTimestamp() const;
    std::string getRenterID() const;
    static Car getCarDetails(const std::string& carID);
    static void setRentalTimestamp(const std::string& carID, const std::string& timestamp);
    static void listAvailableCars();

    void setAvailability(bool availability);
    void setCondition(int newCondition);
    void setRentalDetails(const std::string& renterID, const std::string& timestamp);

    // Convert car details to a string for file storage
    std::string toString() const;

    // File handling methods
    static void addCarToFile(const Car& car);
    static void updateCarInFile(const Car& car);
    static void deleteCarFromFile(const std::string& carID);
    static Car parseFromString(const std::string& line);
};

#endif // CAR_H
