#include "StringCell.h"
#include "../utils/utils.h"

StringCell::StringCell(const char *value) {
    _value = value;
}

unsigned StringCell::getWidth() const {
    return _value.length();
}

void StringCell::printCell(std::ostream &out) const {
    out << _value;
}

double StringCell::getOperationValue() const {
    if (isNumber(_value.c_str())) {
        if (getCharCountInArray(_value.c_str(), '.') == 1) {
            return parseDouble(_value.c_str());
        }
        else {
            return parseInt(_value.c_str());
        }
    }

    return 0;
}
