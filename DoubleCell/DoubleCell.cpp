#include "DoubleCell.h"
#include "../utils/utils.h"

namespace {
    const short DOUBLE_PRESSISION_CAP = 4;
}

void DoubleCell::setValue(double value) {
    _value = value;
}

void DoubleCell::setLength(unsigned length) {
    _length = length;
}

DoubleCell::DoubleCell(const char *value) {
    setValue(roundNumber(parseDouble(value), DOUBLE_PRESSISION_CAP));
    setLength(getNumLen(_value));
}

DoubleCell::DoubleCell(double value) {
    setValue(roundNumber(value, DOUBLE_PRESSISION_CAP));
    setLength(getNumLen(_value));
}

Cell *DoubleCell::clone() {
    return new DoubleCell(*this);
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
