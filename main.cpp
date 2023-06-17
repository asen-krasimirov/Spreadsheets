//#include "CommandMenu/CommandMenu.h"

#include "Spreadsheet/Spreadsheet.h"

#include "utils/utils.h"

#include "StringCell/StringCell.h"

int main() {
//    CommandMenu commandMenu;

//    return commandMenu.run();

    Spreadsheet sp("file.txt");

    sp.print();

}
