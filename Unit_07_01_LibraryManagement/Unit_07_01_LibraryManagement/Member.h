#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Member {
private:
    std::string name, memberID;
    std::vector<std::string> borrowedBooks; // ISBNs

public:
    Member(std::string n, std::string id) : name(n), memberID(id) {}

    std::string getName() const { return name; }
    std::string getID() const { return memberID; }

    void borrowBook(const std::string& isbn) {
        borrowedBooks.push_back(isbn);
    }

    void returnBook(const std::string& isbn) {
        auto it = std::remove(borrowedBooks.begin(), borrowedBooks.end(), isbn);
        borrowedBooks.erase(it, borrowedBooks.end());
    }

    bool hasBook(const std::string& isbn) const {
        return std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn) != borrowedBooks.end();
    }

    void display() const {
        std::cout << "Member: " << name << " (ID: " << memberID << ")\nBorrowed Books: ";
        if (borrowedBooks.empty()) std::cout << "None";
        else for (const auto& b : borrowedBooks) std::cout << b << " ";
        std::cout << "\n";
    }
};
#endif

