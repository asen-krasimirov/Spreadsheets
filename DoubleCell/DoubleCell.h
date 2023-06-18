#pragma once

#include "../Cell/Cell.h"
#include "../IntCell/IntCell.h"

class DoubleCell : public Cell {
private:
    double _value = 0;
    unsigned _length = 0;

    void setValue(double value);
    void setLength(unsigned length);

public:
    explicit DoubleCell(const char *value);
    explicit DoubleCell(double value);

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

    double getOperationValue() const override;

};
