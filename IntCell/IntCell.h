#pragma once

#include "../Cell/Cell.h"

class IntCell : public Cell {
private:
    int _value = 0;
    unsigned _length = 0;

    void setValue(int value);
    void setLength(unsigned length);

public:
    explicit IntCell(const char *value);
    explicit IntCell(int value);
    Cell *clone() override;

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

    double getOperationValue() const override;

};
