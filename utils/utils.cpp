#include <cstring>

#include "utils.h"
#include <cmath>

unsigned getNumLen(int num) {
    unsigned ctr = 0;
    while (num > 0) {
        ctr++;
        num /= 10;
    }
    return ctr;
}

unsigned getNumLen(double num) {
    if (num == 0) {
        return 1;
    }

    int length = 0;
    long long intPart = static_cast<long long>(num);

    while (intPart != 0) {
        intPart /= 10;
        length++;
    }

    double decimalPart = num - static_cast<double>(intPart);
    int decimalLength = 0;

    if (decimalPart != 0) {
        length++;

        while (decimalPart - static_cast<long long>(decimalPart) > 0.001 && decimalLength < 4) {
            decimalPart *= 10;
            decimalLength++;
        }
    }

    return length + decimalLength;
}

unsigned getCharCountInArray(const char *arr, char ch) {
    unsigned ctr = 0;
    for (int i = 0; arr[i] != '\0'; ++i) {
        if (arr[i] == ch) {
            ctr++;
        }
    }

    return ctr;
}

bool isCharInArray(const char *arr, char ch) {
    return getCharCountInArray(arr, ch) > 0;
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

int parseInt(const char* input) {
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

void trimAllWhiteSpaces(char* str) {
    for (char* s2 = str; *s2; ++s2) {
        if (*s2 != ' ')
            *str++ = *s2;
    }
    *str = 0;
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

bool isNumber(const char* str) {
    if (str == nullptr) {
        return false;
    }

    while (*str == ' ') {
        ++str;
    }

    if (*str == '+' || *str == '-') {
        ++str;
    }

    bool isNumber = false;

    while (isDigit(*str)) {
        ++str;
        isNumber = true;
    }

    if (*str == '.') {
        ++str;
    }

    while (isDigit(*str)) {
        ++str;
        if (*str == '.') {
            isNumber = false;
            break;
        }
    }

    while (*str == ' ') {
        ++str;
    }

    return isNumber;
}

double powerNumber(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

void intToCharArray(int number, char* charArray, int arraySize) {
    int i = 0;
    bool isNegative = false;

    if (number < 0) {
        isNegative = true;
        number = -number;
    }

    do {
        charArray[i++] = '0' + (number % 10);
        number /= 10;
    } while (number != 0 && i < arraySize - 1);

    if (isNegative && i < arraySize - 1) {
        charArray[i++] = '-';
    }

    charArray[i] = '\0';

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = charArray[start];
        charArray[start++] = charArray[end];
        charArray[end--] = temp;
    }

    charArray[arraySize] = '\0';
}

double roundNumber(double number, int decimalPlaces) {
    double multiplier = powerNumber(10.0, decimalPlaces);
    return round(number * multiplier) / multiplier;
}
