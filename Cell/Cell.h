#pragma once

#include <iostream>

class Cell {
public:
    virtual ~Cell() = default;

    virtual unsigned getWidth() const = 0;
    virtual void printCell(std::ostream &out) const = 0;

    virtual double getOperationValue() const = 0;

};
