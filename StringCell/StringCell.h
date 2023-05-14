#pragma once

#include "../Cell/Cell.h"

class StringCell : public Cell {
public:
    StringCell() = default;
    StringCell(const char *value);

};
