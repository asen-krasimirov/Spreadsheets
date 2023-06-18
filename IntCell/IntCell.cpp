#include "IntCell.h"
#include "../utils/utils.h"

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
