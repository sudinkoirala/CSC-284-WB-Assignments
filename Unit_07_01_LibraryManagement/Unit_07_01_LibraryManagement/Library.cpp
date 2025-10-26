#include "Library.h"

void Library::addBook(const Book& b) {
    books.push_back(b);
}

void Library::removeBook(const std::string& isbn) {
    auto it = std::remove_if(books.begin(), books.end(),
                             [&](const Book& b){ return b.getISBN() == isbn; });
    if (it != books.end()) {
        books.erase(it, books.end());
        std::cout << "Book removed.\n";
    } else {
        std::cout << "Book not found.\n";
    }
}

void Library::registerMember(const Member& m) {
    members.push_back(m);
}

void Library::borrowBook(const std::string& memberID, const std::string& isbn) {
    auto bookIt = std::find_if(books.begin(), books.end(),
                               [&](const Book& b){ return b.getISBN() == isbn; });
    auto memberIt = std::find_if(members.begin(), members.end(),
                                 [&](const Member& m){ return m.getID() == memberID; });

    if (bookIt != books.end() && memberIt != members.end()) {
        if (bookIt->isAvailable()) {
            bookIt->setAvailable(false);
            memberIt->borrowBook(isbn);
            std::cout << "Book borrowed successfully.\n";
        } else {
            std::cout << "Book already borrowed.\n";
        }
    } else {
        std::cout << "Book or member not found.\n";
    }
}

void Library::returnBook(const std::string& memberID, const std::string& isbn) {
    auto bookIt = std::find_if(books.begin(), books.end(),
                               [&](const Book& b){ return b.getISBN() == isbn; });
    auto memberIt = std::find_if(members.begin(), members.end(),
                                 [&](const Member& m){ return m.getID() == memberID; });

    if (bookIt != books.end() && memberIt != members.end()) {
        if (memberIt->hasBook(isbn)) {
            bookIt->setAvailable(true);
            memberIt->returnBook(isbn);
            std::cout << "Book returned successfully.\n";
        } else {
            std::cout << "Member didn’t borrow this book.\n";
        }
    } else {
        std::cout << "Book or member not found.\n";
    }
}

void Library::displayAllBooks() const {
    std::cout << "\nLibrary Books:\n";
    for (const auto& b : books) b.display();
}

void Library::displayAllMembers() const {
    std::cout << "\nRegistered Members:\n";
    for (const auto& m : members) m.display();
}

