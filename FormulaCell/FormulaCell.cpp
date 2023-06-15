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
    _operators += operatorSymbol;

    for (size_t i = 0; i < value.length(); ++i) {
        if (value[i] == operatorSymbol) {
            int leftIndex = i - 1;
//            MyString leftTempValue;
            while (leftIndex >= 0 && !isOperator(value[leftIndex])) {
                leftIndex--;
//                leftTempValue += value[leftIndex];  // MyString should be optimized- it allocated new memory in the heap every time like that
                                                    // Alternatively Bool type specification of Vector could be used
            }
//            _operands.pushBack(leftTempValue);
            _operands.pushBack(value.substr(leftIndex, i - leftIndex));

            int rightIndex = i + 1;
//            MyString rightTempValue;
            while (rightIndex < value.length() && !isOperator(value[rightIndex])) {
                rightIndex++;
//                rightTempValue += value[rightIndex];
            }
//            _operands.pushBack(rightTempValue);
            _operands.pushBack(value.substr(i, value.length() - rightIndex));

            // TODO: make indexes of value from leftIndex to rightIndex blank

            break;  // Should it break here?
        }
    }
}

FormulaCell::FormulaCell(const char *value) {
    char *tempValue = new char[strlen(value) + 1];
    strcpy(tempValue, value);
    trimAllWhiteSpaces(tempValue);

    MyString operationalValue(tempValue);
    parseOperation(operationalValue, '*');

//    std::cout << tempValue << std::endl;
}

unsigned FormulaCell::getWidth() const {
    return 6;
}

void FormulaCell::printCell(std::ostream &out) const {
    out << "= TEST";
}
