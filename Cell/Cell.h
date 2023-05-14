#pragma once
#include "../MyString/MyString.h"

class Cell {
private:
    MyString _value;

public:
    Cell() = default;
    Cell(const char *value);

    const MyString &getValue() const;
    void setValue(const MyString &value);
};
