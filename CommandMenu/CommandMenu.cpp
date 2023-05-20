#include <sstream>
#include <cstring>

#include "CommandMenu.h"

#include "../MyString/MyString.h"

namespace {
    const short MAX_FILE_NAME_SIZE = 1024;
    const short MAX_COMMAND_LINE_SIZE = 1024;
}

CommandMenu::CommandMenu() : spreadsheet("file.txt") {

}

void CommandMenu::printCommands() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "-> print" << std::endl;

    std::cout << "-> exit" << std::endl;
}

void CommandMenu::getInputLine(MyString &inputLine, const char *message) {
    std::cout << message << std::endl;
//    std::cin.getline(inputLine, MAX_COMMAND_LINE_SIZE);

    // TODO: implement operator>> in MyString
//    std::cin >> inputLine;
}

int CommandMenu::run() {
//    char inputFileName[MAX_FILE_NAME_SIZE];
    MyString inputFileName;
    getInputLine(inputFileName, "Enter file name (\"file.txt\" for default): ");

    if (inputFileName == "") {
        inputFileName = "file.txt";
    }

    if (inputFileName != "file.txt") {
        spreadsheet.loadFile(inputFileName.c_str());
    }

    printCommands();

//    char commandLine[MAX_COMMAND_LINE_SIZE];
    MyString commandLine;

    while (true) {
        getInputLine(commandLine, "Enter valid command: ");

        try {
            std::stringstream commandString(commandLine.c_str());

            char command[MAX_COMMAND_LINE_SIZE];
            commandString.getline(command, MAX_COMMAND_LINE_SIZE, ' ');

            if (std::strcmp(command, "print") == 0) {
                spreadsheet.print();

            } else if (std::strcmp(command, "exit") == 0) {
                break;
            }
            else {
                std::cout << "wrong command";
            }

            std::cout << std::endl;
        }

        catch (const char *message) {
            std::cout << message << std::endl;
        }
    }
}
