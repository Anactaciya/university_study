#ifndef USER_H
#define USER_H

#include <string>
#include <memory>

class Group;

class User {
private:
    std::string userId;
    std::string username;
    std::string house;
    std::string fullName;
    std::string patronus;
    std::string wand;
    std::weak_ptr<Group> group;

public:
    User(const std::string& id, const std::string& name, 
         const std::string& house, const std::string& fullName,
         const std::string& patronus = "", const std::string& wand = "");
    
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getHouse() const;
    std::string getFullName() const;
    std::string getPatronus() const;
    std::string getWand() const;
    std::shared_ptr<Group> getGroup() const;
    
    void setGroup(std::shared_ptr<Group> grp);
    void setUsername(const std::string& name);
    void setHouse(const std::string& house);
    void setFullName(const std::string& name);
    void setPatronus(const std::string& patronus);
    void setWand(const std::string& wand);
    
    void display() const;
};

#endif