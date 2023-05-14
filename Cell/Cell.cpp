#include "Cell.h"

Cell::Cell(const char *value) {
    setValue(value);
}

const MyString &Cell::getValue() const {
    return _value;
}

void Cell::setValue(const MyString &value) {
    _value = value;
}
