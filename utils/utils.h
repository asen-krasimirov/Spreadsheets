#pragma once

unsigned getNumLen(int num);

unsigned getNumLen(double num);

unsigned getCharCountInArray(const char *arr, char ch);

bool isCharInArray(const char *arr, char ch);

bool isDigit(char ch);

double parseDouble(const char* input);

int parseInt(const char* input);

void removeSurroundingChars(char *str, char toRemove, unsigned limit = 0);

void removeWhiteSpaces(char* str);

void trimAllWhiteSpaces(char* str);

void parseEscapeSequences(char* str);

bool isNumber(const char* str);

double powerNumber(double base, int exponent);

void intToCharArray(int number, char* charArray, int arraySize);