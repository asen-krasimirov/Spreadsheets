#include <fstream>
#include <sstream>
#include <cstring>
#include "Spreadsheet.h"

#include "../utils/utils.h"
#include "../StringCell/StringCell.h"
#include "../IntCell/IntCell.h"
#include "../DoubleCell/DoubleCell.h"
#include "../BlankCell/BlankCell.h"
#include "../FormulaCell/FormulaCell.h"

namespace {
    const short MAX_BUFFER_SIZE = 10240;
}

void Spreadsheet::fillRow(Row &row, size_t blankCellsToAdd) {
    for (int i = 0; i < blankCellsToAdd; ++i) {
        row._cells.pushBack(new BlankCell());
    }
}

void Spreadsheet::saveCellWhiteSpaces(Row &row) {
    for (int i = 0; i < row._cells.getSize(); ++i) {
        size_t curLen = row._cells[i]->getWidth();
        if (curLen > _cellWhiteSpaces[i]) {
            _cellWhiteSpaces[i] = curLen;
        }
    }
}

Spreadsheet::Spreadsheet() : _fileName("") {

}

Spreadsheet::Spreadsheet(const char *fileName) : _fileName(fileName) {
    loadFile(fileName);
}

void Spreadsheet::loadFile(const char *fileName) {
    clearData();
    _fileName = fileName;

    std::ifstream in(fileName);

    if (!in.is_open()) {
        throw std::invalid_argument("File did not open! Or file name is incorrect!");
    }

    char buffer[MAX_BUFFER_SIZE];
    int rowIndex = 1;
    while (!in.eof()) {
        in.getline(buffer, MAX_BUFFER_SIZE);
        readRow(rowIndex++, buffer, ',');
    }

    for (int i = 0; i < _formulaCells.getSize(); ++i) {
        dynamic_cast<FormulaCell *>(_formulaCells[i].get())->parseCell();
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

void Spreadsheet::clearData() {
    _rows.clear();
    _cellWhiteSpaces.clear();
    _formulaCells.clear();
    _biggestCellCount = 0;
    _fileName = "";
}

void Spreadsheet::save() const {
    if (_fileName == "") {
        throw std::logic_error("No file loaded!");
    } else {
        saveToFile(_fileName.c_str());
    }
}

void Spreadsheet::saveToFile(const char *fileName) const {
    std::ofstream out(fileName);

    if (!out.is_open()) {
        throw std::invalid_argument("File did not open! Or file name is incorrect!");
    }

    print(out);

    out.close();
}

void Spreadsheet::readRow(int rowIndex, const char *buffer, char delimiter = ',') {
    std::stringstream ss(buffer);

    Row newRow;
    char value[MAX_BUFFER_SIZE];
    size_t curCellCount = 0;

    while (!ss.eof()) {
        ss.getline(value, MAX_BUFFER_SIZE, delimiter);
        removeWhiteSpaces(value);

        if (value[0] == '"' && value[std::strlen(value) - 1] == '"') {
            parseEscapeSequences(value);
            removeSurroundingChars(value, '"', 1);
            newRow._cells.pushBack(new StringCell(value));
        } else if (isNumber(value)) {
            if (getCharCountInArray(value, '.') == 1) {
                newRow._cells.pushBack(new DoubleCell(value));
            } else {
                newRow._cells.pushBack(new IntCell(value));
            }
        } else if (value[0] == '=') {
            removeSurroundingChars(value, '=');

            SharedPointer<Cell> formulaCell = new FormulaCell(value, this);
            newRow._cells.pushBack(formulaCell);
            _formulaCells.pushBack(formulaCell);
        } else if (value[0] == '\0') {
            newRow._cells.pushBack(new BlankCell());
        } else {
            MyString excMessage = "Error: row ";
            excMessage += rowIndex;
            excMessage += ", col ";
            excMessage += curCellCount;
            excMessage += " ";
            excMessage += value;
            excMessage += " is unknown data type!";
            throw std::invalid_argument(excMessage.c_str());
        }

        curCellCount++;
    }

    if (curCellCount > _biggestCellCount) {
        _biggestCellCount = curCellCount;
    }

    _rows.pushBack(std::move(newRow));
}

void Spreadsheet::print(std::ostream &out) const {
    if (_fileName == "") {
        throw std::logic_error("No file loaded!");
    } else {
        for (int i = 0; i < _rows.getSize(); ++i) {
            const Row &curRow = _rows[i];

            printRow(out, curRow);

            out << std::endl;
        }
    }
}

void Spreadsheet::printRow(std::ostream &out, const Row &curRow) const {
    for (int i = 0; i < curRow._cells.getSize(); ++i) {
        curRow._cells[i]->printCell(out);

        printWhiteSpaces(out, curRow, i);

        out << " | ";
    }
}

void Spreadsheet::printWhiteSpaces(std::ostream &out, const Row &curRow, int rowIndex) const {
    size_t whiteSpaces = _cellWhiteSpaces[rowIndex] - curRow._cells[rowIndex]->getWidth();
    for (int j = 0; j < whiteSpaces; ++j) {
        out << " ";
    }
}

const Cell *Spreadsheet::getCellByIndex(size_t rowIndex, size_t cellIndex) const {
    if (rowIndex >= _rows.getSize()) {
        return new BlankCell();
    }
    if (cellIndex >= _rows[rowIndex]._cells.getSize()) {
        return new BlankCell();
    }

    return _rows[rowIndex]._cells[cellIndex].operator->();
}

void Spreadsheet::edit(size_t rowIndex, size_t cellIndex, const char *newValue) {
    char *value = new char[strlen(newValue) + 1];
    strcpy(value, newValue);

    if (rowIndex >= _rows.getSize() || cellIndex >= _rows[rowIndex]._cells.getSize()) {
        throw std::invalid_argument("Indexes out of bounds!");
    }

    removeWhiteSpaces(value);

    if (value[0] == '"' && value[std::strlen(value) - 1] == '"') {
        parseEscapeSequences(value);
        removeSurroundingChars(value, '"', 1);
        _rows[rowIndex]._cells[cellIndex].reset(new StringCell(value));
    } else if (isNumber(value)) {
        if (getCharCountInArray(value, '.') == 1) {
            _rows[rowIndex]._cells[cellIndex].reset(new DoubleCell(value));
        } else {
            _rows[rowIndex]._cells[cellIndex].reset(new IntCell(value));
        }
    } else if (value[0] == '=') {
        removeSurroundingChars(value, '=');

        _rows[rowIndex]._cells[cellIndex].reset(new FormulaCell(value, this));
        dynamic_cast<FormulaCell *>(_rows[rowIndex]._cells[cellIndex].get())->parseCell();
    } else if (value[0] == '\0') {
        _rows[rowIndex]._cells[cellIndex].reset(new BlankCell());
    } else {
        throw std::invalid_argument("Unknown type entered!");
    }
}
