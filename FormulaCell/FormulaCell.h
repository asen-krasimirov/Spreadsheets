#pragma once

#include "../Cell/Cell.h"
#include "../structs/Vector.hpp"
#include "../MyString/MyString.h"
#include "../structs/SharedPointer.hpp"

//#include "../Spreadsheet/Spreadsheet.h"

class Spreadsheet;

class FormulaCell : public Cell {
private:

    Spreadsheet *_spreadsheet;  // TODO: handle memory leak (not with sharedPtr)
//    SharedPointer<Spreadsheet> _spreadsheet;

    Vector<char> _operators;
    Vector<MyString> _operands;

    SharedPointer<Cell> _formulaResult = nullptr;

    void extractOperation(MyString &value, const char *operatorSymbol);

    void parseOperandResult(const MyString &value, double &result);

public:
    explicit FormulaCell(const char *value, Spreadsheet *spreadsheet);
    Cell *clone() override;

    void parseCell();

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

    double getOperationValue() const override;

};
