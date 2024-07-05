#include "Customer.h"
#include "Car.h" 
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>

Customer::Customer(const std::string& id, const std::string& name, 
                   const std::string& contactInfo, const std::string& password, 
                   int rating)
    : User(id, name, contactInfo, password), 
      fineAmount(0.0),
      customerRating(rating) {
}

// Implementation of Getters and Setters ...

void Customer::rentCar(const std::string& carID) {
    // Check if car is available and customer's rating is sufficient
    Car car = Car::getCarDetails(carID); // Assuming such a function exists
    if (car.getAvailability() && customerRating >= 5) {
        std::cout<<" Car rented Successfully";
        rentedCars.push_back(carID);
        car.setAvailability(false); // Update the car's availability
        Car::updateCarInFile(car); // Update car details in the database
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::ostringstream timestamp;
        timestamp << std::put_time(std::localtime(&now_c), "%F %T"); // Format as "YYYY-MM-DD HH:MM:SS"

    Car::setRentalTimestamp(carID, timestamp.str());
    } else {
        std::cout<<"Car is not available or customer rating is too low.";
    }
}

void Customer::viewAllCustomers() {
    std::ifstream inFile("customers.txt");
    std::string line;

    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file to read customers.");
    }

    std::cout << "List of All Customers:\n";
    while (std::getline(inFile, line)) {
        Customer customer = Customer::parseFromString(line);
        std::cout << customer.toString() << std::endl;  // Adjust output formatting as needed
    }
    inFile.close();
}

void Customer::clearFine() {
    fineAmount = 0.0; // Reset the fine amount to zero

    // Update the customer record in the file/database
    updateCustomerInFile(*this);

    std::cout << "All fines have been cleared.\n";
}

int Customer::calculateDelay(const std::string& rentalTimestamp) {
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

void Customer::setFineAmount(float fine) {
    this->fineAmount = fine;
}

float Customer::getFineAmount() const {
    return fineAmount;
}


Customer Customer::getCustomerDetails(const std::string& renterID) {
    std::ifstream file("customers.txt");
    std::string line;

    while (std::getline(file, line)) {
        Customer customer = Customer::parseFromString(line);
        if (customer.getId() == renterID) {
            return customer;
        }
    }

    throw std::runtime_error("Customer not found: " + renterID);
}


void Customer::returnCar(const std::string& carID, int carCondition) {
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
        throw CustomerException("Car not found in the customer's rented list.");
    }
}



int customerDailyLateFee = 1;
int customerDelayPenalty = 1;
int customerDamageFeeRate = 1;
int customerDamagePenalty = 1;

void Customer::updateRecord(int daysLate, int currentCondition, int damage) {
    // Late fee calculation
    if (daysLate > 0) {
        fineAmount += daysLate * customerDailyLateFee; // dailyLateFee is a predefined constant
        customerRating -= customerDelayPenalty; // delayPenalty is a predefined constant
    }

    // Damage fee calculation
    if (damage > 0) {
        fineAmount += damage * customerDamageFeeRate; // damageFeeRate is a predefined constant
        customerRating -= customerDamagePenalty; // damagePenalty is a predefined constant
    }

    // Ensure rating stays within valid range
    customerRating = std::max(0, std::min(customerRating, 10));
}

std::string Customer::toString() const {
    std::stringstream ss;
    ss << User::toString() << "," << fineAmount << "," << customerRating;
    for (const auto& carID : rentedCars) {
        ss << "," << carID;
    }
    return ss.str();
}

// Implement file handling methods following the pattern in User.cpp

// Customer-specific exception handling

void Customer::addCustomerToFile(const Customer& customer) {
    std::ofstream file("customers.txt", std::ios::app); // Append mode
    if (file.is_open()) {
        file << customer.toString() << std::endl;
        file.close();
    } else {
        throw CustomerException("Unable to open file to add customer.");
    }
}

void Customer::viewMyRating() const {
    std::cout << "Your Rating: " << customerRating << "/10" << std::endl;
}

void Customer::viewMyRentedCars() const {
    if (rentedCars.empty()) {
        std::cout << "You have no cars rented currently." << std::endl;
        return;
    }

    std::cout << "Rented Cars:\n";
    for (const auto& carID : rentedCars) {
        std::cout << "Car ID: " << carID << std::endl;
    }
}
void Customer::updateCustomerInFile(const Customer& customer) {
    std::vector<Customer> customers;
    std::ifstream inFile("customers.txt");
    std::string line;
    if (!inFile.is_open()) {
        throw CustomerException("Unable to open file to update customer.");
    }

    while (std::getline(inFile, line)) {
        Customer existingCustomer = parseFromString(line);
        if (existingCustomer.getId() != customer.getId()) {
            customers.push_back(existingCustomer);
        }
    }
    inFile.close();

    // Add the updated customer
    customers.push_back(customer);

    std::ofstream outFile("customers.txt");
    if (!outFile.is_open()) {
        throw CustomerException("Unable to open file to save updated customer.");
    }

    for (const auto& c : customers) {
        outFile << c.toString() << std::endl;
    }
    outFile.close();
}

void Customer::deleteCustomerFromFile(const std::string& customerId) {
    std::vector<Customer> customers;
    std::ifstream inFile("customers.txt");
    if (!inFile.is_open()) {
        throw CustomerException("Unable to open file to delete customer.");
    }

    std::string line;
    while (std::getline(inFile, line)) {
        Customer customer = parseFromString(line);
        if (customer.getId() != customerId) {
            customers.push_back(customer);
        }
    }
    inFile.close();

    std::ofstream outFile("customers.txt");
    if (!outFile.is_open()) {
        throw CustomerException("Unable to open file to save remaining customers.");
    }

    for (const auto& c : customers) {
        outFile << c.toString() << std::endl;
    }
    outFile.close();
}

Customer Customer::parseFromString(const std::string& line) {
    std::stringstream ss(line);
    std::string id, name, contactInfo,password;
    float fineAmount;
    int rating;
    std::vector<std::string> rentedCars;

    std::getline(ss, id, ',');
    std::getline(ss, name, ',');
    std::getline(ss, contactInfo, ',');
    std::getline(ss, password, ',');
    ss >> fineAmount;  // Directly read the fine amount
    ss.ignore();  // Ignore the delimiter before reading the rating
    ss >> rating;

    // Assuming rented car IDs are appended at the end of the line
    while (ss.good()) {
        std::string carId;
        std::getline(ss, carId, ',');
        if (!carId.empty()) {
            rentedCars.push_back(carId);
        }
    }

    Customer customer(id, name, contactInfo,password,rating);
    customer.setFineAmount(fineAmount);
    for (const auto& carID : rentedCars) {
        customer.rentCar(carID);
    }
    return customer;
}

