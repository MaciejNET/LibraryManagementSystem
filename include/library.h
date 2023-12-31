#ifndef LIBRARYMANAGEMENTSYSTEM_LIBRARY_H
#define LIBRARYMANAGEMENTSYSTEM_LIBRARY_H

#include "book_linked_list.h"
#include "reader_double_linked_list.h"

class Library
{
public:
    void addBook(const Book &book);
    void removeBook(const Book &book);
    void addReader(const Reader &reader);
    void removeReader(const Reader &reader);
    void borrowBook(Book &book, Reader &reader, const std::string &borrowedDate);
    void returnBook(Book &book, Reader &reader);
    void displayAllBooks() const;
    void displayAvailableBooks() const;
    void displayAllReaders() const;
    void displayBorrowedBooksByReader(const Reader &reader) const;

    Book *findBook(const std::string &title, const std::string &author) const;
    BookLinkedList findBooksByAuthor(const std::string &author) const;

    ReaderDoubleLinkedList findReaders(const std::string firstName, const std::string lastName) const;
    Reader *findReaderByEmail(const std::string email) const;

    bool isReaderExistsByEmail(const Reader &reader) const;
    bool isBookExists(const Book &book) const;
    bool isBookAvailable(const Book &book) const;

    void addBookCount(const std::string &title, const std::string &author, int count);

    ReaderDoubleLinkedList getReaders() const;
    BookLinkedList getBooks() const;

private:
    BookLinkedList mBooks;
    ReaderDoubleLinkedList mReaders;
};

#endif // LIBRARYMANAGEMENTSYSTEM_LIBRARY_H
