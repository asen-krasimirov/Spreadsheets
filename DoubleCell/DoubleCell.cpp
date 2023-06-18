#include <cstring>

#include "DoubleCell.h"
#include "../utils/utils.h"

#include <sstream> // temp

void DoubleCell::setValue(double value) {
    _value = value;
}

void DoubleCell::setLength(unsigned length) {
    _length = length;
}

DoubleCell::DoubleCell(const char *value) {
    setValue(parseDouble(value));
    setLength(std::strlen(value));
}

DoubleCell::DoubleCell(double value) {
    setValue(value);
    setLength(getNumLen(value));
}

unsigned DoubleCell::getWidth() const {
    return _length;
}

void DoubleCell::printCell(std::ostream &out) const {
    out << _value;
}

double DoubleCell::getOperationValue() const {
    return _value;
}
