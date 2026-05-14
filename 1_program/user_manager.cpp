#include "user_manager.h"
#include <iostream>
#include <algorithm>

bool UserManager::createUser(const std::string& userId, const std::string& username,
                            const std::string& house, const std::string& fullName,
                            const std::string& patronus, const std::string& wand) {
    if (users.find(userId) != users.end()) {
        std::cout << "Error: User with ID " << userId << " already exists!" << std::endl;
        return false;
    }
    
    auto user = std::make_shared<User>(userId, username, house, fullName, patronus, wand);
    users[userId] = user;
    std::cout << "Wizard " << username << " created successfully!" << std::endl;
    return true;
}

bool UserManager::deleteUser(const std::string& userId) {
    auto it = users.find(userId);
    if (it == users.end()) {
        std::cout << "Error: User with ID " << userId << " not found!" << std::endl;
        return false;
    }
    
    auto group = it->second->getGroup();
    if (group) {
        group->removeUser(userId);
    }
    
    users.erase(it);
    std::cout << "User " << userId << " deleted successfully!" << std::endl;
    return true;
}

std::shared_ptr<User> UserManager::getUser(const std::string& userId) {
    auto it = users.find(userId);
    if (it != users.end()) {
        return it->second;
    }
    return nullptr;
}

void UserManager::displayAllUsers() const {
    if (users.empty()) {
        std::cout << "No wizards found at Hogwarts!" << std::endl;
        return;
    }
    
    std::cout << "\n=== All Wizards (" << users.size() << ") ===" << std::endl;
    for (const auto& pair : users) {
        std::cout << "\n";
        pair.second->display();
        std::cout << "------------------------" << std::endl;
    }
}

bool UserManager::createGroup(const std::string& groupId) {
    if (groups.find(groupId) != groups.end()) {
        std::cout << "Error: Group with ID " << groupId << " already exists!" << std::endl;
        return false;
    }
    
    auto group = std::make_shared<Group>(groupId);
    groups[groupId] = group;
    std::cout << "Group " << groupId << " created successfully!" << std::endl;
    return true;
}

bool UserManager::deleteGroup(const std::string& groupId) {
    auto it = groups.find(groupId);
    if (it == groups.end()) {
        std::cout << "Error: Group with ID " << groupId << " not found!" << std::endl;
        return false;
    }
    
    for (const auto& user : it->second->getUsers()) {
        user->setGroup(nullptr);
    }
    
    groups.erase(it);
    std::cout << "Group " << groupId << " deleted successfully!" << std::endl;
    return true;
}

std::shared_ptr<Group> UserManager::getGroup(const std::string& groupId) {
    auto it = groups.find(groupId);
    if (it != groups.end()) {
        return it->second;
    }
    return nullptr;
}

void UserManager::displayAllGroups() const {
    if (groups.empty()) {
        std::cout << "No groups found at Hogwarts!" << std::endl;
        return;
    }
    
    std::cout << "\n=== All Groups (" << groups.size() << ") ===" << std::endl;
    for (const auto& pair : groups) {
        std::cout << "\n";
        pair.second->display();
        std::cout << "------------------------" << std::endl;
    }
}

bool UserManager::addUserToGroup(const std::string& userId, const std::string& groupId) {
    auto user = getUser(userId);
    auto group = getGroup(groupId);
    
    if (!user) {
        std::cout << "Error: Wizard " << userId << " not found at Hogwarts!" << std::endl;
        return false;
    }
    
    if (!group) {
        std::cout << "Error: Group " << groupId << " not found!" << std::endl;
        return false;
    }
    
    auto currentGroup = user->getGroup();
    if (currentGroup) {
        currentGroup->removeUser(userId);
    }
    
    group->addUser(user);
    std::cout << "User " << userId << " added to group " << groupId << std::endl;
    return true;
}