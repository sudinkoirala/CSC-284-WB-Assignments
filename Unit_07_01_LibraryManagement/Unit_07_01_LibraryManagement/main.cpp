#include "Library.h"
#include <iostream>

int main() {
    Library lib;

    lib.addBook(Book("1984", "George Orwell", "ISBN001", 1949));
    lib.addBook(Book("The Hobbit", "J.R.R. Tolkien", "ISBN002", 1937));
    lib.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "ISBN003", 1925));

    lib.registerMember(Member("Alice", "M001"));
    lib.registerMember(Member("Bob", "M002"));

    int choice;
    do {
        std::cout << "\n==== Library Menu ====\n";
        std::cout << "1. Display Books\n2. Display Members\n3. Borrow Book\n4. Return Book\n5. Exit\nChoice: ";
        std::cin >> choice;

        std::string memberID, isbn;

        switch (choice) {
            case 1:
                lib.displayAllBooks();
                break;
            case 2:
                lib.displayAllMembers();
                break;
            case 3:
                std::cout << "Enter member ID: "; std::cin >> memberID;
                std::cout << "Enter ISBN: "; std::cin >> isbn;
                lib.borrowBook(memberID, isbn);
                break;
            case 4:
                std::cout << "Enter member ID: "; std::cin >> memberID;
                std::cout << "Enter ISBN: "; std::cin >> isbn;
                lib.returnBook(memberID, isbn);
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}

