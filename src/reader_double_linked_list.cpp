#include "../include/reader_double_linked_list.h"

ReaderDoubleLinkedList::~ReaderDoubleLinkedList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void ReaderDoubleLinkedList::insert(const Reader& reader) {
    Node* newNode = new Node(reader);

    if (!head || (reader.getLastName() + reader.getFirstName()) < (head->data.getLastName() + head->data.getFirstName())) {
        newNode->next = head;
        if (head) {
            head->prev = newNode;
        }
        head = newNode;
    } else {
        Node* current = head;
        while (current->next && (current->next->data.getLastName() + current->next->data.getFirstName()) < (reader.getLastName() + reader.getFirstName())) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next) {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }

    if (!newNode->next) {
        tail = newNode;
    }

    size++;
}

void ReaderDoubleLinkedList::remove(const Reader& reader) {
    if (!head) {
        return;
    }

    if (head->data == reader) {
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
        return;
    }

    Node* current = head;
    while (current->next && current->next->data != reader) {
        current = current->next;
    }

    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        if (current->next) {
            current->next->prev = current;
        } else {
            tail = current;
        }
        delete temp;
        size--;
    }
}

bool ReaderDoubleLinkedList::contains(const Reader& reader) const {
    Node* current = head;
    while (current) {
        if (current->data.getEmail() == reader.getEmail()) {
            return true;
        }
        current = current->next;
    }
    return false;
}

ReaderDoubleLinkedList ReaderDoubleLinkedList::find(const std::string& lastName, const std::string& firstName) const {
    ReaderDoubleLinkedList matchingReaders;

    Node* current = head;
    while (current) {
        if (current->data.getLastName() == lastName && current->data.getFirstName() == firstName) {
            Reader copiedReader(current->data);
            matchingReaders.insert(copiedReader);
        }
        current = current->next;
    }

    return matchingReaders;
}

Reader* ReaderDoubleLinkedList::findByEmail(const std::string &email) const {
    Node* current = head;
    while (current) {
        if (current->data.getEmail() == email) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

ReaderDoubleLinkedList::Node* ReaderDoubleLinkedList::getFirst() const {
    return head;
}

Reader* ReaderDoubleLinkedList::getFirstReader() const {
    if (head) {
        return &(head->data);
    }
    return nullptr;
}

int ReaderDoubleLinkedList::getSize() const {
    return size;
}

void ReaderDoubleLinkedList::display() const {
    Node* current = head;
    Console::clearConsole();
    std::cout << "Wszyscy czytelnicy: " << std::endl;
    while (current) {
        std::cout << "Imie i nazwisko: " << current->data.getFullName() << " | Email: " << current->data.getEmail() << std::endl;
        current = current->next;
    }
    Console::waitForInput();
}
