#include "../MyString/MyString.h"

struct StringCell {
    MyString _value;

//public:
//    StringCell() = default;
    StringCell(const char *value);
//    const MyString &getValue() const;
private:
    void setValue(const MyString &value);

};
