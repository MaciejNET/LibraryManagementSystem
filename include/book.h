//
// Created by Maciej Deroń on 23/06/2023.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_BOOK_H
#define LIBRARYMANAGEMENTSYSTEM_BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int count;

public:
    Book(std::string  title, std::string  author, int count);
    std::string getTitle() const;
    std::string getAuthor() const;
    int getCount() const;
    bool isAvailable() const;
    void decreaseCount();
    void increaseCount(int amount = 1);
    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;
};


#endif //LIBRARYMANAGEMENTSYSTEM_BOOK_H
