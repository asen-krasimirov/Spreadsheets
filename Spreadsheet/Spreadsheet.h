#pragma once

#include "../structs/Vector.hpp"
#include "../Row/Row.h"
#include "../FormulaCell/FormulaCell.h"

class Spreadsheet {
private:
    Vector<Row> _rows;
    Vector<size_t> _cellWhiteSpaces;
    Vector<SharedPointer<Cell>> _formulaCells;

    size_t _biggestCellCount = 0;

public:
    explicit Spreadsheet(const char *fileName);

    void print() const;

    void loadFile(const char *fileName);

    Cell *getCellByIndex(size_t rowIndex, size_t cellIndex);

private:
    void readRow(const char *buffer, char delimiter);

    static void fillRow(Row &row, size_t blankCellsToAdd);
    void saveCellWhiteSpaces(Row& row);

    void printRow(const Row &curRow) const;
    void printWhiteSpaces(const Row &curRow, int rowIndex) const;

};