#include "BlankCell.h"

BlankCell::BlankCell() : StringCell("") {

}

double BlankCell::getOperationValue() const {
    return 0;
}
