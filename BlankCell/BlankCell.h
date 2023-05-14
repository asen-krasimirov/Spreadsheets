#pragma once

#include "../StringCell/StringCell.h"

class BlankCell : public StringCell {
public:
    BlankCell() = default;
    BlankCell(const char *value);

};
