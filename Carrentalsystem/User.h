#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string id;
    std::string name;
    std::string contactInfo;
    std::string password;
    // Other common attributes

public:
    User(const std::string& id, const std::string& name, const std::string& contactInfo, const std::string& password);
    virtual ~User() = default;

    // Getters and Setters
    std::string getId() const;
    std::string getName() const;
    std::string getContactInfo() const;
    void setPassword(const std::string& newPassword);
    bool verifyPassword(const std::string& inputPassword) const;

    void setName(const std::string& name);
    void setContactInfo(const std::string& contactInfo);

    // Convert user details to a string for file storage
    virtual std::string toString() const;

    // File handling methods
    static void addUserToFile(const User& user);
    static void updateUserInFile(const User& user);
    static void deleteUserFromFile(const std::string& userId);
    static User parseFromString(const std::string& line);
};

#endif // USER_H
