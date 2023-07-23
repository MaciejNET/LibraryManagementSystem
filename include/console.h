#ifndef LIBRARYMANAGEMENTSYSTEM_CONSOLE_H
#define LIBRARYMANAGEMENTSYSTEM_CONSOLE_H

#include <string>

namespace Console
{
    void clearConsole();
    void waitForInput();
    void printSuccess(const std::string &message);
    void printInformation(const std::string &message);
    void printError(const std::string &message);
}

#endif // LIBRARYMANAGEMENTSYSTEM_CONSOLE_H
