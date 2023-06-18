#pragma once

#include "../StringCell/StringCell.h"

class BlankCell : public StringCell {
public:
    BlankCell();

    virtual double getOperationValue() const override;

};
