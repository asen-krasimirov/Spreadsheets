#include <cstring>
#include "FormulaCell.h"
#include "../utils/utils.h"

#include "../structs/SharedPointer.hpp"

#include "../Cell/Cell.h"
#include "../IntCell/IntCell.h"
#include "../DoubleCell/DoubleCell.h"
#include "../BlankCell/BlankCell.h"

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
    return _formulaResult->getWidth();
}

void FormulaCell::printCell(std::ostream &out) const {
//    if (!isParsed) {
//        parseCells();
//    }

//    out << "= TEST";
    _formulaResult->printCell(out);
}

bool FormulaCell::isReferenceValid(const char *value) {
    // TODO !!!: COULD BE WITH MORE THEN 4 LETTERS- R20C1
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
}

void FormulaCell::parseOperandResult(const MyString &value, double &result) {
    if (isNumber(value.c_str())) {
        if (getCharCountInArray(value.c_str(), '.') == 1) {
            result = parseDouble(value.c_str());
        } else {
            result = parseInt(value.c_str());
        }
        return;
    } else if (value[0] == 'R') {
        // TODO !!!: COULD BE WITH MORE THEN 4 LETTERS- R20C1
        if (isReferenceValid(value.c_str())) {
//            return _spreadsheet->getCellByIndex(value[1] - '0' - 1, value[3] - '0' - 1);
            result = _spreadsheet->getCellByIndex(value[1] - '0' - 1, value[3] - '0' - 1)->getOperationValue();
            return;
        }
    }

    throw std::invalid_argument("Invalid type!");
}

void FormulaCell::parseOperandResult(const Cell *value, double &result) {
    result = value->getOperationValue();
}

void FormulaCell::parseCell() {
    Vector<SharedPointer<Cell>> parsedCells;

    try {

        for (int i = 0, operandIndex = 0; i < _operators.getSize(); ++i) {
            double valueOne = 0;
            double valueTwo = 0;

            char curOperator = _operators[i];

            if (curOperator == 'b') {
                parseOperandResult(parsedCells.popBack().get(), valueOne);
                parseOperandResult(_operands[operandIndex], valueTwo);

                curOperator = _operators[i + 1];
                operandIndex += 1;
            }
            else {
                parseOperandResult(_operands[operandIndex], valueOne);
                parseOperandResult(_operands[operandIndex + 1], valueTwo);

                operandIndex += 2;
            }

            double result = 0;
            switch (curOperator) {
                case '^': result = powerNumber(valueOne, valueTwo); break;
                case '*': result = valueOne * valueTwo; break;
                case '/': {
                    if (valueTwo == 0) {
                        throw std::invalid_argument("Division by zero!");
                    }
                    result = valueOne / valueTwo;
                    break;
                }
                case '+': result = valueOne + valueTwo; break;
                case '-': result = valueOne - valueTwo; break;
                default: break;
            }

            if (result == 0) {
                parsedCells.pushBack(new BlankCell());
            } else if (result - (int)result < 0.000001) {
                parsedCells.pushBack(new IntCell((int) result));
            }
            else {
                parsedCells.pushBack(new DoubleCell(result));
            }

        }

        _formulaResult = parsedCells.popBack();
    }
    catch (std::invalid_argument &exc) {
        _formulaResult = new StringCell("ERROR");
        throw exc;
    }
}

double FormulaCell::getOperationValue() const {
    return _formulaResult->getOperationValue();
}
