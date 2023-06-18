#include "IntCell.h"
#include "../utils/utils.h"

#include "../DoubleCell/DoubleCell.h"

void IntCell::setValue(int value) {
    _value = value;
}

void IntCell::setLength(unsigned length) {
    _length = length;
}

IntCell::IntCell(const char *value) {
    setValue(parseInt(value));
    setLength(getNumLen(_value));
}

IntCell::IntCell(int value) {
    setValue(value);
    setLength(getNumLen(value));
}

unsigned IntCell::getWidth() const {
    return _length;
}

void IntCell::printCell(std::ostream &out) const {
    out << _value;
}

double IntCell::getOperationValue() const {
    return _value;
}

//Cell *IntCell::executeOperation(char operation, const Cell *operand) const {
//    return operand->executeOperationWithIntCell(operation, this);
//}
//
//Cell *IntCell::executeOperationWithIntCell(char operation, const IntCell *operand) const {
//    switch (operation) {
//        case '^': return new IntCell(powerNumber(operand->_value, _value));
//        case '*': return new IntCell(operand->_value * _value);
//        case '/': return new DoubleCell((double)operand->_value / _value);
//        case '+': return new IntCell(operand->_value + _value);
//        case '-': return new IntCell(operand->_value - _value);
//        default: return nullptr;
//    }
//}
//
//Cell *IntCell::executeOperationWithDoubleCell(char operation, const DoubleCell *operand) const {
//    switch (operation) {
//        case '^': return new IntCell(powerNumber(operand->_value, _value));
//        case '*': return new IntCell(operand->_value * _value);
//        case '/': return new DoubleCell((double)operand->_value / _value);
//        case '+': return new IntCell(operand->_value + _value);
//        case '-': return new IntCell(operand->_value - _value);
//        default: return nullptr;
//    }
//}
