#include <iostream>
#include <string>
#include <limits>
#include "Car.h"
#include "Customer.h"
#include "Employee.h"
#include "Manager.h"
#include <variant>
#include <memory>
#include <fstream>

void rentCar();
void returnCar();
void manageCustomers();
void manageEmployees();
void manageCars();
void addCustomer();
void updateCustomer();
void deleteCustomer();
void addEmployee();
void updateEmployee();
void deleteEmployee();
void addCar();
void updateCar();
void deleteCar();

using UserVariant = std::variant<std::shared_ptr<Customer>, std::shared_ptr<Employee>, std::shared_ptr<Manager>, std::nullptr_t>;

enum class UserType { Customer, Employee, Manager, Invalid };

UserVariant authenticateUser() {
    std::string id, password;
    std::cout << "Enter ID: ";
    std::getline(std::cin, id);
    std::cout << "Enter Password: ";
    std::getline(std::cin, password);

    // Check if the user is a Customer
    try {
        Customer customer = Customer::getCustomerDetails(id);
        if (customer.verifyPassword(password)) {
            return std::make_shared<Customer>(customer);
        }
    } catch (const std::exception&) {
        // Customer not found, continue to check next database
    }

    // Check if the user is an Employee
    try {
        Employee employee = Employee::getEmployeeDetails(id);
        if (employee.verifyPassword(password)) {
            return std::make_shared<Employee>(employee);
        }
    } catch (const std::exception&) {
        // Employee not found, continue to check next database
    }

    // Check if the user is a Manager
    try {
        Manager manager = Manager::getManagerDetails(id);
        if (manager.verifyPassword(password)) {
            return std::make_shared<Manager>(manager);
        }
    } catch (const std::exception&) {
        // Manager not found, user ID does not exist in any database
    }

    // If authentication fails
    return nullptr;
}

void addCustomer() {
    std::string id, name, contactInfo, password;
    std::cout << "Enter Customer ID: ";
    std::getline(std::cin, id);
    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Contact Info: ";
    std::getline(std::cin, contactInfo);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    Customer newCustomer(id, name, contactInfo,password);
    Customer::addCustomerToFile(newCustomer); // Assuming a static method to handle file operations

    std::cout << "Customer added successfully.\n";
}

void updateCustomer() {
    std::string id;
    std::cout << "Enter Customer ID to update: ";
    std::getline(std::cin, id);

    try {
        Customer customer = Customer::getCustomerDetails(id); // Assuming this method retrieves a customer object

        std::string newName, newContactInfo;
        std::cout << "Enter new Name (current: " << customer.getName() << "): ";
        std::getline(std::cin, newName);
        std::cout << "Enter new Contact Info (current: " << customer.getContactInfo() << "): ";
        std::getline(std::cin, newContactInfo);

        customer.setName(newName);
        customer.setContactInfo(newContactInfo);
        Customer::updateCustomerInFile(customer); // Update the customer record in the file

        std::cout << "Customer updated successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void deleteCustomer() {
    std::string id;
    std::cout << "Enter Customer ID to delete: ";
    std::getline(std::cin, id);

    try {
        Customer::deleteCustomerFromFile(id); // Assuming this method removes the customer from the database
        std::cout << "Customer deleted successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}


void manageCustomers() {
    int choice;
    while (true) {
        std::cout << "\n--- Customer Management ---\n";
        std::cout << "1. Add Customer\n";
        std::cout << "2. Update Customer\n";
        std::cout << "3. Delete Customer\n";
        std::cout << "4. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                updateCustomer();
                break;
            case 3:
                deleteCustomer();
                break;
            case 4:
                return; // Return to the main menu
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}

void addEmployee() {
    std::string id, name, contactInfo, password;
    std::cout << "Enter Employee ID: ";
    std::getline(std::cin, id);
    std::cout << "Enter Employee Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Contact Info: ";
    std::getline(std::cin, contactInfo);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    Employee newEmployee(id, name, contactInfo, password);
    Employee::addEmployeeToFile(newEmployee); // Assuming a static method to handle file operations

    std::cout << "Employee added successfully.\n";
}

void updateEmployee() {
    std::string id;
    std::cout << "Enter Employee ID to update: ";
    std::getline(std::cin, id);

    try {
        Employee employee = Employee::getEmployeeDetails(id); // Assuming this method retrieves an employee object

        std::string newName, newContactInfo;
        std::cout << "Enter new Name (current: " << employee.getName() << "): ";
        std::getline(std::cin, newName);
        std::cout << "Enter new Contact Info (current: " << employee.getContactInfo() << "): ";
        std::getline(std::cin, newContactInfo);

        employee.setName(newName);
        employee.setContactInfo(newContactInfo);
        Employee::updateEmployeeInFile(employee); // Update the employee record in the file

        std::cout << "Employee updated successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void deleteEmployee() {
    std::string id;
    std::cout << "Enter Employee ID to delete: ";
    std::getline(std::cin, id);

    try {
        Employee::deleteEmployeeFromFile(id); // Assuming this method removes the employee from the database
        std::cout << "Employee deleted successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}


void manageEmployees() {
    int choice;
    while (true) {
        std::cout << "\n--- Employee Management ---\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. Update Employee\n";
        std::cout << "3. Delete Employee\n";
        std::cout << "4. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                updateEmployee();
                break;
            case 3:
                deleteEmployee();
                break;
            case 4:
                return; // Return to the main menu
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}

void addCar() {
    std::string carID, model;
    int condition;
    bool isAvailable = true; // Assuming new cars are available by default

    std::cout << "Enter Car ID: ";
    std::getline(std::cin, carID);
    std::cout << "Enter Car Model: ";
    std::getline(std::cin, model);
    std::cout << "Enter Car Condition (0-100): ";
    std::cin >> condition;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Car newCar(carID, model, isAvailable, condition);
    Car::addCarToFile(newCar); // Assuming this method updates the car database

    std::cout << "Car added successfully.\n";
}

void updateCar() {
    std::string carID;
    std::cout << "Enter Car ID to update: ";
    std::getline(std::cin, carID);

    // Fetch the car details first
    try {
        Car car = Car::getCarDetails(carID);

        // Get updated details
        std::string newModel;
        int newCondition;
        std::cout << "Enter new Model (current: " << car.getModel() << "): ";
        std::getline(std::cin, newModel);
        std::cout << "Enter new Condition (current: " << car.getCondition() << "): ";
        std::cin >> newCondition;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Update car details
        car.setCondition(newCondition);
        Car::updateCarInFile(car); // Update the car in the database

        std::cout << "Car updated successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void deleteCar() {
    std::string carID;
    std::cout << "Enter Car ID to delete: ";
    std::getline(std::cin, carID);

    try {
        Car::deleteCarFromFile(carID); // Assuming this method removes the car from the database
        std::cout << "Car deleted successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}






void manageCars() {
    int choice;
    while (true) {
        std::cout << "\n--- Car Management ---\n";
        std::cout << "1. Add Car\n";
        std::cout << "2. Update Car\n";
        std::cout << "3. Delete Car\n";
        std::cout << "4. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addCar();
                break;
            case 2:
                updateCar();
                break;
            case 3:
                deleteCar();
                break;
            case 4:
                return; // Return to the main menu
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}


void rentCar() {
    std::string carID, renterID;
    int renterType;

    std::cout << "Enter Renter Type (1 for Customer, 2 for Employee): ";
    std::cin >> renterType;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Renter ID: ";
    std::getline(std::cin, renterID);

    std::cout << "Available Cars:\n";
    // Assuming a method to list available cars
    // listAvailableCars(); 

    std::cout << "Enter Car ID to rent: ";
    std::getline(std::cin, carID);

    try {
        if (renterType == 1) {
            Customer customer = Customer::getCustomerDetails(renterID); // Assuming this method exists
            customer.rentCar(carID);
            Customer::updateCustomerInFile(customer); // Update the customer record in the file
        } else if (renterType == 2) {
            Employee employee = Employee::getEmployeeDetails(renterID); // Assuming this method exists
            employee.rentCar(carID);
            Employee::updateEmployeeInFile(employee); // Update the employee record in the file
        } else {
            std::cout << "Invalid renter type.\n";
            return;
        }
        
        std::cout << "Car rented successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void CustomerRentCar(Customer& customer) {
    std::string carID;
    std::cout << "Enter Car ID to rent: ";
    std::getline(std::cin, carID);
    std::cin>>carID;

    // Perform the rent operation
    customer.rentCar(carID); // Assuming rentCar method is implemented in Customer class
}

void CustomerReturnCar(Customer& customer) {
    std::string carID;
    int carCondition;
    std::cout << "Enter Car ID to return: ";
    std::cin >> carID;
    std::cout << "Enter the condition of the car (0-100): ";
    std::cin >> carCondition;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Perform the return operation
    customer.returnCar(carID, carCondition); // Assuming returnCar method is implemented in Customer class
}

void viewFine(const Customer& customer) {
    // Assuming getFineAmount method returns the current fine amount for the customer
    std::cout << "Your current fine amount is: $" << customer.getFineAmount() << "\n";
}

void clearDue(Customer& customer) {
    // Assuming clearFine method in Customer class clears the fine
    customer.clearFine();
    std::cout << "Your fines have been cleared.\n";
}

void manageCustomers(Manager& manager) {
    int choice;
    do {
        std::cout << "\nCustomer Management\n";
        std::cout << "1. Add Customer\n";
        std::cout << "2. Update Customer\n";
        std::cout << "3. Delete Customer\n";
        std::cout << "4. Get Customer Details by ID\n";
        std::cout << "5. View All Customers\n";
        std::cout << "6. Return to Previous Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addCustomer();  // Function to add a new customer
                break;
            case 2:
                updateCustomer();  // Function to update an existing customer
                break;
            case 3:
                deleteCustomer();  // Function to delete a customer
                break;
            case 4:
                manager.getCustomerDetailsByID();
                break;
            case 5:
                Customer::viewAllCustomers();
                break;
            case 6:
                std::cout << "Returning to Manager Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

void manageEmployees(Manager& manager) {
    int choice;
    do {
        std::cout << "\nEmployee Management\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. Update Employee\n";
        std::cout << "3. Delete Employee\n";
        std::cout << "4. Get Employee Details by ID\n";
        std::cout << "5. View All Employee\n";
        std::cout << "6. Return to Previous Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addEmployee();  // Function to add a new employee
                break;
            case 2:
                updateEmployee();  // Function to update an existing employee
                break;
            case 3:
                deleteEmployee();  // Function to delete an employee
                break;
            case 4:
                manager.getEmployeeDetailsByID();
                break;
            case 5:
                Employee::viewAllEmployees();
                break;
            case 6:
                std::cout << "Returning to Manager Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

void manageCars(Manager& manager) {
    int choice;
    do {
        std::cout << "\nCar Management\n";
        std::cout << "1. Add Car\n";
        std::cout << "2. Update Car\n";
        std::cout << "3. Delete Car\n";
        std::cout << "4. Get Car Details by ID\n";
        std::cout << "5. View All Cars\n";
        std::cout << "6. Return to Previous Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addCar();  // Function to add a new car
                break;
            case 2:
                updateCar();  // Function to update an existing car
                break;
            case 3:
                deleteCar();  // Function to delete a car
                break;
            case 4:  
                manager.getCarDetailsByID();
                break;
            case 5:  
                manager.viewAllCars();
                break;
            case 6:
                std::cout << "Returning to Manager Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}



void customerMenu(Customer& customer) {
    int choice;
    do {
        std::cout << "\nCustomer Menu\n";
        std::cout << "1. Rent a Car\n";
        std::cout << "2. Return a Car\n";
        std::cout << "3. View Available Cars\n";
        std::cout << "4. View Fine Due\n";
        std::cout << "5. Clear Due\n";
        std::cout << "6. view rented cars\n";
        std::cout << "7. view my rating\n";
        std::cout << "8. Logout\n";
        
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                CustomerRentCar(customer);  // Function to handle renting a car
                break;
            case 2:
                CustomerReturnCar(customer);  // Function to handle returning a car
                break;
            case 3:
                Car::listAvailableCars();  // Function to list all available cars
                break;
            case 4:
                viewFine(customer);  // Function to view any fines due
                break;
            case 5:
                clearDue(customer);  // Function to clear any due fines       
            case 6:
                customer.viewMyRentedCars();
                break;    
            case 7:
                customer.viewMyRating(); 
                break;  
            case 8:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";            
        }
    } while (choice != 8);
}

void EmployeeRentCar(Employee& employee) {
    std::string carID;
    std::cout << "Enter Car ID to rent: ";
    std::cin>>carID;
    employee.rentCar(carID); // Assuming rentCar method is implemented in Employee class
}

void EmployeeReturnCar(Employee& employee) {
    std::string carID;
    int carCondition;
    std::cout << "Enter Car ID to return: ";
    std::cin>> carID;
    std::cout << "Enter the condition of the car (0-100): ";
    std::cin >> carCondition;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Perform the return operation
    employee.returnCar(carID, carCondition); // Assuming returnCar method is implemented in Employee class
}

void viewFine(const Employee& employee) {
    // Assuming getFineAmount method returns the current fine amount for the employee
    std::cout << "Your current fine amount is: $" << employee.getFineAmount() << "\n";
}

void clearDue(Employee& employee) {
    // Assuming clearFine method in Employee class clears the fine
    employee.clearFine();
    std::cout << "Your fines have been cleared.\n";
}


void employeeMenu(Employee& employee) {
    int choice;
    do {
        std::cout << "\nEmployee Menu\n";
        std::cout << "1. Rent a Car\n";
        std::cout << "2. Return a Car\n";
        std::cout << "3. View Available Cars\n";
        std::cout << "4. View Fine Due\n";
        std::cout << "5. Clear Due\n";
        std::cout << "6. view rented cars\n";
        std::cout << "7. view my rating\n";
        std::cout << "8. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                EmployeeRentCar(employee);  // Function to handle renting a car
                break;
            case 2:
                EmployeeReturnCar(employee);  // Function to handle returning a car
                break;
            case 3:
                Car::listAvailableCars();  // Function to list all available cars
                break;
            case 4:
                viewFine(employee);  // Function to view any fines due
                break;
            case 5:
                clearDue(employee);  // Function to clear any due fines
                break;
            case 6:
                employee.viewMyRentedCars();
                break;    
            case 7:
                employee.viewMyRating(); 
                break;   
            case 8:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

void managerMenu(Manager& manager) {
    int choice;
    do {
        std::cout << "\nManager Menu\n";
        std::cout << "1. Manage Customers\n";
        std::cout << "2. Manage Employees\n";
        std::cout << "3. Manage Cars\n";
        std::cout << "4. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

        switch (choice) {
            case 1:
                manageCustomers(manager);
                break;
            case 2:
                manageEmployees(manager);
                break;
            case 3:
                manageCars(manager);
                break;
            case 4:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

void initializeDefaultData() {
    // Default Cars
    std::vector<Car> defaultCars = {
        Car("Car001", "Toyota Camry", true),
        Car("Car002", "Honda Accord", true),
        Car("Car003", "Ford Focus", true),
        Car("Car004", "Nissan Altima", true),
        Car("Car005", "Chevrolet Impala", true)
    };

    if (isFileEmpty("cars.txt")) {
        for (const auto& car : defaultCars) {
            Car::addCarToFile(car);
        }
    }

    // Default Customers
    std::vector<Customer> defaultCustomers = {
        Customer("Cust001", "John Doe", "johndoe@example.com", "password123", 10),
        Customer("Cust002", "Jane Smith", "janesmith@example.com", "password123", 10),
        Customer("Cust003", "Alice Johnson", "alicej@example.com", "password123", 10),
        Customer("Cust004", "Bob Brown", "bobb@example.com", "password123", 10),
        Customer("Cust005", "Charlie Davis", "charlied@example.com", "password123", 10)
    };

    if (isFileEmpty("customers.txt")) {
        for (const auto& customer : defaultCustomers) {
            Customer::addCustomerToFile(customer);
            User::addUserToFile(customer);
        }
    }

    // Default Employees
    std::vector<Employee> defaultEmployees = {
        Employee("Emp001", "Eve White", "evew@example.com", "password123", 10),
        Employee("Emp002", "Mason Green", "masong@example.com", "password123", 10),
        Employee("Emp003", "Lucy Black", "lucyb@example.com", "password123", 10),
        Employee("Emp004", "Oscar Yellow", "oscary@example.com", "password123", 10),
        Employee("Emp005", "Lily Blue", "lilyb@example.com", "password123", 10)
    };

    if (isFileEmpty("employees.txt")) {
        for (const auto& employee : defaultEmployees) {
            Employee::addEmployeeToFile(employee);
            User::addUserToFile(employee);
        }
    }

    // Default Manager
    Manager defaultManager("Man001", "Max Manager", "maxm@example.com", "admin123");

    if (isFileEmpty("managers.txt")) {
        Manager::addManagerToFile(defaultManager);
        User::addUserToFile(defaultManager);
    }
}


int main() {
    // Load data, if necessary
    initializeDefaultData();
    UserVariant userVariant = authenticateUser();
    if (std::holds_alternative<std::shared_ptr<Customer>>(userVariant)) {
        customerMenu(*std::get<std::shared_ptr<Customer>>(userVariant));
    } else if (std::holds_alternative<std::shared_ptr<Employee>>(userVariant)) {
        employeeMenu(*std::get<std::shared_ptr<Employee>>(userVariant));
    } else if (std::holds_alternative<std::shared_ptr<Manager>>(userVariant)) {
        managerMenu(*std::get<std::shared_ptr<Manager>>(userVariant));
    } else {
        std::cout << "Invalid login.\n";
    }

    // Save data, if necessary
    return 0;
}

