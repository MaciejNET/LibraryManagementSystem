//
// Created by Maciej Deroń on 23/06/2023.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_READER_H
#define LIBRARYMANAGEMENTSYSTEM_READER_H

#include <string>
#include "borrowed_books_linked_list.h"

class Reader {
private:
    std::string firstName;
    std::string lastName;
    std::string email;
    BorrowedBooksLinkedList borrowedBooks;

public:
    Reader(std::string  firstName, std::string  lastName, std::string  email);
    Reader(const Reader& other);
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getEmail() const;
    std::string getFullName() const;
    void borrowBook(const Book& book, const std::string& borrowedDate);
    void returnBook(const Book& book);
    void displayBorrowedBooks() const;
    const BorrowedBooksLinkedList& getBorrowedBooks() const;
    bool hasBook(const Book& book) const;
    bool operator==(const Reader& other) const;
    bool operator!=(const Reader& other) const;
};


#endif //LIBRARYMANAGEMENTSYSTEM_READER_H
