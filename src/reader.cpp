#include "../include/reader.h"

#include <utility>

Reader::Reader(std::string firstName, std::string lastName, std::string email) : mFirstName(std::move(firstName)), mLastName(std::move(lastName)), mEmail(std::move(email)), mBorrowedBooks()
{
}

Reader::Reader(const Reader &other) : mFirstName(other.mFirstName), mLastName(other.mLastName), mEmail(other.mEmail), mBorrowedBooks()
{
    const BorrowedBooksLinkedList &otherBorrowedBooks = other.mBorrowedBooks;
    BorrowedBooksLinkedList::Node *borrowedNode = otherBorrowedBooks.getFirst();
    while (borrowedNode)
    {
        mBorrowedBooks.insert(borrowedNode->book, borrowedNode->borrowedDate);
        borrowedNode = borrowedNode->next;
    }
}

std::string Reader::getFirstName() const
{
    return mFirstName;
}

std::string Reader::getLastName() const
{
    return mLastName;
}

std::string Reader::getEmail() const
{
    return mEmail;
}

std::string Reader::getFullName() const
{
    return mFirstName + " " + mLastName;
}

void Reader::borrowBook(const Book &book, const std::string &borrowedDate)
{
    mBorrowedBooks.insert(book, borrowedDate);
    Console::printSuccess("Book \"" + book.getTitle() + "\" has been borrowed by " + getFullName() + " - " + borrowedDate + ".");
}

void Reader::insertBook(const Book &book, const std::string &borrowedDate)
{
    mBorrowedBooks.insert(book, borrowedDate);
}

void Reader::returnBook(const Book &book)
{
    mBorrowedBooks.remove(book);
    Console::printSuccess("Book \"" + book.getTitle() + "\" has been returned by " + getFullName() + ".");
}

void Reader::displayBorrowedBooks() const
{
    Console::clearConsole();
    std::cout << "Borrowed books by " << getFullName() << ":" << std::endl;
    mBorrowedBooks.display();
    Console::waitForInput();
}

const BorrowedBooksLinkedList &Reader::getBorrowedBooks() const
{
    return mBorrowedBooks;
}

bool Reader::hasBook(const Book &book) const
{
    return getBorrowedBooks().contains(book);
}

bool Reader::operator==(const Reader &other) const
{
    return (mFirstName == other.mFirstName && mLastName == other.mLastName);
}

bool Reader::operator!=(const Reader &other) const
{
    return (mFirstName != other.mFirstName || mLastName != other.mLastName);
}
