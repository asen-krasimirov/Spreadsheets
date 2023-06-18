#pragma once

#include <iostream>

class Cell {
public:
    virtual ~Cell() = default;
    virtual Cell *clone() = 0;

    virtual unsigned getWidth() const = 0;
    virtual void printCell(std::ostream &out) const = 0;

    virtual double getOperationValue() const = 0;

};
