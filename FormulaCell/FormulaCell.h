#pragma once

#include "../Cell/Cell.h"
#include "../structs/Vector.hpp"
#include "../MyString/MyString.h"
#include "../StringView/StringView.h"
#include "../structs/SharedPointer.hpp"

class Spreadsheet;

class FormulaCell : public Cell {
private:

    Spreadsheet *_spreadsheet;  // handle memory leak (not with sharedPtr)

    Vector<char> _operators;
    Vector<MyString> _operands;

    SharedPointer<Cell> _formulaResult = nullptr;

//    void setValue(double value);
//    void setLength(unsigned length);

    void extractOperation(MyString &value, const char *operatorSymbol);

    void parseOperandResult(const MyString &value, double &result);
    void parseOperandResult(const Cell *value, double &result);

    static bool isReferenceValid(const char *value);

public:
    explicit FormulaCell(const char *value, Spreadsheet *spreadsheet);

    void parseCell();  // TODO: make func- example: parse R1C1 to double

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

    double getOperationValue() const override;

};
