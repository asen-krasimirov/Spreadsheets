#pragma once

#include <vector>
#include "../Row/Row.h"

class Spreadsheet {
private:
    std::vector<Row> _rows;
    size_t _biggestCellCount = 0;

public:
    Spreadsheet(const char *fileName);

    void print() const;

private:
    void readRow(const char *buffer, char delimiter);

};