#pragma once

#include "../structs/Vector.hpp"
#include "../structs/SharedPointer.hpp"
#include "../MyString/MyString.h"

class Spreadsheet {
private:
    class Cell {
    public:
        virtual ~Cell() = default;
        virtual Cell *clone() = 0;

        virtual unsigned getWidth() const = 0;
        virtual void printCell(std::ostream &out) const = 0;

        virtual double getOperationValue() const = 0;

    };

    class IntCell : public Cell {
    private:
        int _value = 0;
        unsigned _length = 0;

        void setValue(int value);
        void setLength(unsigned length);

    public:
        explicit IntCell(const char *value);
        explicit IntCell(int value);
        Cell *clone() override;

        unsigned getWidth() const override;
        void printCell(std::ostream &out) const override;

        double getOperationValue() const override;

    };

    class DoubleCell : public Cell {
    private:
        double _value = 0;
        unsigned _length = 0;

        void setValue(double value);
        void setLength(unsigned length);

    public:
        explicit DoubleCell(const char *value);
        explicit DoubleCell(double value);
        Cell *clone() override;

        unsigned getWidth() const override;
        void printCell(std::ostream &out) const override;

        double getOperationValue() const override;

    };

    class StringCell : public Cell {
    private:
        MyString _value;

    public:
        explicit StringCell(const char *value);
        Cell *clone() override;

        unsigned getWidth() const override;
        void printCell(std::ostream &out) const override;

        double getOperationValue() const override;

    };

    class BlankCell : public StringCell {
    public:
        BlankCell();
        Cell *clone() override;

        double getOperationValue() const override;

    };

    class FormulaCell : public Cell {
    private:

        Spreadsheet *_spreadsheet;

        Vector<char> _operators;
        Vector<MyString> _operands;

        SharedPointer<Cell> _formulaResult = nullptr;

        void extractOperation(MyString &value, const char *operatorSymbol);

        void parseOperandResult(const MyString &value, double &result);

    public:
        explicit FormulaCell(const char *value, Spreadsheet *spreadsheet);
        Cell *clone() override;

        void parseCell();

        unsigned getWidth() const override;
        void printCell(std::ostream &out) const override;

        double getOperationValue() const override;

    };

    struct Row {
        Vector<SharedPointer<Cell>> _cells;
    };

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

    const Cell *getCellByIndex(size_t rowIndex, size_t cellIndex) const;

private:
    void readRow(int rowIndex, const char *buffer, char delimiter);

    static void fillRow(Row &row, size_t blankCellsToAdd);
    void saveCellWhiteSpaces(Row& row);

    void printRow(std::ostream &out, const Row &curRow) const;
    void printWhiteSpaces(std::ostream &out, const Row &curRow, int rowIndex) const;

};
