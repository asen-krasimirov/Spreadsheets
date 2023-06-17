#pragma once

#include "../Cell/Cell.h"
#include "../structs/Vector.hpp"
#include "../MyString/MyString.h"
#include "../StringView/StringView.h"
#include "../structs/SharedPointer.hpp"

class Spreadsheet;

class FormulaCell : public Cell {
private:

    SharedPointer<Spreadsheet> _spreadsheet;

    Vector<char> _operators;
    Vector<MyString> _operands;

    Cell *_formulaResult = nullptr;

//    void setValue(double value);
//    void setLength(unsigned length);

    void extractOperation(MyString &value, const char *operatorSymbol);

    Cell *parseOperand(const MyString &value);

    static bool isReferenceValid(const char *value);

public:
    explicit FormulaCell(const char *value, Spreadsheet *spreadsheet);

//    void executeFormula()

    void parseCell();  // TODO: make func- example: parse R1C1 to double

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

};
