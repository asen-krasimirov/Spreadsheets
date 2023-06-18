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

    MyString _fileName;

public:
    Spreadsheet();
    explicit Spreadsheet(const char *fileName);

    void print(std::ostream &out = std::cout) const;
    void edit(size_t rowIndex, size_t cellIndex, const char *newValue);

    void loadFile(const char *fileName);
    void clearData();
    void save() const;
    void saveToFile(const char *fileName) const;

    Cell *getCellByIndex(size_t rowIndex, size_t cellIndex);

private:
    void readRow(int rowIndex, const char *buffer, char delimiter);

    static void fillRow(Row &row, size_t blankCellsToAdd);
    void saveCellWhiteSpaces(Row& row);

    void printRow(std::ostream &out, const Row &curRow) const;
    void printWhiteSpaces(std::ostream &out, const Row &curRow, int rowIndex) const;

};