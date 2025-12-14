#include "User.h"

User::User(int fd, const std::string& name)
    : socketFd(fd), username(name), currentRoom(nullptr) {}

int User::getSocket() const {
    return socketFd;
}

const std::string& User::getUsername() const {
    return username;
}

void User::setRoom(Room* room) {
    currentRoom = room;
}

Room* User::getRoom() const {
    return currentRoom;
}
