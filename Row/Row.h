#pragma once

#include "../structs/Vector.hpp"
#include "../structs/UniquePointer.hpp"
#include "../Cell/Cell.h"

struct Row {
    Vector<UniquePointer<Cell>> _cells;

};