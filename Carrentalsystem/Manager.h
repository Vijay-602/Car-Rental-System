#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"
#include "Customer.h"
#include "Employee.h"
#include "Car.h"
#include <stdexcept> // For std::runtime_error
#include <vector>

class Manager : public User {
public:
    Manager(const std::string& id, const std::string& name, const std::string& contactInfo, const std::string& password);

    // Manager-specific functionalities
    void addCustomer(const Customer& customer);
    void updateCustomer(const Customer& customer);
    void deleteCustomer(const std::string& customerId);
    static Manager getManagerDetails(const std::string& id);
    void addEmployee(const Employee& employee);
    void updateEmployee(const Employee& employee);
    void deleteEmployee(const std::string& employeeId);

    void addCar(const Car& car);
    void updateCar(const Car& car);
    void deleteCar(const std::string& carId);
    void viewAllCars() const;
    void getCarDetailsByID() const; 
    std::string toString() const override;

    static void addManagerToFile(const Manager& manager);
    static void updateManagerInFile(const Manager& manager);
    static void deleteManagerFromFile(const std::string& managerId);
    static Manager parseFromString(const std::string& line);
    void getEmployeeDetailsByID() const;  
    void getCustomerDetailsByID() const;  

    // Exception class for handling manager-specific errors
    class ManagerException : public std::runtime_error {
    public:
        ManagerException(const std::string& msg) : std::runtime_error(msg) {}
    };
};

#endif // MANAGER_H
