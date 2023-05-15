#pragma once

#include "../MyString/MyString.h"
#include "../Cell/Cell.h"

class StringCell : public Cell {
private:
    MyString _value;

public:
    StringCell() = default;
    explicit StringCell(const char *value);

    unsigned getWidth() const override;
    void printCell(std::ostream &out) const override;

};
