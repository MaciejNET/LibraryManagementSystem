#ifndef LIBRARYMANAGEMENTSYSTEM_BORROWED_BOOKS_LINKED_LIST_H
#define LIBRARYMANAGEMENTSYSTEM_BORROWED_BOOKS_LINKED_LIST_H

#include <iostream>
#include <utility>
#include "book.h"
#include "console.h"

class BorrowedBooksLinkedList
{
public:
    struct Node
    {
        Book book;
        std::string borrowedDate;
        Node *next;

        Node(Book book, std::string borrowedDate) : book(std::move(book)), borrowedDate(std::move(borrowedDate)), next(nullptr) {}
    };

public:
    BorrowedBooksLinkedList() : mHead(nullptr), mSize(0) {}
    ~BorrowedBooksLinkedList();

    void insert(const Book &book, const std::string &borrowedDate);
    void remove(const Book &book);
    bool contains(const Book &book) const;
    Node *getFirst() const;
    int getSize() const;
    void display() const;

private:
    Node *mHead;
    int mSize;
};

#endif // LIBRARYMANAGEMENTSYSTEM_BORROWED_BOOKS_LINKED_LIST_H
