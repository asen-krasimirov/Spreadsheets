#pragma once

#include "../Cell/Cell.h"

class IntCell : public Cell {
public:
    IntCell() = default;
    IntCell(const char *value);

};
