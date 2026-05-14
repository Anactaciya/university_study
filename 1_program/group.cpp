#include "group.h"
#include "user.h"
#include <iostream>
#include <algorithm>

Group::Group(const std::string& id) : groupId(id) {}

std::string Group::getGroupId() const {
    return groupId;
}

const std::vector<std::shared_ptr<User>>& Group::getUsers() const {
    return users;
}

void Group::addUser(std::shared_ptr<User> user) {
    if (user && !hasUser(user->getUserId())) {
        users.push_back(user);
        user->setGroup(shared_from_this());
    }
}

void Group::removeUser(const std::string& userId) {
    auto it = std::find_if(users.begin(), users.end(),
        [&userId](const std::shared_ptr<User>& user) {
            return user->getUserId() == userId;
        });
    
    if (it != users.end()) {
        (*it)->setGroup(nullptr);
        users.erase(it);
    }
}

bool Group::hasUser(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
        [&userId](const std::shared_ptr<User>& user) {
            return user->getUserId() == userId;
        });
    return it != users.end();
}

void Group::display() const {
    std::cout << "Group ID: " << groupId << std::endl;
    std::cout << "Members (" << users.size() << "):" << std::endl;
    
    if (users.empty()) {
        std::cout << "  No users in this group" << std::endl;
    } else {
        for (const auto& user : users) {
            std::cout << "  - " << user->getUsername() 
                      << " (" << user->getUserId() << ")" << std::endl;
        }
    }
}