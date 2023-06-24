#include "../include/book_linked_list.h"
BookLinkedList::~BookLinkedList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void BookLinkedList::insert(const Book &book) {
    Node* newNode = new Node(book);

    if (!head || book.getTitle() < head->data.getTitle()) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next && current->next->data.getTitle() < book.getTitle()) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    size++;
}

void BookLinkedList::remove(const Book &book) {
    if (!head) {
        return;
    }

    if (head->data == book) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }

    Node* current = head;
    while (current->next && current->next->data != book) {
        current = current->next;
    }

    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        size--;
    }
}

bool BookLinkedList::contains(const Book& book) const {
    Node* current = head;
    while (current) {
        if (current->data == book) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Book* BookLinkedList::find(const std::string& title, const std::string& author) const {
    Node* current = head;
    Book temp(title, author, 1);
    while (current) {
        if (current->data == temp) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

BookLinkedList BookLinkedList::findByAuthor(const std::string &author) const {
    BookLinkedList matchingBooks;
    Node* current = head;

    while (current) {
        if (current->data.getAuthor() == author) {
            matchingBooks.insert(current->data);
        }
        current = current->next;
    }

    return matchingBooks;
}

BookLinkedList::Node* BookLinkedList::getFirst() const {
    return head;
}

int BookLinkedList::getSize() const {
    return size;
}

void BookLinkedList::display() const {
    Node* current = head;
    Console::clearConsole();
    std::cout << "Wszystkie ksiazki:" << std::endl;
    while (current) {
        std::cout << "Tytul: " << current->data.getTitle() << " | Autor: " << current->data.getAuthor() << " | Ilosc: " << current->data.getCount() << std::endl;
        current = current->next;
    }
    Console::waitForInput();
}

void BookLinkedList::displayAvailable() const {
    Node* current = head;
    Console::clearConsole();
    std::cout << "Dostępne ksiazki:" << std::endl;
    while (current) {
        if (current->data.isAvailable()) {
            std::cout << "Tytul: " << current->data.getTitle() << " | Autor: " << current->data.getAuthor() << " | Ilosc: " << current->data.getCount() << std::endl;
        }
        current = current->next;
    }
    Console::waitForInput();
}

bool BookLinkedList::isAvailable(const Book &book) const {
    Node* current = head;
    while (current) {
        if (current->data == book && current->data.isAvailable()) {
            return true;
        }
        current = current->next;
    }
    return false;
}

