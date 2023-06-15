#include <cstring>
#include "FormulaCell.h"
#include "../utils/utils.h"
//#include "../StringView/StringView.h"

namespace {
    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
    }
}

void FormulaCell::parseOperation(MyString &value, char operatorSymbol) {
    for (size_t i = 0; i < value.length(); ++i) {
        if (value[i] == operatorSymbol) {
            // _operators += operatorSymbol;        // MyString should be optimized- it allocated new memory in the heap every time like that
            _operators.pushBack(operatorSymbol);    // Alternatively Bool type specification of Vector could be used

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

            for (size_t y = leftIndex + 1; y < rightIndex; ++y) {
                value[y] = ' ';
            }

            break;  // Should it break here?
        }
    }
}

FormulaCell::FormulaCell(const char *value) {
    char *tempValue = new char[strlen(value) + 1];
    strcpy(tempValue, value);
    trimAllWhiteSpaces(tempValue);

    MyString operationalValue(tempValue);
    std::cout << operationalValue << std::endl;
    parseOperation(operationalValue, '*');
    std::cout << operationalValue << std::endl;
    parseOperation(operationalValue, '+');
    std::cout << operationalValue << std::endl;
    parseOperation(operationalValue, '/');
    std::cout << operationalValue << std::endl;

//    std::cout << tempValue << std::endl;

    for (size_t i = 0; i < _operators.getSize(); ++i) {
        std::cout << _operators[i] << std::endl;
    }

    for (size_t i = 0; i < _operands.getSize(); ++i) {
        std::cout << _operands[i] << std::endl;
    }
}

unsigned FormulaCell::getWidth() const {
    return 6;
}

void FormulaCell::printCell(std::ostream &out) const {
    out << "= TEST";
}
