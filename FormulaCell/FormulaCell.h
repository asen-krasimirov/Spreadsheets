#pragma once

#include "../Cell/Cell.h"
#include "../structs/Vector.hpp"
#include "../MyString/MyString.h"

class FormulaCell : public Cell {
private:

//    Vector<char> _operators;
    MyString _operators;
    Vector<MyString> _operands;

//    void setValue(double value);
//    void setLength(unsigned length);

public:
    explicit FormulaCell(const char *value);

//    void executeFormula()

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

};
