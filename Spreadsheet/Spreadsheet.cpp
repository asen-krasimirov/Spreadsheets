#include <fstream>
#include <sstream>
#include "Spreadsheet.h"

namespace {
    const short MAX_BUFFER_SIZE = 1024;
}

Spreadsheet::Spreadsheet(const char *fileName) {
    std::ifstream in(fileName);

    if (!in.is_open()) {
        throw std::ios_base::failure("File did not open!");
    }

    char buffer[MAX_BUFFER_SIZE];

//    in.getline(buffer, MAX_BUFFER_SIZE);
//    readHeadingRow(buffer);

//    in.getline(buffer, MAX_BUFFER_SIZE);
//    readAlignments(buffer);

    while (!in.eof()) {
        in.getline(buffer, MAX_BUFFER_SIZE);
        readRow(buffer, ',');
    }

    in.close();
}

void Spreadsheet::readRow(const char *buffer, char delimiter) {
    std::stringstream ss(buffer);

    Row newRow;
    char value[MAX_BUFFER_SIZE];
    size_t curCellCount = 0;
    while (!ss.eof()) {
        ss.getline(value, MAX_BUFFER_SIZE, delimiter);
//        sanitizeInputValue(value);
//        _rows.pushBack(StringCell(value));
        newRow._cells.emplace_back(value);
        curCellCount++;
    }

    if (curCellCount > _biggestCellCount) {
        _biggestCellCount = curCellCount;
    }

    size_t blankCellsToAdd = _biggestCellCount - curCellCount;
    for (int i = 0; i < blankCellsToAdd; ++i) {
        newRow._cells.push_back("");
    }

    _rows.push_back(newRow);
}

void Spreadsheet::print() const {
    for (int i = 0; i < _rows.size(); ++i) {
        const Row &curRow = _rows[i];
        for (int y = 0; y < curRow._cells.size(); ++y) {
            std::cout << curRow._cells[y]._value << " ";
        }
        std::cout << std::endl;
    }
}


