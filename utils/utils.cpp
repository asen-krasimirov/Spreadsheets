#include <cstring>

#include "utils.h"

unsigned getNumLen(int num) {
    unsigned ctr = 0;
    while (num > 0) {
        ctr++;
        num /= 10;
    }
    return ctr;
}

bool isDigit(char ch) {
    return '0' <= ch && ch <= '9';
}

int parseNumber(const char* input) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (input[i] == '+' || input[i] == '-') {
        sign = (input[i] == '-') ? -1 : 1;
        i++;
    }

    while (isDigit(input[i])) {
        result = result * 10 + (input[i] - '0');
        i++;
    }

    return result * sign;
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
