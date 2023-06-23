//
// Created by Maciej Deroń on 23/06/2023.
//

#include "../include/borrowed_books_linked_list.h"

BorrowedBooksLinkedList::~BorrowedBooksLinkedList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void BorrowedBooksLinkedList::insert(const Book& book, const std::string& borrowedDate) {
    Node* newNode = new Node(book, borrowedDate);

    if (!head || borrowedDate < head->borrowedDate) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next && current->next->borrowedDate < borrowedDate) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    size++;
}

void BorrowedBooksLinkedList::remove(const Book& book) {
    if (!head) {
        return;
    }

    if (head->book == book) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }

    Node* current = head;
    while (current->next && current->next->book != book) {
        current = current->next;
    }

    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        size--;
    }
}

bool BorrowedBooksLinkedList::contains(const Book &book) const {
    Node* current = head;
    while (current) {
        if (current->book == book) {
            return true;
        }

        current = current->next;
    }

    return false;
}

BorrowedBooksLinkedList::Node* BorrowedBooksLinkedList::getFirst() const {
    return head;
}

int BorrowedBooksLinkedList::getSize() const {
    return size;
}

void BorrowedBooksLinkedList::display() const {
    Node* current = head;
    while (current) {
        std::cout << "Title: " << current->book.getTitle() << " | Author: " << current->book.getAuthor() << " | Borrowed date: " << current->borrowedDate << std::endl;
        current = current->next;
    }
}
