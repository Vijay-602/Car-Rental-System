#include "User.h"
#include <fstream>
#include <sstream>
#include <vector>

User::User(const std::string& id, const std::string& name, const std::string& contactInfo, const std::string& password)
    : id(id), name(name), contactInfo(contactInfo), password(password) {
    // Initialize all the member variables, including the password
    // In a real application, consider hashing the password for security
}

std::string User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getContactInfo() const { return contactInfo; }

void User::setName(const std::string& name) { this->name = name; }
void User::setContactInfo(const std::string& contactInfo) { this->contactInfo = contactInfo; }

std::string User::toString() const {
    std::ostringstream ss;
    ss << id << "," << name << "," << contactInfo << "," << password;
    return ss.str();
}

void User::addUserToFile(const User& user) {
    std::ofstream file("users.txt", std::ios::app);
    if (file.is_open()) {
        file << user.toString() << std::endl;
        file.close();
    }
}

void User::setPassword(const std::string& newPassword) {
    password = newPassword; // In real application, consider hashing the password
}

bool User::verifyPassword(const std::string& inputPassword) const {
    return password == inputPassword; // For hashed passwords, compare hashes
}

void User::updateUserInFile(const User& user) {
    std::vector<User> users;
    std::ifstream inFile("users.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        User existingUser = parseFromString(line);
        if (existingUser.getId() != user.getId()) {
            users.push_back(existingUser);
        }
    }
    inFile.close();

    users.push_back(user); // Add the updated user

    std::ofstream outFile("users.txt");
    for (const auto& u : users) {
        outFile << u.toString() << std::endl;
    }
    outFile.close();
}

void User::deleteUserFromFile(const std::string& userId) {
    std::vector<User> users;
    std::ifstream inFile("users.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        User user = parseFromString(line);
        if (user.getId() != userId) {
            users.push_back(user);
        }
    }
    inFile.close();

    std::ofstream outFile("users.txt");
    for (const auto& u : users) {
        outFile << u.toString() << std::endl;
    }
    outFile.close();
}

User User::parseFromString(const std::string& line) {
    std::stringstream ss(line);
    std::string id, name, contactInfo,password;

    std::getline(ss, id, ',');
    std::getline(ss, name, ',');
    std::getline(ss, contactInfo);
    std::getline(ss, password);

    return User(id, name, contactInfo,password);
}
