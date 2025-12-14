#pragma once
#include <string>

class Room;

// Represents a connected client
class User {
public:
    User(int fd, const std::string& name);

    int getSocket() const;
    const std::string& getUsername() const;

    void setRoom(Room* room);
    Room* getRoom() const;

private:
    int socketFd;
    std::string username;
    Room* currentRoom;
};
