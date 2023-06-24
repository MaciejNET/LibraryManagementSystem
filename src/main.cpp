#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "../include/library.h"

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
            //Dodaj ksiazke
            case 1: {
                std::string title, author;
                int count;
                std::cout << "Tytul: ";
                std::getline(std::cin, title);
                std::cout << "Autor: ";
                std::getline(std::cin, author);
                std::cout << "Ilosc: ";
                std::cin >> count;
                if (count <= 0) {
                    Console::printError("Liczba ksiazek musi być wieksza niz 0!");
                    break;
                }
                Book book(title, author, count);
                bool exists = library.isBookExistis(book);

                if (exists) {
                    library.addBookCount(title, author, count);
                    Console::printInformation("Ksiazka \"" + title + "\" juz istnieje. Dodano " + std::to_string(count) + "ksiazek.");
                } else {
                    library.addBook(book);
                    Console::printSuccess("Ksiazka \"" + title + "\" zostala dodana do biblioteki.");
                }

                break;
            }

            //Usun ksiazke
            case 2: {
                std::string title, author;
                std::cout << "Tytul: ";
                std::getline(std::cin, title);
                std::cout << "Autor: ";
                std::getline(std::cin, author);

                Book* bookToRemove = library.findBook(title, author);

                if (bookToRemove) {
                    library.removeBook(*bookToRemove);
                    Console::printSuccess("Ksiazka \"" + title + "\" zostala usunieta z biblioteki.");
                } else {
                    Console::printError("Nie znaleziono ksiazki.");
                }

                break;
            }

            //Dodaj czytelnika
            case 3: {
                std::string firstName, lastName, email;
                std::cout << "Imie: ";
                std::getline(std::cin, firstName);
                std::cout << "Nazwisko: ";
                std::getline(std::cin, lastName);
                std::cout << "Email: ";
                std::getline(std::cin, email);

                Reader reader(firstName, lastName, email);

                bool existsByEmail = library.isReaderExistsByEmail(reader);

                if (!existsByEmail) {
                    library.addReader(reader);
                    Console::printSuccess("Czytelnik \"" + reader.getFullName() + "\" zostal dodany do biblioteki.");
                } else {
                    Console::printError("Czytelnik z adresem email : \"" + email + "\" juz istnieje.");
                }

                break;
            }

            //Usun czytelnika
            case 4: {
                std::string firstName, lastName;
                std::cout << "Imie: ";
                std::getline(std::cin, firstName);
                std::cout << "Nazwisko: ";
                std::getline(std::cin, lastName);

                ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);

                if (readers.getSize() == 1) {
                    library.removeReader(*readers.getFirstReader());
                } else {
                    std::string email;
                    Console::printInformation("Znaleziono wiecej niz jednego czytelnika o podanych danych.");
                    readers.display();
                    std::cout << "Podaj email czytelnika, którego chcesz usunać: ";
                    std::cin >> email;

                    Reader* reader = readers.findByEmail(email);

                    if (reader) {
                        library.removeReader(*reader);
                        Console::printSuccess("Czytelnik \"" + reader->getFullName() + "\" zostal usuniety..");
                    } else {
                        Console::printError("Podales nie prawidlowy email.");
                    }
                }

                break;
            }

            //Wypozycz ksiazke
            case 5: {
                std::string title, author;
                std::cout << "Tytul: ";
                std::getline(std::cin, title);
                std::cout << "Autor: ";
                std::getline(std::cin, author);

                Book* book = library.findBook(title, author);

                if (!book) {
                    Console::printError("Nie znaleziono ksiazki.");
                } else if (book && !library.isBookAvailable(*book)) {
                    Console::printError("Ksiazka nie jest dostepna.");
                } else {
                    std::string firstName, lastName;
                    std::cout << "Imie: ";
                    std::getline(std::cin, firstName);
                    std::cout << "Nazwisko: ";
                    std::getline(std::cin, lastName);

                    ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);
                    Reader *reader;
                    if (readers.getSize() == 1) {
                        reader = readers.getFirstReader();
                        std::string email = reader->getEmail();
                        reader = library.findReaderByEmail(email);
                    } else {
                        std::string email;
                        Console::printInformation("Znaleziono wiecej niz jednego czytelnika o podanych danych.");
                        readers.display();
                        std::cout << "Podaj email czytelnika, którego chcesz usunać: ";
                        std::cin >> email;

                        reader = library.findReaderByEmail(email);
                    }
                    if (reader) {
                        std::time_t currentTime = std::time(nullptr);
                        std::tm* localTime = std::localtime(&currentTime);

                        std::ostringstream oss;
                        oss << std::put_time(localTime, "%d/%m/%Y");
                        std::string formattedDate = oss.str();

                        library.borrowBook(*book, *reader, formattedDate);
                    } else {
                        Console::printError("Nie znaleziono czytelnika.");
                    }
                }
                break;
            }

            //Zwróć ksiazke
            case 6 : {
                std::string firstName, lastName;
                std::cout << "Imie: ";
                std::getline(std::cin, firstName);
                std::cout << "Nazwisko: ";
                std::getline(std::cin, lastName);

                ReaderDoubleLinkedList readers = library.findReaders(firstName, lastName);
                Reader* reader;

                if (readers.getSize() == 1) {
                    reader = readers.getFirstReader();
                    std::string email = reader->getEmail();
                    reader = library.findReaderByEmail(email);
                } else {
                    std::string email;
                    Console::printInformation("Znaleziono wiecej niz jednego czytelnika o podanych danych.");
                    readers.display();
                    std::cout << "Podaj email czytelnika, którego chcesz usunać: ";
                    std::cin >> email;

                    reader = readers.findByEmail(email);
                }

                if (reader) {
                    reader->displayBorrowedBooks();
                    std::cout << "Która ksiazke chcialbys zwrócić?" << std::endl;
                    std::string title, author;
                    std::cout << "Tytul: ";
                    std::getline(std::cin, title);
                    std::cout << "Autor: ";
                    std::getline(std::cin, author);

                    Book* book = library.findBook(title, author);

                    if (!book) {
                        Console::printError("Nie znaleziono ksiazki.");
                    } else if (book && !reader->hasBook(*book)) {
                        Console::printError("Nie mozna zwrócić ksiazki, która nie zostala wyporzyczona przez czytalnika.");
                    } else {
                        library.returnBook(*book, *reader);
                    }

                } else {
                    Console::printError("Nie znaleziono czytelnika.");
                }

                break;
            }

            //Wyswietl wszystkie ksiazki
            case 7: {
                library.displayAllBooks();
                break;
            }

            //Wyswietl dostepne ksiazki
            case 8 : {
                library.displayAvailableBooks();
                break;
            }

            //Wyswietl wszyskich czytelników
            case 9: {
                library.displayAllReaders();
                break;
            }

            //Wyswietl ksiazki wypozyczone przez czyetlnika
            case 10: {
                std::string firstName, lastName;
                std::cout << "Imie: ";
                std::getline(std::cin, firstName);
                std::cout << "Nazwisko: ";
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
                    Console::printInformation("Znaleziono wiecej niz jednego czytelnika o podanych danych.");
                    readers.display();
                    std::cout << "Podaj email czytelnika, którego chcesz usunać: ";
                    std::cin >> email;

                    reader = readers.findByEmail(email);

                    if (reader) {
                        library.displayBorrowedBooksByReader(*reader);
                    } else {
                        Console::printError("Nie znaleziono czytelnika.");
                    }
                }
                break;
            }


            //Koniex
            case 11:
                saveDataToFile(library, FILE_NAME);
                exit(0);

            default:
                Console::printError("Nieprawidlowy wybór. Spróbuj ponownie.");
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
        Console::printSuccess("Zapisano do pliku: " + filename);
    } else {
        Console::printError("Blad przy otwarciu pliku: " + filename);
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
        Console::printSuccess("Wczytano dane z pliku: " + filename);
    } else {
        Console::printError("Blad przy otwarciu pliku: " + filename);
    }
    return library;
}

void displayMenu() {
    std::cout << "-----------------------" << std::endl;
    std::cout << "Baza danych biblioteki" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "1. Dodaj ksiazke" << std::endl;
    std::cout << "2. Usun ksiazke" << std::endl;
    std::cout << "3. Dodaj czytelnika" << std::endl;
    std::cout << "4. Usun czytelnika" << std::endl;
    std::cout << "5. Wypozycz ksiazke" << std::endl;
    std::cout << "6. Zwróć ksiazke" << std::endl;
    std::cout << "7. Wyswietl wszystkie ksiazki" << std::endl;
    std::cout << "8. Wyswietl dostepne ksiazki" << std::endl;
    std::cout << "9. Wyswietl wszystkich czytelników" << std::endl;
    std::cout << "10. Wysietl ksiazki wypozyczone przez czytelnika" << std::endl;
    std::cout << "11. Koniec" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "Podaj swój wybór: ";
}
