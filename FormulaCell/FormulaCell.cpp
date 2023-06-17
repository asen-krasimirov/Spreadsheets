#include <cstring>
#include "FormulaCell.h"
#include "../utils/utils.h"

#include "../structs/SharedPointer.hpp"

#include "../Cell/Cell.h"
#include "../IntCell/IntCell.h"
#include "../DoubleCell/DoubleCell.h"

#include "../Spreadsheet/Spreadsheet.h"

//template<typename T>
//class SharedPointer;
//class Cell;
//class DoubleCell;
//class IntCell;

namespace {
    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
    }
}

void FormulaCell::extractOperation(MyString &value, const char *operators) {
    for (size_t i = 0; i < value.length(); ++i) {
        if (isCharInArray(operators, value[i])) {
            int leftIndex = i - 1;
            while (leftIndex >= 0 && value[leftIndex] != ' ' && !isOperator(value[leftIndex])) {
                leftIndex--;
            }

            if (leftIndex != i - 1) {
                _operands.pushBack(value.substr(leftIndex + 1, i - leftIndex - 1));
            }

            int rightIndex = i + 1;
            while (rightIndex < value.length() && value[rightIndex] != ' ' && !isOperator(value[rightIndex])) {
                rightIndex++;
            }

            if (rightIndex != i + 1) {
                _operands.pushBack(value.substr(i + 1, rightIndex - i - 1));
            }

            if (value[leftIndex] == ' ' || value[rightIndex] == ' ') {
                _operators.pushBack('b');
            }

            _operators.pushBack(value[i]);

            for (size_t y = leftIndex + 1; y < rightIndex; ++y) {
                value[y] = ' ';
            }
        }
    }
}

FormulaCell::FormulaCell(const char *value, Spreadsheet *spreadsheet) : _spreadsheet(spreadsheet) {
    char *tempValue = new char[strlen(value) + 1];
    strcpy(tempValue, value);
    trimAllWhiteSpaces(tempValue);

    MyString operationalValue(tempValue);
    extractOperation(operationalValue, "^");
    extractOperation(operationalValue, "/*");
    extractOperation(operationalValue, "-+");
}

unsigned FormulaCell::getWidth() const {
    return 6;
}

void FormulaCell::printCell(std::ostream &out) const {
//    if (!isParsed) {
//        parseCells();
//    }

    out << "= TEST";
}

bool FormulaCell::isReferenceValid(const char *value) {
    if (strlen(value) != 4) {
        return false;
    }

    if (value[0] != 'R' || value[2] != 'C') {
        return false;
    }

    if (!isDigit(value[1]) || !isDigit(value[3])) {
        return false;
    }

    return true;
};

Cell *FormulaCell::parseOperand(const MyString &value) {
    if (isNumber(value.c_str())) {
        if (getCharCountInArray(value.c_str(), '.') == 1) {
            return new DoubleCell(value.c_str());
        }
        else {
            return new IntCell(value.c_str());
        }
    }
    else if (value[0] == 'R') {
        if (isReferenceValid(value.c_str())) {
            return _spreadsheet->getCellByIndex(value[1] - '0', value[3] - '0');
        }
    }

    throw std::invalid_argument("Invalid type!");
}


void FormulaCell::parseCell() {
    Vector<SharedPointer<Cell>> parsedCells;

    for (int i = 0, operandIndex = 0; i < _operators.getSize(); ++i, operandIndex += 2) {
        if (_operators[i] == 'b') {

        }

        Cell *firstOperand = parseOperand(_operands[operandIndex]);
        Cell *secondOperand = parseOperand(_operands[operandIndex + 1]);

//        if ()
    }

//    this->parsedResult = ...
}
