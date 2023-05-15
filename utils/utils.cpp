#include <cmath>    // for std::floor test
#include <cstring>

#include "utils.h"

int getAbs(int num) {
    return num >= 0 ? num : num * -1;
}

double getAbs(double num) {
    return num >= 0 ? num : num * -1;
}

int getFloor(double number) {
    int integerPart = (int)number;

    if (number >= 0 || number == integerPart)
        return integerPart;
    else
        return integerPart - 1;
}

unsigned getNumLen(int num) {
    unsigned ctr = 0;
    while (num > 0) {
        ctr++;
        num /= 10;
    }
    return ctr;
}

unsigned getNumLen(double num) {
    // TODO: not working

    unsigned length = 0;
    int integerPart = getAbs((int) num);
    while (integerPart > 0) {
        length++;
        integerPart /= 10;
    }

    double decimalPart = getAbs(num) - getAbs((int) num);
//    double decimalPart = getAbs(num) - getAbs(static_cast<int>(num));
    while (getFloor(decimalPart) != decimalPart) {
//    while (std::floor(decimalPart) != decimalPart) {
        decimalPart *= 10;
        length++;
    }

    return length;
}

bool isDigit(char ch) {
    return '0' <= ch && ch <= '9';
}

double parseDouble(const char* input) {
    double result = 0.0;
    int sign = 1;
    int i = 0;

    if (input[i] == '+' || input[i] == '-') {
        sign = (input[i] == '-') ? -1 : 1;
        i++;
    }

    while (isDigit(input[i])) {
        result = result * 10.0 + (input[i] - '0');
        i++;
    }

    if (input[i] == '.') {
        i++;
        double divisor = 10.0;
        while (isDigit(input[i])) {
            result += (input[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }

    return result * sign;
}

int parseNumber(const char* input) {
    return parseDouble(input);
}

void removeSurroundingChars(char *str, char toRemove, unsigned limit) {
    int length = std::strlen(str);
    int start = 0;
    int end = length - 1;

    int removedCount = 0;

    while (str[start] == toRemove) {
        if (limit == 0) {
            start++;
            continue;
        }

        removedCount++;
        if (removedCount > limit) {
            break;
        }

        start++;
    }

    removedCount = 0;

    while (end >= 0 && str[end] == toRemove) {
        if (limit == 0) {
            end--;
            continue;
        }

        removedCount++;
        if (removedCount > limit) {
            break;
        }

        end--;
    }

    int count = 0;

    for (int i = start; i <= end; i++) {
        str[count++] = str[i];
    }

    str[count] = '\0';
}

void removeWhiteSpaces(char* str) {
    removeSurroundingChars(str, ' ');
}

void parseEscapeSequences(char* str) {
    char* readPtr = str;
    char* writePtr = str;

    while (*readPtr != '\0') {
        if (*readPtr == '\\' && *(readPtr + 1) == '"') {
            // Replace `\"` with `"`
            *writePtr = '"';
            readPtr += 2;
        } else if (*readPtr == '\\' && *(readPtr + 1) == '\\') {
            // Replace `\\` with `\`
            *writePtr = '\\';
            readPtr += 2;
        } else {
            *writePtr = *readPtr;
            ++readPtr;
        }
        ++writePtr;
    }

    *writePtr = '\0';
}
