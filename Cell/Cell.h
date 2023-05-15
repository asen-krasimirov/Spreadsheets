#pragma once

#include <iostream>

class Cell {
public:
    virtual ~Cell() = default; // no necessary if there are non variables (maybe)

    virtual unsigned getWidth() const = 0;
    virtual void printCell(std::ostream &out) const = 0;

};
