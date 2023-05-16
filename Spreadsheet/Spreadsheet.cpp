#include <fstream>
#include <sstream>
#include <cstring>
#include "Spreadsheet.h"

#include "../utils/utils.h"
#include "../StringCell/StringCell.h"
#include "../IntCell/IntCell.h"
#include "../DoubleCell/DoubleCell.h"
#include "../BlankCell/BlankCell.h"

namespace {
    const short MAX_BUFFER_SIZE = 1024;
}

void Spreadsheet::fillRow(Row &row, size_t blankCellsToAdd) {
    for (int i = 0; i < blankCellsToAdd; ++i) {
        row._cells.push_back(new BlankCell(""));
    }
}

void Spreadsheet::saveCellWhiteSpaces(Row& row) {
    for (int i = 0; i < row._cells.size(); ++i) {
        size_t curLen = row._cells[i]->getWidth();
        if (curLen > _cellWhiteSpaces[i]) {
            _cellWhiteSpaces[i] = curLen;
        }
    }
}

Spreadsheet::Spreadsheet(const char *fileName) {
    std::ifstream in(fileName);

    if (!in.is_open()) {
        throw std::ios_base::failure("File did not open!");
    }

    char buffer[MAX_BUFFER_SIZE];

    while (!in.eof()) {
        in.getline(buffer, MAX_BUFFER_SIZE);
        readRow(buffer, ',');
    }

    for (int i = 0; i < _biggestCellCount; ++i) {
        _cellWhiteSpaces.push_back(0);
    }

    for (int i = 0; i < _rows.size(); ++i) {
        Row &curRow = _rows[i];

        fillRow(curRow, _biggestCellCount - curRow._cells.size());
        saveCellWhiteSpaces(curRow);
    }

    in.close();
}

void Spreadsheet::readRow(const char *buffer, char delimiter = ',') {
    std::stringstream ss(buffer);

    Row newRow;
    char value[MAX_BUFFER_SIZE];
    size_t curCellCount = 0;

    while (!ss.eof()) {
        ss.getline(value, MAX_BUFFER_SIZE, delimiter);
        // add check for double too
        // sanitize input (wight spaces, ...)
        removeWhiteSpaces(value);

        if (value[0] == '\0') {
            newRow._cells.push_back(new BlankCell());
        }
        else if (value[0] == '"') {
            parseEscapeSequences(value);
            removeSurroundingChars(value, '"', 1);
            newRow._cells.push_back(new StringCell(value));
        }
        else if (getCharCountInArray(value, '.') == 1) {
//            double doubleValue = parseDouble(value);
            newRow._cells.push_back(new DoubleCell(value));
        }
        else {
//            int intValue = parseNumber(value);
            newRow._cells.push_back(new IntCell(value));
        }

        curCellCount++;
    }

    if (curCellCount > _biggestCellCount) {
        _biggestCellCount = curCellCount;
    }

    _rows.push_back(newRow);
}

void Spreadsheet::print() const {
    for (int i = 0; i < _rows.size(); ++i) {
        const Row &curRow = _rows[i];

        printRow(curRow);

        std::cout << std::endl;
    }
}

void Spreadsheet::printRow(const Row &curRow) const {
    for (int i = 0; i < curRow._cells.size(); ++i) {
//        std::cout << curRow._cells[i]->getValue();
        curRow._cells[i]->printCell(std::cout);

        printWhiteSpaces(curRow, i);

        std::cout << " | ";
    }
}

void Spreadsheet::printWhiteSpaces(const Row &curRow, int rowIndex) const {
    size_t whiteSpaces = _cellWhiteSpaces[rowIndex] - curRow._cells[rowIndex]->getWidth();
    for (int j = 0; j < whiteSpaces; ++j) {
        std::cout << " ";
    }
}


