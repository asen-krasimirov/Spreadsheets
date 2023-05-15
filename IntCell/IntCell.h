#pragma once

#include "../Cell/Cell.h"

class IntCell : public Cell {
private:
    int _value = 0;
    unsigned _length = 0;

    void setValue(int value);

public:
    IntCell() = default;
    explicit IntCell(int value);

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

};
