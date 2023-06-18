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

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

    double getOperationValue() const override;

//    Cell *executeOperation(char operation, const Cell *operand) const override;
//
//    Cell *executeOperationWithIntCell(char operation, const IntCell *operand) const override;
//    Cell *executeOperationWithDoubleCell(char operation, const DoubleCell *operand) const override;
//    Cell *executeOperationWithStringCell(char operation, const StringCell *operand) const override;
//    Cell *executeOperationWithBlankCell(char operation, const BlankCell *operand) const override;
//    Cell *executeOperationWithFormulaCell(char operation, const FormulaCell *operand) const override;

};
