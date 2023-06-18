#pragma once

#include "../Spreadsheet/Spreadsheet.h"
#include "../MyString/MyString.h"

class CommandMenu {
private:
    Spreadsheet spreadsheet;

    static void printCommands();
    static void getInputLine(MyString &inputLine, const char *message);

public:
    CommandMenu();

    void run();

};