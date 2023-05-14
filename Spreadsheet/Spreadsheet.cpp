#include <fstream>
#include <sstream>
#include "Spreadsheet.h"

#include "../utils/utils.h"
//#include "../Cell/Cell.h"
#include "../StringCell/StringCell.h"
#include "../IntCell/IntCell.h"
#include "../BlankCell/BlankCell.h"

namespace {
    const short MAX_BUFFER_SIZE = 1024;
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

        if (value[0] == '"') {
            parseEscapeSequences(value);
            removeSurroundingChars(value, '"', 1);
            newRow._cells.push_back(new StringCell(value));
        }
        else {
            newRow._cells.push_back(new IntCell(value));
        }

        curCellCount++;
    }

    if (curCellCount > _biggestCellCount) {
        _biggestCellCount = curCellCount;
    }

    size_t blankCellsToAdd = _biggestCellCount - curCellCount;
    for (int i = 0; i < blankCellsToAdd; ++i) {
        newRow._cells.push_back(new BlankCell(""));
    }

    _rows.push_back(newRow);
}

void Spreadsheet::print() const {
    for (int i = 0; i < _rows.size(); ++i) {
        const Row &curRow = _rows[i];
        for (int y = 0; y < curRow._cells.size(); ++y) {
            std::cout << curRow._cells[y]->getValue() << " ";
        }
        std::cout << std::endl;
    }
}


