#include "../include/library.h"

void Library::addBook(const Book &book)
{
    mBooks.insert(book);
}

void Library::removeBook(const Book &book)
{
    mBooks.remove(book);
}

void Library::addReader(const Reader &reader)
{
    mReaders.insert(reader);
}

void Library::removeReader(const Reader &reader)
{
    mReaders.remove(reader);
}

void Library::borrowBook(Book &book, Reader &reader, const std::string &borrowedDate)
{
    if (mBooks.contains(book))
    {
        book.decreaseCount();

        reader.borrowBook(book, borrowedDate);
    }
}

void Library::returnBook(Book &book, Reader &reader)
{
    book.increaseCount();

    reader.returnBook(book);
}

void Library::displayAllBooks() const
{
    mBooks.display();
}

void Library::displayAvailableBooks() const
{
    mBooks.displayAvailable();
}

void Library::displayAllReaders() const
{
    mReaders.display();
}

void Library::displayBorrowedBooksByReader(const Reader &reader) const
{
    reader.displayBorrowedBooks();
}

Book *Library::findBook(const std::string &title, const std::string &author) const
{
    return mBooks.find(title, author);
}

BookLinkedList Library::findBooksByAuthor(const std::string &author) const
{
    return mBooks.findByAuthor(author);
}

ReaderDoubleLinkedList Library::findReaders(const std::string firstName, const std::string lastName) const
{
    return mReaders.find(lastName, firstName);
}

Reader *Library::findReaderByEmail(const std::string email) const
{
    return mReaders.findByEmail(email);
}

bool Library::isReaderExistsByEmail(const Reader &reader) const
{
    return mReaders.contains(reader);
}

bool Library::isBookExists(const Book &book) const
{
    return mBooks.contains(book);
}

bool Library::isBookAvailable(const Book &book) const
{
    return mBooks.isAvailable(book);
}

void Library::addBookCount(const std::string &title, const std::string &author, int count)
{
    Book *book = mBooks.find(title, author);

    if (book)
        book->increaseCount(count);
}

ReaderDoubleLinkedList Library::getReaders() const
{
    return mReaders;
}

BookLinkedList Library::getBooks() const
{
    return mBooks;
}
