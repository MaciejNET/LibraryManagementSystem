#ifndef LIBRARYMANAGEMENTSYSTEM_READER_H
#define LIBRARYMANAGEMENTSYSTEM_READER_H

#include <string>
#include "borrowed_books_linked_list.h"

class Reader
{
public:
    Reader(std::string firstName, std::string lastName, std::string email);
    Reader(const Reader &other);
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getEmail() const;
    std::string getFullName() const;
    void borrowBook(const Book &book, const std::string &borrowedDate);
    void insertBook(const Book &book, const std::string &borrowedDate);
    void returnBook(const Book &book);
    void displayBorrowedBooks() const;
    const BorrowedBooksLinkedList &getBorrowedBooks() const;
    bool hasBook(const Book &book) const;
    bool operator==(const Reader &other) const;
    bool operator!=(const Reader &other) const;

private:
    std::string mFirstName;
    std::string mLastName;
    std::string mEmail;
    BorrowedBooksLinkedList mBorrowedBooks;
};

#endif // LIBRARYMANAGEMENTSYSTEM_READER_H
