#include "../include/library.h"

void Library::addBook(const Book& book) {
    books.insert(book);
}

void Library::removeBook(const Book& book) {
    books.remove(book);
}

void Library::addReader(const Reader& reader) {
    readers.insert(reader);
}

void Library::removeReader(const Reader& reader) {
    readers.remove(reader);
}

void Library::borrowBook(Book& book, Reader& reader, const std::string& borrowedDate) {
    if (books.contains(book)) {
        book.decreaseCount();

        reader.borrowBook(book, borrowedDate);
    }
}

void Library::returnBook(Book& book, Reader& reader) {
    book.increaseCount();

    reader.returnBook(book);
}

void Library::displayAllBooks() const {
    books.display();
}

void Library::displayAvailableBooks() const {
    books.displayAvailable();
}

void Library::displayAllReaders() const {
    readers.display();
}

void Library::displayBorrowedBooksByReader(const Reader& reader) const {
    reader.displayBorrowedBooks();
}

Book* Library::findBook(const std::string& title, const std::string& author) const {
    return books.find(title, author);
}

BookLinkedList Library::findBooksByAuthor(const std::string& author) const {
    return books.findByAuthor(author);
}

ReaderDoubleLinkedList Library::findReaders(const std::string firstName, const std::string lastName) const {
    return readers.find(lastName, firstName);
}

Reader* Library::findReaderByEmail(const std::string email) const {
    return readers.findByEmail(email);
}

bool Library::isReaderExistsByEmail(const Reader& reader) const {
    return readers.contains(reader);
}

bool Library::isBookExistis(const Book& book) const {
    return books.contains(book);
}

bool Library::isBookAvailable(const Book &book) const {
    return books.isAvailable(book);
}

void Library::addBookCount(const std::string& title, const std::string& author, int count) {
    Book* book = books.find(title, author);

    if (book)
        book->increaseCount(count);
}

ReaderDoubleLinkedList Library::getReaders() const {
    return readers;
}

BookLinkedList Library::getBooks() const {
    return books;
}
