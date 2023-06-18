#pragma once

#include "../MyString/MyString.h"
#include "../Cell/Cell.h"

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
