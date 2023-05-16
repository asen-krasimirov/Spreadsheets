#include <cstring>

#include "DoubleCell.h"
#include "../utils/utils.h"

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

unsigned DoubleCell::getWidth() const {
    return _length;
}

void DoubleCell::printCell(std::ostream &out) const {
    out << _value;
}
