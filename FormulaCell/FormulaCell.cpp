#include <cstring>
#include "FormulaCell.h"
#include "../utils/utils.h"

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

FormulaCell::FormulaCell(const char *value) {
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
    out << "= TEST";
}
