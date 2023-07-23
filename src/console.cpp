#include "../include/console.h"
#include <iostream>
#include <cstdlib>

namespace Console
{
    void clearConsole()
    {
#ifdef _WIN32
        // Windows
        std::system("cls");
#else
        // Unix/Linux
        std::system("clear");
#endif
    }

    void waitForInput()
    {
        std::cout << "Press enter to continue..." << std::endl;
        getchar();
    }

    void printSuccess(const std::string &message)
    {
        clearConsole();
        std::cout << "\033[1;32mSuccess!\033[0m" << std::endl; // Green color
        std::cout << "\033[1;32m" << message << "\033[0m" << std::endl;
        waitForInput();
    }

    void printInformation(const std::string &message)
    {
        clearConsole();
        std::cout << "\033[1;33mInformation!\033[0m" << std::endl; // Yellow color
        std::cout << "\033[1;33m" << message << "\033[0m" << std::endl;
        waitForInput();
    }

    void printError(const std::string &message)
    {
        clearConsole();
        std::cout << "\033[1;31mError!\033[0m" << std::endl; // Red color
        std::cout << "\033[1;31m" << message << "\033[0m" << std::endl;
        waitForInput();
    }
}
