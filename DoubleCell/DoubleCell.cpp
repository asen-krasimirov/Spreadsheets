#include "DoubleCell.h"
#include "../utils/utils.h"

void DoubleCell::setValue(double value) {
    _value = value;
    _length = getNumLen(value);
}

DoubleCell::DoubleCell(double value) {
    setValue(value);
}

unsigned DoubleCell::getWidth() const {
    return _length;
}

void DoubleCell::printCell(std::ostream &out) const {
    out << _value;
}
