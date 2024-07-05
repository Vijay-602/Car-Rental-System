#include "Employee.h"
#include "Car.h" // Assuming this is the Car class with required functionalities
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

Employee::Employee(const std::string& id, const std::string& name, 
                   const std::string& contactInfo, const std::string& password, 
                   int rating)
    : User(id, name, contactInfo, password),
      fineAmount(0.0),  // Initialize fineAmount to 0.0
      employeeRating(rating) {
}


// Implementation of Getters and Setters ...

float Employee::getFineAmount() const {
    return fineAmount;
}

int Employee::getEmployeeRating() const {
    return employeeRating;
}

std::vector<std::string> Employee::getRentedCars() const {
    return rentedCars;
}

void Employee::setFineAmount(float fine) {
    fineAmount = fine;
}

void Employee::setEmployeeRating(int rating) {
    employeeRating = rating;
}

void Employee::viewAllEmployees() {
    std::ifstream inFile("employees.txt");
    std::string line;

    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file to read employees.");
    }

    std::cout << "List of All Employees:\n";
    while (std::getline(inFile, line)) {
        Employee employee = Employee::parseFromString(line);
        std::cout << employee.toString() << std::endl;  // Adjust output formatting as needed
    }
    inFile.close();
}


void Employee::rentCar(const std::string& carID) {
    // Check if car is available and employee's rating is sufficient
    Car car = Car::getCarDetails(carID); // Assuming such a function exists
    if (car.getAvailability() && employeeRating >= 5) {
        rentedCars.push_back(carID);
        car.setAvailability(false); // Update the car's availability
        Car::updateCarInFile(car); // Update car details in the database
    } else {
        std::cout<<"Car is not available or employee rating is too low.\n";
    }
}

void Employee::clearFine() {
    fineAmount = 0.0; // Reset the fine amount to zero

    // Update the customer record in the file/database
    updateEmployeeInFile(*this);

    std::cout << "All fines have been cleared.\n";
}

int Employee::calculateDelay(const std::string& rentalTimestamp) {
    // Parse the rental timestamp
    std::tm tm = {};
    std::istringstream ss(rentalTimestamp);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S"); // Adjust format if different
    auto rentalTime = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    // Get the current time
    auto now = std::chrono::system_clock::now();

    // Calculate the difference in seconds
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - rentalTime);

    // Convert the difference to days
    int delayDays = duration.count() / (60 * 60 * 24);

    return delayDays > 0 ? delayDays : 0; // Return the delay in days, ensuring it's not negative
}

void Employee::returnCar(const std::string& carID, int carCondition) {
    auto it = std::find(rentedCars.begin(), rentedCars.end(), carID);
    if (it != rentedCars.end()) {
        rentedCars.erase(it);

        Car car = Car::getCarDetails(carID); // Retrieve car details
        std::string rentalTimestamp = car.getRentalTimestamp();

        // Calculate days late and damage
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::time_t rentalTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::from_time_t(std::mktime(std::localtime(&now_c))) - std::chrono::hours(24) * calculateDelay(rentalTimestamp));
        
        int daysLate = std::difftime(now_c, rentalTime) / (60 * 60 * 24);
        int damage = std::max(0, car.getCondition() - carCondition);

        updateRecord(daysLate, carCondition, damage);

        car.setAvailability(true); // Make the car available again
        car.setCondition(carCondition); // Update car condition
        Car::updateCarInFile(car); // Update car details in the database
    } else {
        throw EmployeeException("Car not found in the employee's rented list.");
    }
}

int employeeDailyLateFee = 1;
int employeeDelayPenalty = 1;
int employeeDamageFeeRate = 1;
int employeeDamagePenalty = 1;

void Employee::updateRecord(int daysLate, int currentCondition, int damage) {
    // Adjustments for late return
    if (daysLate > 0) {
        fineAmount += daysLate * employeeDailyLateFee; // dailyLateFee is a predefined constant
        employeeRating -= employeeDelayPenalty; // delayPenalty is a predefined constant
    }

    // Adjustments for car condition
    if (damage > 0) {
        fineAmount += damage * employeeDamageFeeRate; // damageFeeRate is a predefined constant
        employeeRating -= employeeDamagePenalty; // damagePenalty is a predefined constant
    }

    // Ensure rating stays within the valid range
    employeeRating = std::max(0, std::min(employeeRating, 10));
}

Employee Employee::getEmployeeDetails(const std::string& renterID) {
    std::ifstream file("employees.txt");
    std::string line;

    while (std::getline(file, line)) {
        Employee employee = Employee::parseFromString(line);
        if (employee.getId() == renterID) {
            return employee;
        }
    }

    throw std::runtime_error("Employee not found: " + renterID);
}

std::string Employee::toString() const {
    std::stringstream ss;
    ss << User::toString() << "," << fineAmount << "," << employeeRating;
    for (const auto& carID : rentedCars) {
        ss << "," << carID;
    }
    return ss.str();
}

// ... [Previous Code]

void Employee::addEmployeeToFile(const Employee& employee) {
    std::ofstream file("employees.txt", std::ios::app); // Append mode
    if (file.is_open()) {
        file << employee.toString() << std::endl;
        file.close();
    } else {
        throw EmployeeException("Unable to open file to add employee.");
    }
}

void Employee::updateEmployeeInFile(const Employee& employee) {
    std::vector<Employee> employees;
    std::ifstream inFile("employees.txt");
    std::string line;
    if (!inFile.is_open()) {
        throw EmployeeException("Unable to open file to update employee.");
    }

    while (std::getline(inFile, line)) {
        Employee existingEmployee = parseFromString(line);
        if (existingEmployee.getId() != employee.getId()) {
            employees.push_back(existingEmployee);
        }
    }
    inFile.close();

    // Add the updated employee
    employees.push_back(employee);

    std::ofstream outFile("employees.txt");
    if (!outFile.is_open()) {
        throw EmployeeException("Unable to open file to save updated employee.");
    }

    for (const auto& e : employees) {
        outFile << e.toString() << std::endl;
    }
    outFile.close();
}

void Employee::deleteEmployeeFromFile(const std::string& employeeId) {
    std::vector<Employee> employees;
    std::ifstream inFile("employees.txt");
    if (!inFile.is_open()) {
        throw EmployeeException("Unable to open file to delete employee.");
    }

    std::string line;
    while (std::getline(inFile, line)) {
        Employee employee = parseFromString(line);
        if (employee.getId() != employeeId) {
            employees.push_back(employee);
        }
    }
    inFile.close();

    std::ofstream outFile("employees.txt");
    if (!outFile.is_open()) {
        throw EmployeeException("Unable to open file to save remaining employees.");
    }

    for (const auto& e : employees) {
        outFile << e.toString() << std::endl;
    }
    outFile.close();
}

void Employee::viewMyRating() const {
    std::cout << "Your Rating: " << employeeRating << "/10" << std::endl;
}

void Employee::viewMyRentedCars() const {
    if (rentedCars.empty()) {
        std::cout << "You have no cars rented currently." << std::endl;
        return;
    }

    std::cout << "Rented Cars:\n";
    for (const auto& carID : rentedCars) {
        std::cout << "Car ID: " << carID << std::endl;
    }
}
Employee Employee::parseFromString(const std::string& line) {
    std::stringstream ss(line);
    std::string id, name, contactInfo, password;
    float fineAmount;
    int rating;
    std::vector<std::string> rentedCars;

    std::getline(ss, id, ',');
    std::getline(ss, name, ',');
    std::getline(ss, contactInfo, ',');
    std::getline(ss, password, ',');
    ss >> fineAmount;
    ss.ignore(); // Ignore the delimiter
    ss >> rating;

    // Assuming rented car IDs are appended at the end of the line
    while (ss.good()) {
        std::string carId;
        std::getline(ss, carId, ',');
        if (!carId.empty()) {
            rentedCars.push_back(carId);
        }
    }

    Employee employee(id, name, contactInfo, password, rating);
    employee.setFineAmount(fineAmount);
    for (const auto& carID : rentedCars) {
        employee.rentCar(carID); // Assuming this method only modifies the rentedCars vector
    }
    return employee;
}



