#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <vector>
#include <stdexcept> // For std::runtime_error

class Customer : public User {
private:
    float fineAmount;
    int customerRating; // Rating out of 100
    std::vector<std::string> rentedCars; // List of car IDs

public:
    Customer(const std::string& id, const std::string& name, const std::string& contactInfo, const std::string& password, int rating=10);


    // Getters and Setters
    float getFineAmount() const;
    int getCustomerRating() const;
    std::vector<std::string> getRentedCars() const;

    void setFineAmount(float fine);
    void setCustomerRating(int rating);
void viewMyRating() const;  // New method to view employee's rating
    void viewMyRentedCars() const;
    // Customer-specific functionalities
    void rentCar(const std::string& carID) ;
    void returnCar(const std::string& carID, int carCondition);
    void updateRecord(int daysLate, int currentCondition, int damage);
    static void viewAllCustomers(); 

    // Override toString for file handling
    std::string toString() const override;
    int calculateDelay(const std::string& rentalTimestamp);
    void clearFine();
    // File handling methods
    static void addCustomerToFile(const Customer& customer);
    static void updateCustomerInFile(const Customer& customer);
    static void deleteCustomerFromFile(const std::string& customerId);
    static Customer parseFromString(const std::string& line);
    static Customer getCustomerDetails(const std::string& renterID);
    // Exception class for handling customer-specific errors
    class CustomerException : public std::runtime_error {
    public:
        CustomerException(const std::string& msg) : std::runtime_error(msg) {}
    };
};

#endif // CUSTOMER_H
