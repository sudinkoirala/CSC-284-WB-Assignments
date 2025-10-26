#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Member.h"
#include <vector>
#include <string>
#include <algorithm>

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:
    void addBook(const Book& b);
    void removeBook(const std::string& isbn);
    void registerMember(const Member& m);
    void borrowBook(const std::string& memberID, const std::string& isbn);
    void returnBook(const std::string& memberID, const std::string& isbn);
    void displayAllBooks() const;
    void displayAllMembers() const;
};
#endif


