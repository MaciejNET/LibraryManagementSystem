#include "../include/book.h"

#include <utility>

Book::Book(std::string title, std::string  author, int count) : title(std::move(title)), author(std::move(author)), count(count) {}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getCount() const {
    return count;
}

bool Book::isAvailable() const {
    return count > 0;
}

void Book::decreaseCount() {
    if (count > 0)
        count--;
}

void Book::increaseCount(int amount) {
    count += amount;
}

bool Book::operator==(const Book& other) const {
    return (title == other.title && author == other.author);
}

bool Book::operator!=(const Book& other) const {
    return (title != other.title || author != other.author);
}
