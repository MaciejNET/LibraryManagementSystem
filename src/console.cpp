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
        std::cout << "Program is waiting for input. Press enter to continue..." << std::endl;
        getchar();
    }

    void printSuccess(const std::string &message) {
        clearConsole();
        std::cout << "Success!" << std::endl;
        std::cout << message << std::endl;
        waitForInput();
    }

    void printInformation(const std::string &message) {
        clearConsole();
        std::cout << "Information!" << std::endl;
        std::cout << message << std::endl;
       waitForInput();
    }

    void printError(const std::string &message) {
        clearConsole();
        std::cout << "Error!" << std::endl;
        std::cout << message << std::endl;
        waitForInput();
    }
}