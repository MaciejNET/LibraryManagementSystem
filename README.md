# Library Management System

## Overview

This Library Management System is a simple application designed to manage books and readers in a library. It provides basic functionalities such as adding and removing books, adding and removing readers, borrowing and returning books, and displaying information about available books and readers.

## Running the Application

### Prerequisites

To run the application, you need to have the g++ compiler and CMake installed on your system.

### Build and Run

```shell
mkdir build
cd build
cmake ..
cmake --build .
cd ..
./build/LibraryManagementSystem.exe
```

## Description

This project was developed as part of a university assignment. The Library Management System allows library staff to manage the library's book inventory and readers effectively. It offers a user-friendly command-line interface for performing various library management tasks.

The application allows users to:

- Add new books to the library's collection, including information about the title, author, and initial book count.
- Remove books from the library.
- Add new readers to the library's database, capturing their first name, last name, and email address.
- Remove readers from the library's database.
- Borrow books from the library, associating books with readers and recording the borrowing date.
- Return borrowed books, updating the book's availability status.
- Display all available books in the library.
- Display information about all registered readers.
- Display the books borrowed by a specific reader.

Please note that this application is intended for educational purposes and serves as a basic demonstration of library management functionalities. For real-world library management needs, more advanced features and a graphical user interface would be necessary.

**Important**: Before running the application, make sure you have the required compiler and CMake installed on your system. The application source code is organized in the "src" directory, and CMake is used for building the project.

## Acknowledgments

This project was developed as a university assignment to demonstrate programming skills and knowledge of basic data structures. It was completed as part of the coursework and does not represent a complete and fully optimized library management system.