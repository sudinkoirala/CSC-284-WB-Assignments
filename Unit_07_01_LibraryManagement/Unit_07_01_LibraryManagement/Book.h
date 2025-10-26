#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

class Book {
private:
    std::string title, author, isbn;
    int year;
    bool available;

public:
    Book(std::string t, std::string a, std::string i, int y)
        : title(t), author(a), isbn(i), year(y), available(true) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getISBN() const { return isbn; }
    int getYear() const { return year; }
    bool isAvailable() const { return available; }

    void setAvailable(bool a) { available = a; }

    void display() const {
        std::cout << title << " by " << author
                  << " (" << year << ") [ISBN: " << isbn << "] - "
                  << (available ? "Available" : "Borrowed") << "\n";
    }
};
#endif

