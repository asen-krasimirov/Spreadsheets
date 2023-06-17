#pragma once

#include "../structs/Vector.hpp"
#include "../structs/UniquePointer.hpp"
#include "../structs/SharedPointer.hpp"
#include "../Cell/Cell.h"

struct Row {
    Vector<SharedPointer<Cell>> _cells;

};
