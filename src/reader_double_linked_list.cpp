#include "../include/reader_double_linked_list.h"

ReaderDoubleLinkedList::~ReaderDoubleLinkedList()
{
    Node *current = mHead;
    while (current)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

void ReaderDoubleLinkedList::insert(const Reader &reader)
{
    Node *newNode = new Node(reader);

    if (!mHead || (reader.getLastName() + reader.getFirstName()) < (mHead->data.getLastName() + mHead->data.getFirstName()))
    {
        newNode->next = mHead;
        if (mHead)
        {
            mHead->prev = newNode;
        }
        mHead = newNode;
    }
    else
    {
        Node *current = mHead;
        while (current->next && (current->next->data.getLastName() + current->next->data.getFirstName()) < (reader.getLastName() + reader.getFirstName()))
        {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next)
        {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }

    if (!newNode->next)
    {
        mTail = newNode;
    }

    mSize++;
}

void ReaderDoubleLinkedList::remove(const Reader &reader)
{
    if (!mHead)
    {
        return;
    }

    if (mHead->data == reader)
    {
        Node *temp = mHead;
        mHead = mHead->next;
        if (mHead)
        {
            mHead->prev = nullptr;
        }
        else
        {
            mTail = nullptr;
        }
        delete temp;
        mSize--;
        return;
    }

    Node *current = mHead;
    while (current->next && current->next->data != reader)
    {
        current = current->next;
    }

    if (current->next)
    {
        Node *temp = current->next;
        current->next = current->next->next;
        if (current->next)
        {
            current->next->prev = current;
        }
        else
        {
            mTail = current;
        }
        delete temp;
        mSize--;
    }
}

bool ReaderDoubleLinkedList::contains(const Reader &reader) const
{
    Node *current = mHead;
    while (current)
    {
        if (current->data.getEmail() == reader.getEmail())
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

ReaderDoubleLinkedList ReaderDoubleLinkedList::find(const std::string &lastName, const std::string &firstName) const
{
    ReaderDoubleLinkedList matchingReaders;

    Node *current = mHead;
    while (current)
    {
        if (current->data.getLastName() == lastName && current->data.getFirstName() == firstName)
        {
            Reader copiedReader(current->data);
            matchingReaders.insert(copiedReader);
        }
        current = current->next;
    }

    return matchingReaders;
}

Reader *ReaderDoubleLinkedList::findByEmail(const std::string &email) const
{
    Node *current = mHead;
    while (current)
    {
        if (current->data.getEmail() == email)
        {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

ReaderDoubleLinkedList::Node *ReaderDoubleLinkedList::getFirst() const
{
    return mHead;
}

Reader *ReaderDoubleLinkedList::getFirstReader() const
{
    if (mHead)
    {
        return &(mHead->data);
    }
    return nullptr;
}

int ReaderDoubleLinkedList::getSize() const
{
    return mSize;
}

void ReaderDoubleLinkedList::display() const
{
    Node *current = mHead;
    Console::clearConsole();
    std::cout << "Readers: " << std::endl;
    while (current)
    {
        std::cout << "Full name: " << current->data.getFullName() << " | Email: " << current->data.getEmail() << std::endl;
        current = current->next;
    }
    Console::waitForInput();
}
