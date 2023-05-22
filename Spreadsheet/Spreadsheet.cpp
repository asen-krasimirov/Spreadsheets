#include <fstream>
#include <sstream>
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
        UniquePointer<Cell> newCell = UniquePointer<Cell>((new BlankCell()));
        row._cells.pushBack(std::move(newCell));
    }
}

void Spreadsheet::saveCellWhiteSpaces(Row& row) {
    for (int i = 0; i < row._cells.getSize(); ++i) {
        size_t curLen = row._cells[i]->getWidth();
        if (curLen > _cellWhiteSpaces[i]) {
            _cellWhiteSpaces[i] = curLen;
        }
    }
}

Spreadsheet::Spreadsheet(const char *fileName) {
    loadFile(fileName);
}

void Spreadsheet::loadFile(const char *fileName) {
    std::ifstream in(fileName);

    if (!in.is_open()) {
        throw std::ios_base::failure("File did not open!");
    }

    char buffer[MAX_BUFFER_SIZE];

    // TODO: validate table format (row format, cell format, ...)
    while (!in.eof()) {
        in.getline(buffer, MAX_BUFFER_SIZE);
        readRow(buffer, ',');
    }

    for (int i = 0; i < _biggestCellCount; ++i) {
        _cellWhiteSpaces.pushBack(0);
    }

    for (int i = 0; i < _rows.getSize(); ++i) {
        Row &curRow = _rows[i];

        fillRow(curRow, _biggestCellCount - curRow._cells.getSize());
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
        // TODO: validate cell format before casting and stop program upon exception
        ss.getline(value, MAX_BUFFER_SIZE, delimiter);
        removeWhiteSpaces(value);

        if (value[0] == '\0') {
            newRow._cells.pushBack(UniquePointer<Cell>(new BlankCell()));
        }
        else if (value[0] == '"') {
            parseEscapeSequences(value);
            removeSurroundingChars(value, '"', 1);
            newRow._cells.pushBack(UniquePointer<Cell>(new StringCell(value)));
        }
        else if (getCharCountInArray(value, '.') == 1) {
            newRow._cells.pushBack(UniquePointer<Cell>(new DoubleCell(value)));
        }
        else {
            newRow._cells.pushBack(UniquePointer<Cell>(new IntCell(value)));
        }

        curCellCount++;
    }

    if (curCellCount > _biggestCellCount) {
        _biggestCellCount = curCellCount;
    }

    _rows.pushBack(std::move(newRow));
}

void Spreadsheet::print() const {
    for (int i = 0; i < _rows.getSize(); ++i) {
        const Row &curRow = _rows[i];

        printRow(curRow);

        std::cout << std::endl;
    }
}

void Spreadsheet::printRow(const Row &curRow) const {
    for (int i = 0; i < curRow._cells.getSize(); ++i) {
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


