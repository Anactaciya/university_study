#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#include <memory>

class User;

class Group : public std::enable_shared_from_this<Group> {
private:
    std::string groupId;
    std::vector<std::shared_ptr<User>> users;

public:
    Group(const std::string& id);
    
    std::string getGroupId() const;
    const std::vector<std::shared_ptr<User>>& getUsers() const;
    
    void addUser(std::shared_ptr<User> user);
    void removeUser(const std::string& userId);
    bool hasUser(const std::string& userId) const;
    
    void display() const;
};

#endif