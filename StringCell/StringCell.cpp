#include "StringCell.h"

StringCell::StringCell(const char *value) {
    _value = value;
}

unsigned StringCell::getWidth() const {
    return _value.length();
}

void StringCell::printCell(std::ostream &out) const {
    out << _value;
}
