#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/library.h"
#include "../include/console.h"

const std::string FILE_NAME = "library.txt";

void saveDataToFile(const Library& library, const std::string& filename);
Library loadDataFromFile(const std::string& filename);
void displayMenu();

int main(int argc, const char * argv[]) {
    Library library = loadDataFromFile(FILE_NAME);

    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string title, author;
                int count;
                std::cout << "Title: ";
                std::getline(std::cin, title);
                std::cout << "Author: ";
                std::getline(std::cin, author);
                std::cout << "Count: ";
                std::cin >> count;
                if (count <= 0) {
                    Console::printError("Book count must be greater than 0!");
                    break;
                }
                Book book(title, author, count);
                bool exists = library.isBookExistis(book);

                if (exists) {
                    library.addBookCount(title, author, count);
                    Console::printInformation("Book \"" + title + "\" has been found. Adding book count to existing book.");
                } else {
                    library.addBook(book);
                    Console::printSuccess("Book \"" + title + "\" has been added to library.");
                }

                break;
            }

            case 2: {
                std::string title, author;
                std::cout << "Title: ";
                std::getline(std::cin, title);
                std::cout << "Author: ";
                std::getline(std::cin, author);

                Book* bookToRemove = library.findBook(title, author);

                if (bookToRemove) {
                    library.removeBook(*bookToRemove);
                    Console::printSuccess("Book \"" + title + "\" has been removed to library.");
                } else {
                    Console::printError("Cannot find book to remove.");
                }

                break;
            }

            case 3: {
                std::string firstName, lastName, email;
                std::cout << "First name: ";
                std::getline(std::cin, firstName);
                std::cout << "Last name: ";
                std::getline(std::cin, lastName);
                std::cout << "Email: ";
                std::getline(std::cin, email);

                Reader reader(firstName, lastName, email);

                bool existsByEmail = library.isReaderExistsByEmail(reader);

                if (!existsByEmail) {
                    library.addReader(reader);
                    Console::printSuccess("Reader \"" + reader.getFullName() + "\" has been added to library.");
                } else {
                    Console::printError("Reader with email : \"" + email + "\" already exists.");
                }

                break;
            }

            case 4: {
                std::string firstName, lastName;
                std::cout << "First name: ";
                std::getline(std::cin, firstName);
                std::cout << "Last name: ";
                std::getline(std::cin, lastName);

                ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);

                if (readers.getSize() == 1) {
                    library.removeReader(*readers.getFirstReader());
                } else {
                    std::string email;
                    Console::printInformation("Found more than one reader with given first and last name.");
                    readers.display();
                    std::cout << "Enter email of reader which you want to remove: ";
                    std::cin >> email;

                    Reader* reader = readers.findByEmail(email);

                    if (reader) {
                        library.removeReader(*reader);
                        Console::printSuccess("Reader \"" + reader->getFullName() + "\" has been removed to library.");
                    } else {
                        Console::printError("You pass wrong email.");
                    }
                }

                break;
            }

            case 5: {
                std::string title, author;
                std::cout << "Title: ";
                std::getline(std::cin, title);
                std::cout << "Author: ";
                std::getline(std::cin, author);

                Book* book = library.findBook(title, author);

                if (!book) {
                    Console::printError("Cannot find book.");
                } else if (book && !library.isBookAvailable(*book)) {
                    Console::printError("Book is not available.");
                } else {
                    std::string firstName, lastName;
                    std::cout << "First name: ";
                    std::getline(std::cin, firstName);
                    std::cout << "Last name: ";
                    std::getline(std::cin, lastName);

                    ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);
                    Reader *reader;
                    if (readers.getSize() == 1) {
                        reader = readers.getFirstReader();
                        std::string email = reader->getEmail();
                        reader = library.findReaderByEmail(email);
                    } else {
                        std::string email;
                        Console::printInformation("Found more than one reader with given first and last name.");
                        readers.display();
                        std::cout << "Enter email of reader which you want to remove: ";
                        std::cin >> email;

                        reader = library.findReaderByEmail(email);
                    }
                    if (reader) {
                        auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                        std::tm* localTime = std::localtime(&currentTime);
                        std::string formattedDate(11, '\0');
                        std::strftime(&formattedDate[0], formattedDate.size(), "%d/%m/%Y", localTime);
                        formattedDate.resize(formattedDate.find('\0'));
                        library.borrowBook(*book, *reader, formattedDate);
                    } else {
                        Console::printError("Reader does not exists.");
                    }
                }
                break;
            }

            case 6 : {
                std::string firstName, lastName;
                std::cout << "First name: ";
                std::getline(std::cin, firstName);
                std::cout << "Last name: ";
                std::getline(std::cin, lastName);

                ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);
                Reader* reader;

                if (readers.getSize() == 1) {
                    reader = readers.getFirstReader();
                    std::string email = reader->getEmail();
                    reader = library.findReaderByEmail(email);
                } else {
                    std::string email;
                    Console::printInformation("Found more than one reader with given first and last name.");
                    readers.display();
                    std::cout << "Enter email of reader which you want to remove: ";
                    std::cin >> email;

                    reader = readers.findByEmail(email);
                }

                if (reader) {
                    reader->displayBorrowedBooks();
                    std::cout << "Which book you want to return?" << std::endl;
                    std::string title, author;
                    std::cout << "Title: ";
                    std::getline(std::cin, title);
                    std::cout << "Author: ";
                    std::getline(std::cin, author);

                    Book* book = library.findBook(title, author);

                    if (!book) {
                        Console::printError("Cannot find book.");
                    } else if (book && !reader->hasBook(*book)) {
                        Console::printError("A book that has been borrowed by a reader cannot be returned.");
                    } else {
                        library.returnBook(*book, *reader);
                    }

                } else {
                    Console::printError("Reader does not exists.");
                }

                break;
            }

            case 7 : {
                library.displayAvailableBooks();
                break;
            }

            case 8: {
                std::string firstName, lastName;
                std::cout << "First name: ";
                std::getline(std::cin, firstName);
                std::cout << "Last name: ";
                std::getline(std::cin, lastName);

                ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);
                Reader* reader;

                if (readers.getSize() == 1) {
                    reader = readers.getFirstReader();
                    std::string email = reader->getEmail();
                    reader = library.findReaderByEmail(email);
                    library.displayBorrowedBooksByReader(*reader);
                } else {
                    std::string email;
                    Console::printInformation("Found more than one reader with given first and last name.");
                    readers.display();
                    std::cout << "Enter email: ";
                    std::cin >> email;

                    reader = readers.findByEmail(email);

                    if (reader) {
                        library.displayBorrowedBooksByReader(*reader);
                    } else {
                        Console::printError("Reader does not exists.");
                    }
                }
                break;
            }

            case 9:
                saveDataToFile(library, FILE_NAME);
                exit(0);

            default:
                Console::printError("Invalid choice. Please try again.");
                break;
        }
    }
    return 0;
}

void saveDataToFile(const Library& library, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        const BookLinkedList& bookList = library.getBooks();
        BookLinkedList::Node* bookNode = bookList.getFirst();
        while (bookNode != nullptr) {
            const Book& book = bookNode->data;
            file << "book," << book.getTitle() << "," << book.getAuthor() << "," << book.getCount() << std::endl;
            bookNode = bookNode->next;
        }

        const ReaderDoubleLinkedList& readerList = library.getReaders();
        ReaderDoubleLinkedList::Node* readerNode = readerList.getFirst();
        while (readerNode != nullptr) {
            const Reader& reader = readerNode->data;
            file << "reader," << reader.getFirstName() << "," << reader.getLastName() << "," << reader.getEmail() << std::endl;
            const BorrowedBooksLinkedList& borrowedBooks = reader.getBorrowedBooks();
            BorrowedBooksLinkedList::Node* borrowedNode = borrowedBooks.getFirst();
            while (borrowedNode != nullptr) {
                const Book& borrowedBook = borrowedNode->book;
                file << "borrowed," << reader.getEmail() << "," << borrowedBook.getTitle() << "," << borrowedBook.getAuthor() << "," << borrowedNode->borrowedDate << std::endl;
                borrowedNode = borrowedNode->next;
            }
            readerNode = readerNode->next;
        }

        file.close();
        Console::printSuccess("Data saved to file: " + filename);
    } else {
        Console::printError("Error opening file: " + filename);
    }
}

Library loadDataFromFile(const std::string& filename) {
    Library library;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type;
            if (!(getline(iss, type, ','))) {
                continue;
            }

            if (type == "book") {
                std::string title, author;
                int count;
                if (getline(iss, title, ',') && getline(iss, author, ',') && (iss >> count)) {
                    Book book(title, author, count);
                    library.addBook(book);
                }
            } else if (type == "reader") {
                std::string firstName, lastName, email;
                if (getline(iss, firstName, ',') && getline(iss, lastName, ',') && getline(iss, email, ',')) {
                    Reader reader(firstName, lastName, email);
                    library.addReader(reader);
                }
            } else if (type == "borrowed") {
                std::string email, title, author, borrowedDate;
                if (getline(iss, email, ',') && getline(iss, title, ',') && getline(iss, author, ',') && getline(iss, borrowedDate, ',')) {
                    Book* book = library.findBook(title, author);
                    if (book != nullptr) {
                        Reader* reader = library.findReaderByEmail(email);
                        if (reader != nullptr) {
                            reader->insertBook(*book, borrowedDate);
                        }
                    }
                }
            }
        }

        file.close();
        Console::printSuccess("Data loaded from file: " + filename);
    } else {
        Console::printError("Error opening file: " + filename);
    }
    return library;
}

void displayMenu() {
    std::cout << "-----------------------" << std::endl;
    std::cout << "Library Management System" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "1. Add Book" << std::endl;
    std::cout << "2. Remove Book" << std::endl;
    std::cout << "3. Add Reader" << std::endl;
    std::cout << "4. Remove Reader" << std::endl;
    std::cout << "5. Borrow Book" << std::endl;
    std::cout << "6. Return Book" << std::endl;
    std::cout << "7. Display Available Books" << std::endl;
    std::cout << "8. Display Borrowed Books by Reader" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "Enter your choice: ";
}
