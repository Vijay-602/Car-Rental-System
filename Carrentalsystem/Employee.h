#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"
#include <vector>
#include <stdexcept> // For std::runtime_error

class Employee : public User {
private:
    float fineAmount;
    int employeeRating; // Rating out of 10
    std::vector<std::string> rentedCars; // List of car IDs
    const float discountRate = 0.15; // 15% discount for employees

public:
     Employee(const std::string& id, const std::string& name, const std::string& contactInfo, const std::string& password, int rating=10);

    // Getters and Setters
    float getFineAmount() const;
    int getEmployeeRating() const;
    std::vector<std::string> getRentedCars() const;

    void setFineAmount(float fine);
    void setEmployeeRating(int rating);
    static void viewAllEmployees(); 
    // Employee-specific functionalities
    void rentCar(const std::string& carID);
    void returnCar(const std::string& carID, int carCondition);
    void updateRecord(bool isLate, int carCondition, int daysRented);
    void clearFine();
    // Override toString for file handling
    std::string toString() const override;
void viewMyRating() const;  // New method to view employee's rating
    void viewMyRentedCars() const;
    // File handling methods
    static void addEmployeeToFile(const Employee& employee);
    static void updateEmployeeInFile(const Employee& employee);
    static void deleteEmployeeFromFile(const std::string& employeeId);
    static Employee parseFromString(const std::string& line);
    void updateRecord(int daysLate, int currentCondition, int damage);
    int calculateDelay(const std::string& rentalTimestamp);
    static Employee getEmployeeDetails(const std::string& renterID);
    // Exception class for handling employee-specific errors
    class EmployeeException : public std::runtime_error {
    public:
        EmployeeException(const std::string& msg) : std::runtime_error(msg) {}
    };
};

#endif // EMPLOYEE_H
