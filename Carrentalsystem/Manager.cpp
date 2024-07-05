#include "Manager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Manager::Manager(const std::string& id, const std::string& name, const std::string& contactInfo, const std::string& password) 
    : User(id, name, contactInfo,password) {
    // The constructor initializes the Manager with the provided details.
    // The User constructor is called with id, name, and contactInfo.
    // The password is set for the Manager.
}

void Manager::addCustomer(const Customer& customer) {
    try {
        Customer::addCustomerToFile(customer);
        User::addUserToFile(customer);
    } catch (const std::runtime_error& e) {
        throw ManagerException("Failed to add customer: " + std::string(e.what()));
    }
}

void Manager::updateCustomer(const Customer& customer) {
    try {
        Customer::updateCustomerInFile(customer);

    } catch (const std::runtime_error& e) {
        throw ManagerException("Failed to update customer: " + std::string(e.what()));
    }
}

void Manager::deleteCustomer(const std::string& customerId) {
    try {
        Customer::deleteCustomerFromFile(customerId);
    } catch (const std::runtime_error& e) {
        throw ManagerException("Failed to delete customer: " + std::string(e.what()));
    }
}

// ... [Include necessary headers and previous code]

void Manager::addEmployee(const Employee& employee) {
    try {
        Employee::addEmployeeToFile(employee);
    } catch (const Employee::EmployeeException& e) {
        throw ManagerException("Failed to add employee: " + std::string(e.what()));
    } catch (const std::exception& e) {
        throw ManagerException("An error occurred while adding an employee: " + std::string(e.what()));
    } catch (...) {
        throw ManagerException("An unknown error occurred while adding an employee.");
    }
}

Manager Manager::getManagerDetails(const std::string& id) {
    std::ifstream file("managers.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string managerId, name, contactInfo, password;
        std::getline(iss, managerId, ',');

        if (managerId == id) {
            std::getline(iss, name, ',');
            std::getline(iss, contactInfo, ',');
            std::getline(iss, password);  // Assuming password is the last item in the line

            return Manager(managerId, name, contactInfo, password);
        }
    }

    throw std::runtime_error("Manager not found with ID: " + id);
}

void Manager::updateEmployee(const Employee& employee) {
    try {
        Employee::updateEmployeeInFile(employee);
    } catch (const Employee::EmployeeException& e) {
        throw ManagerException("Failed to update employee: " + std::string(e.what()));
    } catch (const std::exception& e) {
        throw ManagerException("An error occurred while updating an employee: " + std::string(e.what()));
    } catch (...) {
        throw ManagerException("An unknown error occurred while updating an employee.");
    }
}

void Manager::deleteEmployee(const std::string& employeeId) {
    try {
        Employee::deleteEmployeeFromFile(employeeId);
    } catch (const Employee::EmployeeException& e) {
        throw ManagerException("Failed to delete employee: " + std::string(e.what()));
    } catch (const std::exception& e) {
        throw ManagerException("An error occurred while deleting an employee: " + std::string(e.what()));
    } catch (...) {
        throw ManagerException("An unknown error occurred while deleting an employee.");
    }
}

std::string Manager::toString() const {
    std::ostringstream ss;
    ss << User::toString();  
    return ss.str();
}

void Manager::addManagerToFile(const Manager& manager) {
    std::ofstream outFile("managers.txt", std::ios::app);  // Append mode
    if (outFile.is_open()) {
        outFile << manager.toString() << std::endl;
        outFile.close();
    } else {
        throw std::runtime_error("Unable to open file to add manager.");
    }
}

void Manager::updateManagerInFile(const Manager& manager) {
    std::vector<Manager> managers;
    std::ifstream inFile("managers.txt");
    std::string line;
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file to update manager.");
    }

    while (std::getline(inFile, line)) {
        Manager existingManager = parseFromString(line);
        if (existingManager.getId() != manager.getId()) {
            managers.push_back(existingManager);
        }
    }
    inFile.close();

    // Add the updated manager
    managers.push_back(manager);

    std::ofstream outFile("managers.txt");
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file to save updated manager.");
    }

    for (const auto& m : managers) {
        outFile << m.toString() << std::endl;
    }
    outFile.close();
}

void Manager::getEmployeeDetailsByID() const {
    std::string employeeId;
    std::cout << "Enter Employee ID: ";
    std::getline(std::cin, employeeId);

    try {
        Employee employee = Employee::getEmployeeDetails(employeeId);
        std::cout << "Employee Details:\n" << employee.toString() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Manager::getCustomerDetailsByID() const {
    std::string customerId;
    std::cout << "Enter Customer ID: ";
    std::getline(std::cin, customerId);

    try {
        Customer customer = Customer::getCustomerDetails(customerId);
        std::cout << "Customer Details:\n" << customer.toString() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Manager::getCarDetailsByID() const {
    std::string carId;
    std::cout << "Enter Car ID: ";
    std::getline(std::cin, carId);

    try {
        Car car = Car::getCarDetails(carId);
        std::cout << "Car Details:\n" << car.toString() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Manager::viewAllCars() const {
    std::ifstream inFile("cars.txt");
    std::string line;

    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file to read cars.");
    }

    std::cout << "List of All Cars:\n";
    while (std::getline(inFile, line)) {
        Car car = Car::parseFromString(line);
        std::cout << car.toString() << std::endl;  
    }
    inFile.close();
}


void Manager::deleteManagerFromFile(const std::string& managerId) {
    std::vector<Manager> managers;
    std::ifstream inFile("managers.txt");
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file to delete manager.");
    }

    std::string line;
    while (std::getline(inFile, line)) {
        Manager manager = parseFromString(line);
        if (manager.getId() != managerId) {
            managers.push_back(manager);
        }
    }
    inFile.close();

    std::ofstream outFile("managers.txt");
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file to save remaining managers.");
    }

    for (const auto& m : managers) {
        outFile << m.toString() << std::endl;
    }
    outFile.close();
}

Manager Manager::parseFromString(const std::string& line) {
    std::stringstream ss(line);
    std::string id, name, contactInfo, password;

    std::getline(ss, id, ',');
    std::getline(ss, name, ',');
    std::getline(ss, contactInfo, ',');
    std::getline(ss, password, ',');

    return Manager(id, name, contactInfo, password);
}

void Manager::addCar(const Car& car) {
    try {
        Car::addCarToFile(car);
    } catch (const std::runtime_error& e) {
        throw ManagerException("Failed to add car: " + std::string(e.what()));
    }
}

void Manager::updateCar(const Car& car) {
    try {
        Car::updateCarInFile(car);
    } catch (const std::runtime_error& e) {
        throw ManagerException("Failed to update car: " + std::string(e.what()));
    }
}

void Manager::deleteCar(const std::string& carId) {
    try {
        Car::deleteCarFromFile(carId);
    } catch (const std::runtime_error& e) {
        throw ManagerException("Failed to delete car: " + std::string(e.what()));
    }
}

// Implementation of Manager-specific exception handling...
