#pragma once

#include "../StringCell/StringCell.h"

class BlankCell : public StringCell {
public:
    BlankCell();
    Cell *clone() override;

    double getOperationValue() const override;

};
