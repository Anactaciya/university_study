#include "user_manager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>


std::vector<std::string> parseCommand(const std::string& input) {
    std::vector<std::string> tokens;
    std::string current;
    bool inQuotes = false;
    
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ' ' && !inQuotes) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }
    
    if (!current.empty()) {
        tokens.push_back(current);
    }
    
    return tokens;
}



void handleCreateUser(UserManager& manager, const std::vector<std::string>& tokens) {
    if (tokens.size() < 5) {
        std::cout << "Mandatory arguments are missing" << std::endl;
        return;
    }
    
    std::string userId = tokens[1];
    std::string username = tokens[2];
    std::string house = tokens[3];
    std::string fullName = tokens[4];
    std::string patronus = tokens.size() > 5 ? tokens[5] : "";
    std::string wand = tokens.size() > 6 ? tokens[6] : "";
    
    manager.createUser(userId, username, house, fullName, patronus, wand);
}

void handleDeleteUser(UserManager& manager, const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        std::cout << "Mandatory arguments are missing" << std::endl;
        return;
    }
    manager.deleteUser(tokens[1]);
}

void handleGetUser(UserManager& manager, const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        std::cout << "Mandatory arguments are missing" << std::endl;
        return;
    }
    
    auto user = manager.getUser(tokens[1]);
    if (user) {
        user->display();
    } else {
        std::cout << "Wizard not found at Hogwarts!" << std::endl;
    }
}

void handleCreateGroup(UserManager& manager, const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        std::cout << "Mandatory arguments are missing" << std::endl;
        return;
    }
    manager.createGroup(tokens[1]);
}

void handleDeleteGroup(UserManager& manager, const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        std::cout << "Mandatory arguments are missing" << std::endl;
        return;
    }
    manager.deleteGroup(tokens[1]);
}

void handleGetGroup(UserManager& manager, const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        std::cout << "Mandatory arguments are missing" << std::endl;
        return;
    }
    
    auto group = manager.getGroup(tokens[1]);
    if (group) {
        std::cout << "\n";
        group->display();
    } else {
        std::cout << "Group not found!" << std::endl;
    }
}

void handleAddUserToGroup(UserManager& manager, const std::vector<std::string>& tokens) {
    if (tokens.size() < 3) {
        std::cout << "Mandatory arguments are missing" << std::endl;
        return;
    }
    manager.addUserToGroup(tokens[1], tokens[2]);
}

int main() {
    UserManager manager;
    std::string input;
;
    std::cout << "---- HOGWARTS SCHOOL OF WITCHCRAFT AND WIZARDRY ----" << std::endl;
    std::cout << "\nCOMMANDS:" << std::endl;
    std::cout << "  createUser {userId} {username} {house} \"{fullName}\" [\"{patronus}\"] [\"{wand}\"]" << std::endl;
    std::cout << "  deleteUser {userId}" << std::endl;
    std::cout << "  allUsers" << std::endl;
    std::cout << "  getUser {userId}" << std::endl;
    std::cout << "  createGroup {groupId}" << std::endl;
    std::cout << "  deleteGroup {groupId}" << std::endl;
    std::cout << "  allGroups" << std::endl;
    std::cout << "  getGroup {groupId}" << std::endl;
    std::cout << "  addUserToGroup {userId} {groupId}" << std::endl;
    std::cout << "  help - show this help" << std::endl;
    std::cout << "  exit - exit program" << std::endl;

    
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);
        
        if (input.empty()) continue;
        
        std::vector<std::string> tokens = parseCommand(input);
        
        if (tokens.empty()) continue;
        
        std::string command = tokens[0];
        
        if (command == "exit" || command == "quit") {
            std::cout << "\n✨ Farewell, young wizard! Until next time! ✨" << std::endl;
            break;
        } else if (command == "createUser") {
            handleCreateUser(manager, tokens);
        } else if (command == "deleteUser") {
            handleDeleteUser(manager, tokens);
        } else if (command == "allUsers") {
            manager.displayAllUsers();
        } else if (command == "getUser") {
            handleGetUser(manager, tokens);
        } else if (command == "createGroup") {
            handleCreateGroup(manager, tokens);
        } else if (command == "deleteGroup") {
            handleDeleteGroup(manager, tokens);
        } else if (command == "allGroups") {
            manager.displayAllGroups();
        } else if (command == "getGroup") {
            handleGetGroup(manager, tokens);
        } else if (command == "addUserToGroup") {
            handleAddUserToGroup(manager, tokens);
        } else {
            std::cout << "Unknown spell!" << std::endl;
        }
    }
    
    return 0;
}