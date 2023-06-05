cmake_minimum_required(VERSION 3.25)
project(Spreadsheets)

set(CMAKE_CXX_STANDARD 17)

add_executable(Spreadsheets
        main.cpp
        utils/utils.h utils/utils.cpp
        structs/Vector.hpp
        structs/UniquePointer.hpp

        MyString/MyString.h MyString/MyString.cpp

        Spreadsheet/Spreadsheet.h Spreadsheet/Spreadsheet.cpp

        Row/Row.h

        Cell/Cell.h Cell/Cell.cpp
        BlankCell/BlankCell.h BlankCell/BlankCell.cpp
        StringCell/StringCell.h StringCell/StringCell.cpp
        IntCell/IntCell.h IntCell/IntCell.cpp
        DoubleCell/DoubleCell.h DoubleCell/DoubleCell.cpp
        FormulaCell/FormulaCell.h FormulaCell/FormulaCell.cpp

        CommandMenu/CommandMenu.h CommandMenu/CommandMenu.cpp
        )
