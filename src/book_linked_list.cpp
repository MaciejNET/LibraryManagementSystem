#include "../include/book_linked_list.h"
BookLinkedList::~BookLinkedList()
{
    Node *current = mHead;
    while (current)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

void BookLinkedList::insert(const Book &book)
{
    Node *newNode = new Node(book);

    if (!mHead || book.getTitle() < mHead->data.getTitle())
    {
        newNode->next = mHead;
        mHead = newNode;
    }
    else
    {
        Node *current = mHead;
        while (current->next && current->next->data.getTitle() < book.getTitle())
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    mSize++;
}

void BookLinkedList::remove(const Book &book)
{
    if (!mHead)
    {
        return;
    }

    if (mHead->data == book)
    {
        Node *temp = mHead;
        mHead = mHead->next;
        delete temp;
        mSize--;
        return;
    }

    Node *current = mHead;
    while (current->next && current->next->data != book)
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

bool BookLinkedList::contains(const Book &book) const
{
    Node *current = mHead;
    while (current)
    {
        if (current->data == book)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

Book *BookLinkedList::find(const std::string &title, const std::string &author) const
{
    Node *current = mHead;
    Book temp(title, author, 1);
    while (current)
    {
        if (current->data == temp)
        {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

BookLinkedList BookLinkedList::findByAuthor(const std::string &author) const
{
    BookLinkedList matchingBooks;
    Node *current = mHead;

    while (current)
    {
        if (current->data.getAuthor() == author)
        {
            matchingBooks.insert(current->data);
        }
        current = current->next;
    }

    return matchingBooks;
}

BookLinkedList::Node *BookLinkedList::getFirst() const
{
    return mHead;
}

int BookLinkedList::getSize() const
{
    return mSize;
}

void BookLinkedList::display() const
{
    Node *current = mHead;
    Console::clearConsole();
    std::cout << "Books:" << std::endl;
    while (current)
    {
        std::cout << "Title: " << current->data.getTitle() << " | Author: " << current->data.getAuthor() << " | Amount: " << current->data.getCount() << std::endl;
        current = current->next;
    }
    Console::waitForInput();
}

void BookLinkedList::displayAvailable() const
{
    Node *current = mHead;
    Console::clearConsole();
    std::cout << "Available books:" << std::endl;
    while (current)
    {
        if (current->data.isAvailable())
        {
            std::cout << "Title: " << current->data.getTitle() << " | Author: " << current->data.getAuthor() << " | Amount: " << current->data.getCount() << std::endl;
        }
        current = current->next;
    }
    Console::waitForInput();
}

bool BookLinkedList::isAvailable(const Book &book) const
{
    Node *current = mHead;
    while (current)
    {
        if (current->data == book && current->data.isAvailable())
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
