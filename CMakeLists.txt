cmake_minimum_required(VERSION 3.25)
project(LibraryManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

add_executable(LibraryManagementSystem src/main.cpp src/book.cpp include/book.h src/book_linked_list.cpp include/book_linked_list.h src/borrowed_books_linked_list.cpp include/borrowed_books_linked_list.h src/console.cpp include/console.h src/reader.cpp include/reader.h src/reader_double_linked_list.cpp include/reader_double_linked_list.h src/library.cpp include/library.h)