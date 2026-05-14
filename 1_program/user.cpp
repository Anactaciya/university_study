#include "user.h"
#include "group.h"
#include <iostream>

User::User(const std::string& id, const std::string& name, 
           const std::string& house, const std::string& fullName,
           const std::string& patronus, const std::string& wand)
    : userId(id), username(name), house(house), fullName(fullName), 
      patronus(patronus), wand(wand) {}

std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getHouse() const { return house; }
std::string User::getFullName() const { return fullName; }
std::string User::getPatronus() const { return patronus; }
std::string User::getWand() const { return wand; }

std::shared_ptr<Group> User::getGroup() const { return group.lock(); }

void User::setGroup(std::shared_ptr<Group> grp) { group = grp; }
void User::setUsername(const std::string& name) { username = name; }
void User::setHouse(const std::string& house) { this->house = house; }
void User::setFullName(const std::string& name) { fullName = name; }
void User::setPatronus(const std::string& patronus) { this->patronus = patronus; }
void User::setWand(const std::string& wand) { this->wand = wand; }

void User::display() const {
    std::cout << "═══════════════════════════════════" << std::endl;
    std::cout << "Wizard ID: " << userId << std::endl;
    std::cout << "Name: " << fullName << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "House: " << (house.empty() ? "Not sorted yet" : house) << std::endl;
    if (!patronus.empty()) {
        std::cout << "Patronus: " << patronus << std::endl;
    }
    if (!wand.empty()) {
        std::cout << "Wand: " << wand << std::endl;
    }
    auto grp = group.lock();
    if (grp) {
        std::cout << "Member of: " << grp->getGroupId() << std::endl;
    }
    std::cout << "═══════════════════════════════════" << std::endl;
}