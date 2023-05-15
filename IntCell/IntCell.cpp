#include "IntCell.h"
#include "../utils/utils.h"

void IntCell::setValue(int value) {
    _value = value;
    _length = getNumLen(value);
}

IntCell::IntCell(int value) {
    setValue(value);
}

unsigned IntCell::getWidth() const {
    return _length;
}

void IntCell::printCell(std::ostream &out) const {
    out << _value;
}
