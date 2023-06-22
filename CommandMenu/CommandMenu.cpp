#include <sstream>
#include <cstring>

#include "CommandMenu.h"

#include "../utils/utils.h"

namespace {
    const short MAX_COMMAND_LINE_SIZE = 10240;
}

void CommandMenu::printCommands() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "-> open <FileName>" << std::endl;
    std::cout << "-> close" << std::endl;
    std::cout << "-> save" << std::endl;
    std::cout << "-> save as <NewFileName>" << std::endl;
    std::cout << "-> print" << std::endl;
    std::cout << "-> edit <Row> <Column> <NewValue>" << std::endl;
    std::cout << "-> parseFormulas" << std::endl;

    std::cout << "-> exit" << std::endl;
}

void CommandMenu::getInputLine(MyString &inputLine, const char *message) {
    std::cout << message << std::endl;

    std::cin >> inputLine;
}

void CommandMenu::run() {
    std::cout << "Welcome to Spreadsheets Project!" << std::endl;

    printCommands();

    MyString commandLine;
    try {
        while (true) {
            getInputLine(commandLine, "Enter valid command: ");

            try {
                std::stringstream commandString(commandLine.c_str());

                char command[MAX_COMMAND_LINE_SIZE];
                commandString.getline(command, MAX_COMMAND_LINE_SIZE, ' ');

                if (strcmp(command, "open") == 0) {
                    char fileName[MAX_COMMAND_LINE_SIZE];
                    commandString.getline(fileName, MAX_COMMAND_LINE_SIZE, ' ');
                    try {
                        spreadsheet.loadFile(fileName);

                        std::cout << "File loaded!";
                    }
                    catch (std::invalid_argument &exc) {
                        std::cout << exc.what();
                    }
                } else if (strcmp(command, "close") == 0) {
                    spreadsheet.clearData();

                    std::cout << "File closed!";

                } else if (strcmp(command, "save") == 0) {
                    char mode[MAX_COMMAND_LINE_SIZE];
                    commandString.getline(mode, MAX_COMMAND_LINE_SIZE, ' ');

                    try {
                        if (strcmp(mode, "as") == 0) {
                            char newFileName[MAX_COMMAND_LINE_SIZE];
                            commandString.getline(newFileName, MAX_COMMAND_LINE_SIZE, ' ');

                            spreadsheet.saveToFile(newFileName);

                            std::cout << "Saved in " << newFileName << "!";
                        } else {
                            spreadsheet.save();

                            std::cout << "Saved in file!";
                        }
                    }
                    catch (std::logic_error &exc) {
                        std::cout << exc.what();
                    }
                } else if (strcmp(command, "print") == 0) {
                    try {
                        spreadsheet.print();
                    }
                    catch (std::logic_error &exc) {
                        std::cout << exc.what();
                    }
                } else if (strcmp(command, "edit") == 0) {
                    char rowIndexVal[MAX_COMMAND_LINE_SIZE];
                    commandString.getline(rowIndexVal, MAX_COMMAND_LINE_SIZE, ' ');
                    char columnIndexVal[MAX_COMMAND_LINE_SIZE];
                    commandString.getline(columnIndexVal, MAX_COMMAND_LINE_SIZE, ' ');
                    char newValue[MAX_COMMAND_LINE_SIZE];
                    commandString.getline(newValue, MAX_COMMAND_LINE_SIZE);

                    size_t rowIndex = parseInt(rowIndexVal);
                    size_t columnIndex = parseInt(columnIndexVal);

                    try {
                        spreadsheet.edit(rowIndex - 1, columnIndex - 1, newValue);

                        std::cout << "Edit made successfully!";
                    }
                    catch (std::invalid_argument &exc) {
                        std::cout << exc.what();
                    }
                } else if (strcmp(command, "parseFormulas") == 0) {
                    spreadsheet.parseFormulaCells();

                    std::cout << "Formula cells parsed successfully!";
                } else if (strcmp(command, "exit") == 0) {
                    spreadsheet.clearData();
                    break;
                } else {
                    std::cout << "wrong command";
                }

                std::cout << std::endl << std::endl;
            }

            catch (const char *message) {
                std::cout << message << std::endl;
            }
        }
    }
    catch (std::invalid_argument &exc) {
        std::cout << exc.what();
    }
    catch (...) {
        std::cout << "Something unexpected happen!";
    }
}
