#include "Room.h"
#include "User.h"
#include <unistd.h>

Room::Room(const std::string& roomName) : name(roomName) {}

const std::string& Room::getName() const {
    return name;
}

void Room::addUser(User* user) {
    std::lock_guard<std::mutex> guard(roomLock);
    users.insert(user);
}

void Room::removeUser(User* user) {
    std::lock_guard<std::mutex> guard(roomLock);
    users.erase(user);
}

void Room::sendToRoom(const std::string& msg, User* sender) {
    std::lock_guard<std::mutex> guard(roomLock);
    for (User* u : users) {
        if (sender && u == sender) continue;
        send(u->getSocket(), msg.c_str(), msg.size(), 0);
    }
}
