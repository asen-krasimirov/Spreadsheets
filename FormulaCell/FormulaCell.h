#pragma once

#include "../Cell/Cell.h"
#include "../structs/Vector.hpp"
#include "../MyString/MyString.h"
#include "../StringView/StringView.h"

class FormulaCell : public Cell {
private:

//    Vector<char> _operators;
    Vector<char> _operators;
    Vector<MyString> _operands;

//    void setValue(double value);
//    void setLength(unsigned length);

    void parseOperation(MyString &value, char operatorSymbol = '+');

public:
    explicit FormulaCell(const char *value);

//    void executeFormula()

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

};
