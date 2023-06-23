//
// Created by Maciej Deroń on 23/06/2023.
//

#include "../include/reader.h"

#include <utility>

Reader::Reader(std::string firstName, std::string lastName, std::string email) : firstName(std::move(firstName)), lastName(std::move(lastName)), email(std::move(email)), borrowedBooks(){
}

Reader::Reader(const Reader &other) : firstName(other.firstName), lastName(other.lastName), email(other.email), borrowedBooks() {
    const BorrowedBooksLinkedList& otherBorrowedBooks = other.borrowedBooks;
    BorrowedBooksLinkedList::Node* borrowedNode = otherBorrowedBooks.getFirst();
    while (borrowedNode) {
        borrowedBooks.insert(borrowedNode->book, borrowedNode->borrowedDate);
        borrowedNode = borrowedNode->next;
    }
}

std::string Reader::getFirstName() const{
    return firstName;
}

std::string Reader::getLastName() const {
    return lastName;
}

std::string Reader::getEmail() const {
    return email;
}

std::string Reader::getFullName() const {
    return firstName + " " + lastName;
}

void Reader::borrowBook(const Book &book, const std::string &borrowedDate) {
    borrowedBooks.insert(book, borrowedDate);
    Console::printSuccess("Książka \"" + book.getTitle() + "\" została wypożyczona przez " + getFullName() + " - " + borrowedDate + ".");
}

void Reader::insertBook(const Book &book, const std::string &borrowedDate) {
    borrowedBooks.insert(book, borrowedDate);
}

void Reader::returnBook(const Book &book) {
    borrowedBooks.remove(book);
    Console::printSuccess("Książka \"" + book.getTitle() + "\" została zwrócona przez " + getFullName() + ".");
}

void Reader::displayBorrowedBooks() const {
    Console::clearConsole();
    std::cout << "Wypożyczone ksiązki przez " << getFullName() << ":" << std::endl;
    borrowedBooks.display();
    Console::waitForInput();
}

const BorrowedBooksLinkedList& Reader::getBorrowedBooks() const {
    return borrowedBooks;
}

bool Reader::hasBook(const Book &book) const {
    return getBorrowedBooks().contains(book);
}

bool Reader::operator==(const Reader& other) const {
    return (firstName == other.firstName && lastName == other.lastName);
}

bool Reader::operator!=(const Reader& other) const {
    return (firstName != other.firstName || lastName != other.lastName);
}

