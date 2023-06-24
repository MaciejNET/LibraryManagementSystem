#ifndef LIBRARYMANAGEMENTSYSTEM_READER_DOUBLE_LINKED_LIST_H
#define LIBRARYMANAGEMENTSYSTEM_READER_DOUBLE_LINKED_LIST_H

#include <utility>

#include "reader.h"

class ReaderDoubleLinkedList {
public:
    struct Node {
        Reader data;
        Node* prev;
        Node* next;

        Node(Reader data) : data(std::move(data)), prev(nullptr), next(nullptr) {}
    };

private:
    Node* head;
    Node* tail;
    int size;

public:
    ReaderDoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~ReaderDoubleLinkedList();

    void insert(const Reader& reader);
    void remove(const Reader& reader);
    bool contains(const Reader& reader) const;
    ReaderDoubleLinkedList find(const std::string& lastName, const std::string& firstName) const;
    Reader* findByEmail(const std::string& email) const;
    Node* getFirst() const;
    Reader* getFirstReader() const;
    int getSize() const;
    void display() const;
};


#endif //LIBRARYMANAGEMENTSYSTEM_READER_DOUBLE_LINKED_LIST_H
