//
// Created by Maciej Deroń on 23/06/2023.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_BOOK_LINKED_LIST_H
#define LIBRARYMANAGEMENTSYSTEM_BOOK_LINKED_LIST_H

#include "book.h"

#include <iostream>
#include <utility>

class BookLinkedList {
public:
    struct Node {
        Book data;
        Node* next;

        explicit Node(Book  data) : data(std::move(data)), next(nullptr) {}
    };

private:
    Node* head;
    int size;

public:
    BookLinkedList() : head(nullptr), size(0) {}
    ~BookLinkedList();

    void insert(const Book& book);
    void remove(const Book& book);
    bool contains(const Book& book) const;
    Book* find(const std::string& title, const std::string& author) const;
    BookLinkedList findByAuthor(const std::string& author) const;
    Node* getFirst() const;
    int getSize() const;
    void display() const;
    void displayAvailable() const;
    bool isAvailable(const Book& book) const;
};


#endif //LIBRARYMANAGEMENTSYSTEM_BOOK_LINKED_LIST_H
