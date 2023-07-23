#include "../include/borrowed_books_linked_list.h"

BorrowedBooksLinkedList::~BorrowedBooksLinkedList()
{
    Node *current = mHead;
    while (current)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

void BorrowedBooksLinkedList::insert(const Book &book, const std::string &borrowedDate)
{
    Node *newNode = new Node(book, borrowedDate);

    if (!mHead || borrowedDate < mHead->borrowedDate)
    {
        newNode->next = mHead;
        mHead = newNode;
    }
    else
    {
        Node *current = mHead;
        while (current->next && current->next->borrowedDate < borrowedDate)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    mSize++;
}

void BorrowedBooksLinkedList::remove(const Book &book)
{
    if (!mHead)
    {
        return;
    }

    if (mHead->book == book)
    {
        Node *temp = mHead;
        mHead = mHead->next;
        delete temp;
        mSize--;
        return;
    }

    Node *current = mHead;
    while (current->next && current->next->book != book)
    {
        current = current->next;
    }

    if (current->next)
    {
        Node *temp = current->next;
        current->next = current->next->next;
        delete temp;
        mSize--;
    }
}

bool BorrowedBooksLinkedList::contains(const Book &book) const
{
    Node *current = mHead;
    while (current)
    {
        if (current->book == book)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

BorrowedBooksLinkedList::Node *BorrowedBooksLinkedList::getFirst() const
{
    return mHead;
}

int BorrowedBooksLinkedList::getSize() const
{
    return mSize;
}

void BorrowedBooksLinkedList::display() const
{
    Node *current = mHead;
    Console::clearConsole();
    std::cout << "Borrowed books by reader:" << std::endl;
    while (current)
    {
        std::cout << "Title: " << current->book.getTitle() << " | Author: " << current->book.getAuthor() << " | Borrowed date: " << current->borrowedDate << std::endl;
        current = current->next;
    }
    Console::waitForInput();
}
