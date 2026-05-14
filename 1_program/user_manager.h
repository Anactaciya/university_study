#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <unordered_map>
#include <memory>
#include "user.h"
#include "group.h"

class UserManager {
private:
    std::unordered_map<std::string, std::shared_ptr<User>> users;
    std::unordered_map<std::string, std::shared_ptr<Group>> groups;

public:
    bool createUser(const std::string& userId, const std::string& username,
                   const std::string& house, const std::string& fullName,
                   const std::string& patronus = "", const std::string& wand = "");
    bool deleteUser(const std::string& userId);
    std::shared_ptr<User> getUser(const std::string& userId);
    void displayAllUsers() const;
    
    bool createGroup(const std::string& groupId);
    bool deleteGroup(const std::string& groupId);
    std::shared_ptr<Group> getGroup(const std::string& groupId);
    void displayAllGroups() const;
    
    bool addUserToGroup(const std::string& userId, const std::string& groupId);
};

#endif