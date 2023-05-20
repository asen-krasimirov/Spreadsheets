#pragma once

#include <vector>
#include "../Row/Row.h"

class Spreadsheet {
private:
    std::vector<Row> _rows;
    std::vector<size_t> _cellWhiteSpaces;
    size_t _biggestCellCount = 0;

public:
    explicit Spreadsheet(const char *fileName);

    void print() const;

    void loadFile(const char *fileName);

private:
    void readRow(const char *buffer, char delimiter);

    static void fillRow(Row &row, size_t blankCellsToAdd);
    void saveCellWhiteSpaces(Row& row);

    void printRow(const Row &curRow) const;
    void printWhiteSpaces(const Row &curRow, int rowIndex) const;

};