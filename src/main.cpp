#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "../include/library.h"

const std::string FILE_NAME = "library.txt";

void saveDataToFile(const Library &library, const std::string &filename);
Library loadDataFromFile(const std::string &filename);
void displayMenu();
void addBook(Library &library);
void removeBook(Library &library);
void addReader(Library &library);
void removeReader(Library &library);
void borrowBook(Library &library);
void returnBook(Library &library);
void displayAllBooks(const Library &library);
void displayAvailableBooks(const Library &library);
void displayAllReaders(const Library &library);
void displayBorrowedBooksByReader(const Library &library);

int main(int argc, const char *argv[])
{
    Library library = loadDataFromFile(FILE_NAME);

    int choice;
    while (true)
    {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
            addBook(library);
            break;
        case 2:
            removeBook(library);
            break;
        case 3:
            addReader(library);
            break;
        case 4:
            removeReader(library);
            break;
        case 5:
            borrowBook(library);
            break;
        case 6:
            returnBook(library);
            break;
        case 7:
            displayAllBooks(library);
            break;
        case 8:
            displayAvailableBooks(library);
            break;
        case 9:
            displayAllReaders(library);
            break;
        case 10:
            displayBorrowedBooksByReader(library);
            break;
        case 11:
            saveDataToFile(library, FILE_NAME);
            exit(0);
        default:
            Console::printError("Invalid choice. Please try again.");
            break;
        }
    }
    return 0;
}

void saveDataToFile(const Library &library, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        const BookLinkedList &bookList = library.getBooks();
        BookLinkedList::Node *bookNode = bookList.getFirst();
        while (bookNode != nullptr)
        {
            const Book &book = bookNode->data;
            file << "book," << book.getTitle() << "," << book.getAuthor() << "," << book.getCount() << std::endl;
            bookNode = bookNode->next;
        }

        const ReaderDoubleLinkedList &readerList = library.getReaders();
        ReaderDoubleLinkedList::Node *readerNode = readerList.getFirst();
        while (readerNode != nullptr)
        {
            const Reader &reader = readerNode->data;
            file << "reader," << reader.getFirstName() << "," << reader.getLastName() << "," << reader.getEmail() << std::endl;
            const BorrowedBooksLinkedList &borrowedBooks = reader.getBorrowedBooks();
            BorrowedBooksLinkedList::Node *borrowedNode = borrowedBooks.getFirst();
            while (borrowedNode != nullptr)
            {
                const Book &borrowedBook = borrowedNode->book;
                file << "borrowed," << reader.getEmail() << "," << borrowedBook.getTitle() << "," << borrowedBook.getAuthor() << "," << borrowedNode->borrowedDate << std::endl;
                borrowedNode = borrowedNode->next;
            }
            readerNode = readerNode->next;
        }

        file.close();
        Console::printSuccess("Data saved to the file: " + filename);
    }
    else
    {
        Console::printError("Error opening file: " + filename);
    }
}

Library loadDataFromFile(const std::string &filename)
{
    Library library;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string type;
            if (!(getline(iss, type, ',')))
            {
                continue;
            }

            if (type == "book")
            {
                std::string title, author;
                int count;
                if (getline(iss, title, ',') && getline(iss, author, ',') && (iss >> count))
                {
                    Book book(title, author, count);
                    library.addBook(book);
                }
            }
            else if (type == "reader")
            {
                std::string firstName, lastName, email;
                if (getline(iss, firstName, ',') && getline(iss, lastName, ',') && getline(iss, email, ','))
                {
                    Reader reader(firstName, lastName, email);
                    library.addReader(reader);
                }
            }
            else if (type == "borrowed")
            {
                std::string email, title, author, borrowedDate;
                if (getline(iss, email, ',') && getline(iss, title, ',') && getline(iss, author, ',') && getline(iss, borrowedDate, ','))
                {
                    Book *book = library.findBook(title, author);
                    if (book != nullptr)
                    {
                        Reader *reader = library.findReaderByEmail(email);
                        if (reader != nullptr)
                        {
                            reader->insertBook(*book, borrowedDate);
                        }
                    }
                }
            }
        }

        file.close();
        Console::printSuccess("Data loaded from the file: " + filename);
    }
    else
    {
        Console::printError("Error opening file: " + filename);
    }
    return library;
}

void displayMenu()
{
    std::cout << "-----------------------" << std::endl;
    std::cout << "Library Database" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "1. Add book" << std::endl;
    std::cout << "2. Remove book" << std::endl;
    std::cout << "3. Add reader" << std::endl;
    std::cout << "4. Remove reader" << std::endl;
    std::cout << "5. Borrow a book" << std::endl;
    std::cout << "6. Return a book" << std::endl;
    std::cout << "7. Display all books" << std::endl;
    std::cout << "8. Display available books" << std::endl;
    std::cout << "9. Display all readers" << std::endl;
    std::cout << "10. Display books borrowed by a reader" << std::endl;
    std::cout << "11. Exit" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

void addBook(Library &library)
{
    std::string title, author;
    int count;
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Author: ";
    std::getline(std::cin, author);
    std::cout << "Amount: ";
    std::cin >> count;
    std::cin.ignore(); // Ignore the newline character left by std::cin

    if (count <= 0)
    {
        Console::printError("Book amount must be greater than 0!");
        return;
    }

    Book book(title, author, count);
    bool exists = library.isBookExists(book);

    if (exists)
    {
        library.addBookCount(title, author, count);
        Console::printInformation("Book \"" + title + "\" already exists. Added " + std::to_string(count) + " books.");
    }
    else
    {
        library.addBook(book);
        Console::printSuccess("Book \"" + title + "\" has been added to the library.");
    }
}

void removeBook(Library &library)
{
    std::string title, author;
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Author: ";
    std::getline(std::cin, author);

    Book *bookToRemove = library.findBook(title, author);

    if (bookToRemove)
    {
        library.removeBook(*bookToRemove);
        Console::printSuccess("Book \"" + title + "\" has been removed from the library.");
    }
    else
    {
        Console::printError("Book not found.");
    }
}

void addReader(Library &library)
{
    std::string firstName, lastName, email;
    std::cout << "First Name: ";
    std::getline(std::cin, firstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, lastName);
    std::cout << "Email: ";
    std::getline(std::cin, email);

    Reader reader(firstName, lastName, email);

    bool existsByEmail = library.isReaderExistsByEmail(reader);

    if (!existsByEmail)
    {
        library.addReader(reader);
        Console::printSuccess("Reader \"" + reader.getFullName() + "\" has been added to the library.");
    }
    else
    {
        Console::printError("Reader with email: \"" + email + "\" already exists.");
    }
}

void removeReader(Library &library)
{
    std::string firstName, lastName;
    std::cout << "First Name: ";
    std::getline(std::cin, firstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, lastName);

    ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);

    if (readers.getSize() == 1)
    {
        library.removeReader(*readers.getFirstReader());
    }
    else
    {
        std::string email;
        Console::printInformation("More than one reader found with the given data.");
        readers.display();
        std::cout << "Enter the email of the reader you want to remove: ";
        std::getline(std::cin, email);

        Reader *reader = readers.findByEmail(email);

        if (reader)
        {
            library.removeReader(*reader);
            Console::printSuccess("Reader \"" + reader->getFullName() + "\" has been removed.");
        }
        else
        {
            Console::printError("You entered an incorrect email.");
        }
    }
}

void borrowBook(Library &library)
{
    std::string title, author;
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Author: ";
    std::getline(std::cin, author);

    Book *book = library.findBook(title, author);

    if (!book)
    {
        Console::printError("Book not found.");
    }
    else if (!library.isBookAvailable(*book))
    {
        Console::printError("The book is not available.");
    }
    else
    {
        std::string firstName, lastName;
        std::cout << "First Name: ";
        std::getline(std::cin, firstName);
        std::cout << "Last Name: ";
        std::getline(std::cin, lastName);

        ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);
        Reader *reader = nullptr;

        if (readers.getSize() == 1)
        {
            reader = readers.getFirstReader();
        }
        else
        {
            std::string email;
            Console::printInformation("More than one reader found with the given data.");
            readers.display();
            std::cout << "Enter the email of the reader you want to borrow the book: ";
            std::getline(std::cin, email);

            reader = library.findReaderByEmail(email);
        }

        if (reader)
        {
            std::time_t currentTime = std::time(nullptr);
            std::tm *localTime = std::localtime(&currentTime);

            std::ostringstream oss;
            oss << std::put_time(localTime, "%d/%m/%Y");
            std::string formattedDate = oss.str();

            library.borrowBook(*book, *reader, formattedDate);
        }
        else
        {
            Console::printError("Reader not found.");
        }
    }
}

void returnBook(Library &library)
{
    std::string firstName, lastName;
    std::cout << "First Name: ";
    std::getline(std::cin, firstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, lastName);

    ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);
    Reader *reader = nullptr;

    if (readers.getSize() == 1)
    {
        reader = readers.getFirstReader();
    }
    else
    {
        std::string email;
        Console::printInformation("More than one reader found with the given data.");
        readers.display();
        std::cout << "Enter the email of the reader you want to return the book: ";
        std::getline(std::cin, email);

        reader = library.findReaderByEmail(email);
    }

    if (reader)
    {
        reader->displayBorrowedBooks();
        std::cout << "Which book would you like to return?" << std::endl;
        std::string title, author;
        std::cout << "Title: ";
        std::getline(std::cin, title);
        std::cout << "Author: ";
        std::getline(std::cin, author);

        Book *book = library.findBook(title, author);

        if (!book)
        {
            Console::printError("Book not found.");
        }
        else if (!reader->hasBook(*book))
        {
            Console::printError("You cannot return a book that was not borrowed by the reader.");
        }
        else
        {
            library.returnBook(*book, *reader);
        }
    }
    else
    {
        Console::printError("Reader not found.");
    }
}

void displayAllBooks(const Library &library)
{
    library.displayAllBooks();
}

void displayAvailableBooks(const Library &library)
{
    library.displayAvailableBooks();
}

void displayAllReaders(const Library &library)
{
    library.displayAllReaders();
}

void displayBorrowedBooksByReader(const Library &library)
{
    std::string firstName, lastName;
    std::cout << "First Name: ";
    std::getline(std::cin, firstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, lastName);

    ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);
    Reader *reader = nullptr;

    if (readers.getSize() == 1)
    {
        reader = readers.getFirstReader();
    }
    else
    {
        std::string email;
        Console::printInformation("More than one reader found with the given data.");
        readers.display();
        std::cout << "Enter the email of the reader you want to display the borrowed books: ";
        std::getline(std::cin, email);

        reader = library.findReaderByEmail(email);
    }

    if (reader)
    {
        library.displayBorrowedBooksByReader(*reader);
    }
    else
    {
        Console::printError("Reader not found.");
    }
}
