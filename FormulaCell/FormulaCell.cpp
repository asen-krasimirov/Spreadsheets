#include "FormulaCell.h"
#include "../utils/utils.h"
#include <cstring>

FormulaCell::FormulaCell(const char *value) {
    char *tempValue = new char[strlen(value) + 1];
    strcpy(tempValue, value);
    trimAllWhiteSpaces(tempValue);

    std::cout << tempValue << std::endl;
}

unsigned FormulaCell::getWidth() const {
    return 6;
}

void FormulaCell::printCell(std::ostream &out) const {
    out << "= TEST";
}
