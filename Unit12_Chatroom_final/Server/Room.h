#pragma once
#include <string>
#include <set>
#include <mutex>

class User;

// Represents a chat room
class Room {
public:
    Room(const std::string& roomName);

    const std::string& getName() const;

    void addUser(User* user);
    void removeUser(User* user);
    void sendToRoom(const std::string& msg, User* sender);

private:
    std::string name;
    std::set<User*> users;
    std::mutex roomLock;
};
