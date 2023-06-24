#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
#include "Spreadsheet.h"

#include "../utils/utils.h"

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

    parseFormulaCells();

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
    saveToFile(_fileName.c_str());
}

void Spreadsheet::saveToFile(const char *fileName) const {
    if (strcmp(fileName, "") == 0) {
        throw std::logic_error("No file loaded!");
    }

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

            out << std::fixed << std::setprecision(4);   // Double padding fix

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

const Spreadsheet::Cell *Spreadsheet::getCellByIndex(size_t rowIndex, size_t cellIndex) const {
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
        _formulaCells.pushBack(_rows[rowIndex]._cells[cellIndex].get());
        dynamic_cast<FormulaCell *>(_rows[rowIndex]._cells[cellIndex].get())->parseCell();
    } else if (value[0] == '\0') {
        _rows[rowIndex]._cells[cellIndex].reset(new BlankCell());
    } else {
        throw std::invalid_argument("Unknown type entered!");
    }

    saveCellWhiteSpaces(_rows[rowIndex]);
}

void Spreadsheet::parseFormulaCells() {
    for (int i = 0; i < _formulaCells.getSize(); ++i) {
        dynamic_cast<FormulaCell *>(_formulaCells[i].get())->parseCell();
    }
}

// IntCell functions implementation
void Spreadsheet::Spreadsheet::IntCell::setValue(int value) {
    _value = value;
}

void Spreadsheet::IntCell::setLength(unsigned length) {
    _length = length;
}

Spreadsheet::IntCell::IntCell(const char *value) {
    setValue(parseInt(value));
    setLength(getNumLen(_value));
}

Spreadsheet::IntCell::IntCell(int value) {
    setValue(value);
    setLength(getNumLen(value));
}

Spreadsheet::Cell *Spreadsheet::IntCell::clone() {
    return new Spreadsheet::IntCell(*this);
}

unsigned Spreadsheet::IntCell::getWidth() const {
    return _length;
}

void Spreadsheet::IntCell::printCell(std::ostream &out) const {
    out << _value;
}

double Spreadsheet::IntCell::getOperationValue() const {
    return _value;
}

// DoubleCell functions implementation
namespace {
    const short DOUBLE_PRECISION_CAP = 4;
}

void Spreadsheet::DoubleCell::setValue(double value) {
    _value = value;
}

void Spreadsheet::DoubleCell::setLength(unsigned length) {
    _length = length;
}

Spreadsheet::DoubleCell::DoubleCell(const char *value) {
    setValue(roundNumber(parseDouble(value), DOUBLE_PRECISION_CAP));
    setLength(getNumLen(_value));
}

Spreadsheet::DoubleCell::DoubleCell(double value) {
    setValue(roundNumber(value, DOUBLE_PRECISION_CAP));
    setLength(getNumLen(_value));
}

Spreadsheet::Cell *Spreadsheet::DoubleCell::clone() {
    return new DoubleCell(*this);
}

unsigned Spreadsheet::DoubleCell::getWidth() const {
    return _length;
}

void Spreadsheet::DoubleCell::printCell(std::ostream &out) const {
    out << _value;
}

double Spreadsheet::DoubleCell::getOperationValue() const {
    return _value;
}

// StringCell functions implementation
Spreadsheet::StringCell::StringCell(const char *value) {
    _value = value;
}

Spreadsheet::Cell *Spreadsheet::StringCell::clone() {
    return new StringCell(*this);
}

unsigned Spreadsheet::StringCell::getWidth() const {
    return _value.length();
}

void Spreadsheet::StringCell::printCell(std::ostream &out) const {
    out << _value;
}

double Spreadsheet::StringCell::getOperationValue() const {
    if (isNumber(_value.c_str())) {
        if (getCharCountInArray(_value.c_str(), '.') == 1) {
            return parseDouble(_value.c_str());
        }
        else {
            return parseInt(_value.c_str());
        }
    }

    return 0;
}

// BlankCell functions implementation
Spreadsheet::BlankCell::BlankCell() : StringCell("") {

}

Spreadsheet::Cell *Spreadsheet::BlankCell::clone() {
    return new BlankCell(*this);
}

double Spreadsheet::BlankCell::getOperationValue() const {
    return 0;
}

// FormulaCell functions implementation
namespace {
    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
    }
}

void Spreadsheet::FormulaCell::extractOperation(MyString &value, const char *operators) {
    for (size_t i = 0; i < value.length(); ++i) {
        if (isCharInArray(operators, value[i])) {
            int leftIndex = i - 1;
            while (leftIndex >= 0 && value[leftIndex] != ' ' && !isOperator(value[leftIndex])) {
                leftIndex--;
            }

            if (leftIndex != i - 1) {
                _operands.pushBack(value.substr(leftIndex + 1, i - leftIndex - 1));
            }

            int rightIndex = i + 1;
            while (rightIndex < value.length() && value[rightIndex] != ' ' && !isOperator(value[rightIndex])) {
                rightIndex++;
            }

            if (rightIndex != i + 1) {
                _operands.pushBack(value.substr(i + 1, rightIndex - i - 1));
            }

            if (value[leftIndex] == ' ' || value[rightIndex] == ' ') {
                _operators.pushBack('b');
            }

            _operators.pushBack(value[i]);

            for (size_t y = leftIndex + 1; y < rightIndex; ++y) {
                value[y] = ' ';
            }
        }
    }
}

Spreadsheet::FormulaCell::FormulaCell(const char *value, Spreadsheet *spreadsheet) : _spreadsheet(spreadsheet) {
    char *tempValue = new char[strlen(value) + 1];
    strcpy(tempValue, value);
    trimAllWhiteSpaces(tempValue);

    MyString operationalValue(tempValue);
    extractOperation(operationalValue, "^");
    extractOperation(operationalValue, "/*");
    extractOperation(operationalValue, "-+");
}

Spreadsheet::Cell *Spreadsheet::FormulaCell::clone() {
    return new FormulaCell(*this);
}

unsigned Spreadsheet::FormulaCell::getWidth() const {
    return _formulaResult->getWidth();
}

void Spreadsheet::FormulaCell::printCell(std::ostream &out) const {
    _formulaResult->printCell(out);
}

void Spreadsheet::FormulaCell::parseOperandResult(const MyString &value, double &result) {
    if (isNumber(value.c_str())) {
        if (getCharCountInArray(value.c_str(), '.') == 1) {
            result = parseDouble(value.c_str());
        } else {
            result = parseInt(value.c_str());
        }
        return;
    } else if (value[0] == 'R' && getCharCountInArray(value.c_str(), 'C') == 1) {
        bool isValid = true;
        int rowIndexLen = 0;
        for (int i = 1; value[i] != 'C' && i < value.length() && value[i] != '\0'; ++i, ++rowIndexLen) {
            if (!isDigit(value[i])) {
                isValid= false;
                break;
            }
        }

        int columnIndexStart = rowIndexLen + 2;
        int columnIndexLen = 0;

        if (isValid) {
            for (int i = columnIndexStart; i < value.length() && value[i] != '\0'; ++i, ++columnIndexLen) {
                if (!isDigit(value[i])) {
                    isValid= false;
                    break;
                }
            }
        }

        if (isValid) {
            size_t rowIndex = parseInt(value.substr(1, rowIndexLen).c_str());
            size_t columnIndex = parseInt(value.substr(columnIndexStart, columnIndexLen).c_str());
            result = _spreadsheet->getCellByIndex(rowIndex - 1, columnIndex - 1)->getOperationValue();
            return;
        }
    }

    throw std::invalid_argument("Invalid type!");
}

void Spreadsheet::FormulaCell::parseCell() {
    Vector<double> operationResults;

    try {
        for (int i = 0, operandIndex = 0; i < _operators.getSize(); ++i) {
            double valueOne = 0;
            double valueTwo = 0;
            char curOperator = _operators[i];

            if (curOperator == 'b') {
                curOperator = _operators[i + 1];
                i++;

                if (operandIndex < _operands.getSize()) {
                    valueOne = operationResults.popBack();
                    parseOperandResult(_operands[operandIndex], valueTwo);
                    operandIndex += 1;
                }
                else {
                    // edge case: when there is no more operands left to get
                    valueTwo = operationResults.popBack();
                    valueOne = operationResults.popBack();
                }
            }
            else {
                parseOperandResult(_operands[operandIndex], valueOne);
                parseOperandResult(_operands[operandIndex + 1], valueTwo);

                operandIndex += 2;
            }

            double result = 0;
            switch (curOperator) {
                case '^': result = powerNumber(valueOne, valueTwo); break;
                case '*': result = valueOne * valueTwo; break;
                case '/': {
                    if (valueTwo == 0) {
                        throw std::invalid_argument("Division by zero!");
                    }
                    result = valueOne / valueTwo;
                    break;
                }
                case '+': result = valueOne + valueTwo; break;
                case '-': result = valueOne - valueTwo; break;
                default: break;
            }

            operationResults.pushBack(result);
        }

        double finalResult = operationResults.popBack();

        if (finalResult == 0) {
            _formulaResult = new BlankCell();
        } else if (finalResult - (int)finalResult < 0.000001) {
            _formulaResult = new IntCell((int) finalResult);
        }
        else {
            _formulaResult = new DoubleCell(finalResult);
        }
    }
    catch (std::invalid_argument &exc) {
        _formulaResult = new StringCell("ERROR");
    }
}

double Spreadsheet::FormulaCell::getOperationValue() const {
    return _formulaResult->getOperationValue();
}
