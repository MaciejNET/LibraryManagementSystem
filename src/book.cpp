#include "../include/book.h"

#include <utility>

Book::Book(std::string title, std::string author, int count) : mTitle(std::move(title)), mAuthor(std::move(author)), mCount(count) {}

std::string Book::getTitle() const
{
    return mTitle;
}

std::string Book::getAuthor() const
{
    return mAuthor;
}

int Book::getCount() const
{
    return mCount;
}

bool Book::isAvailable() const
{
    return mCount > 0;
}

void Book::decreaseCount()
{
    if (mCount > 0)
        mCount--;
}

void Book::increaseCount(int amount)
{
    mCount += amount;
}

bool Book::operator==(const Book &other) const
{
    return (mTitle == other.mTitle && mAuthor == other.mAuthor);
}

bool Book::operator!=(const Book &other) const
{
    return (mTitle != other.mTitle || mAuthor != other.mAuthor);
}
