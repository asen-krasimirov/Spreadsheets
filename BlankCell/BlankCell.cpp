#include "BlankCell.h"

BlankCell::BlankCell() : StringCell("") {

}

Cell *BlankCell::clone() {
    return new BlankCell(*this);
}

double BlankCell::getOperationValue() const {
    return 0;
}
