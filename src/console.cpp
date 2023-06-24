#include "../include/console.h"
#include <iostream>
#include <cstdlib>

namespace Console {
    void clearConsole() {
#ifdef _WIN32
        // Windows
        std::system("cls");
#else
        // Unix/Linux
        std::system("clear");
#endif
    }

    void waitForInput() {
        std::cout << "Wcisnij enter aby kontynulowac..." << std::endl;
        getchar();
    }

    void printSuccess(const std::string &message) {
        clearConsole();
        std::cout << "Sukces!" << std::endl;
        std::cout << message << std::endl;
        waitForInput();
    }

    void printInformation(const std::string &message) {
        clearConsole();
        std::cout << "Informacja!" << std::endl;
        std::cout << message << std::endl;
       waitForInput();
    }

    void printError(const std::string &message) {
        clearConsole();
        std::cout << "Blad!" << std::endl;
        std::cout << message << std::endl;
        waitForInput();
    }
}