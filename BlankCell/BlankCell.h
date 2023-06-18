#pragma once

#include "../StringCell/StringCell.h"

class BlankCell : public StringCell {
public:
    BlankCell();

    double getOperationValue() const override;

};
