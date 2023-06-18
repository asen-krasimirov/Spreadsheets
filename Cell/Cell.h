#pragma once

#include <iostream>

//class IntCell;
//class DoubleCell;
//class StringCell;
//class BlankCell;
//class FormulaCell;

class Cell {
public:
    virtual ~Cell() = default;

    virtual unsigned getWidth() const = 0;
    virtual void printCell(std::ostream &out) const = 0;

    virtual double getOperationValue() const = 0;

//    virtual Cell *executeOperation(char operation, const Cell *operand) const = 0;
//
//    virtual Cell *executeOperationWithIntCell(char operation, const IntCell *operand) const = 0;
//    virtual Cell *executeOperationWithDoubleCell(char operation, const DoubleCell *operand) const = 0;
//    virtual Cell *executeOperationWithStringCell(char operation, const StringCell *operand) const = 0;
//    virtual Cell *executeOperationWithBlankCell(char operation, const BlankCell *operand) const = 0;
//    virtual Cell *executeOperationWithFormulaCell(char operation, const FormulaCell *operand) const = 0;

};
