//
// Created by Maciej Deroń on 23/06/2023.
//

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
        std::cout << "Wciśnij enter aby kontynułować..." << std::endl;
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
        std::cout << "Błąd!" << std::endl;
        std::cout << message << std::endl;
        waitForInput();
    }
}