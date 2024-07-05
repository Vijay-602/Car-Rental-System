#include "Car.h"
#include <fstream>
#include <sstream>
#include <vector>

std::string Car::getCarID() const {
    return carID;
}

std::string Car::getModel() const {
    return model;
}

bool Car::getAvailability() const {
    return isAvailable;
}

int Car::getCondition() const {
    return condition;
}

std::string Car::getRentalTimestamp() const {
    return rentalTimestamp;
}

std::string Car::getRenterID() const {
    return renterID;
}

void Car::setAvailability(bool availability) {
    isAvailable = availability;
}

void Car::setCondition(int newCondition) {
    condition = newCondition;
}


Car::Car(const std::string& carID, const std::string& model, bool isAvailable, int condition)
    : carID(carID), model(model), isAvailable(isAvailable), condition(condition) {}

// Implement getters and setters...

void Car::setRentalDetails(const std::string& renterID, const std::string& timestamp) {
    this->renterID = renterID;
    rentalTimestamp = timestamp;
}

std::string Car::toString() const {
    std::stringstream ss;
    ss << carID << "," << model << "," << isAvailable << "," << condition << "," 
       << rentalTimestamp << "," << renterID;
    return ss.str();
}

void Car::addCarToFile(const Car& car) {
    std::ofstream file("cars.txt", std::ios::app);
    if (file.is_open()) {
        file << car.toString() << std::endl;
        file.close();
    }
}

void Car::listAvailableCars() {
    std::ifstream file("cars.txt");
    std::string line;
    bool availableCarsFound = false;

    while (std::getline(file, line)) {
        Car car = Car::parseFromString(line);
        if (car.getAvailability()) {
            std::cout << "Car ID: " << car.getCarID() << ", Model: " << car.getModel() << std::endl;
            availableCarsFound = true;
        }
    }

    if (!availableCarsFound) {
        std::cout << "No available cars at the moment." << std::endl;
    }
}


void Car::updateCarInFile(const Car& car) {
    std::vector<Car> cars;
    std::ifstream inFile("cars.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        Car existingCar = parseFromString(line);
        if (existingCar.getCarID() != car.getCarID()) {
            cars.push_back(existingCar);
        }
    }
    inFile.close();

    cars.push_back(car); // Add the updated car

    std::ofstream outFile("cars.txt");
    for (const auto& c : cars) {
        outFile << c.toString() << std::endl;
    }
    outFile.close();
    // Handle file operations errors
}

Car Car::getCarDetails(const std::string& carID) {
    std::ifstream inFile("cars.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        Car car = parseFromString(line);
        if (car.getCarID() == carID) {
            inFile.close();
            return car;
        }
    }
    inFile.close();
    throw std::runtime_error("Car not found: " + carID); // or handle it as per your error handling strategy
}

void Car::setRentalTimestamp(const std::string& carID, const std::string& timestamp) {
    std::vector<Car> cars;
    std::ifstream inFile("cars.txt");
    std::string line;
    bool carFound = false;

    while (std::getline(inFile, line)) {
        Car car = parseFromString(line);
        if (car.getCarID() == carID) {
            car.rentalTimestamp = timestamp;
            carFound = true;
        }
        cars.push_back(car);
    }
    inFile.close();

    if (!carFound) {
        throw std::runtime_error("Car not found: " + carID); // or handle as per your error handling strategy
    }

    std::ofstream outFile("cars.txt");
    for (const auto& c : cars) {
        outFile << c.toString() << std::endl;
    }
    outFile.close();
}

void Car::deleteCarFromFile(const std::string& carID) {
    std::vector<Car> cars;
    std::ifstream inFile("cars.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        Car car = parseFromString(line);
        if (car.getCarID() != carID) {
            cars.push_back(car);
        }
    }
    inFile.close();

    std::ofstream outFile("cars.txt");
    for (const auto& c : cars) {
        outFile << c.toString() << std::endl;
    }
    outFile.close();
    // Handle file operations errors
}

Car Car::parseFromString(const std::string& line) {
    std::stringstream ss(line);
    std::string carID, model, renterID, rentalTimestamp;
    bool isAvailable;
    int condition;

    std::getline(ss, carID, ',');
    std::getline(ss, model, ',');
    ss >> isAvailable;
    ss.ignore(1); // Ignore the delimiter
    ss >> condition;
    ss.ignore(1); // Ignore the delimiter
    std::getline(ss, rentalTimestamp, ',');
    std::getline(ss, renterID);

    Car car(carID, model, isAvailable, condition);
    car.setRentalDetails(renterID, rentalTimestamp);

    return car;
}
