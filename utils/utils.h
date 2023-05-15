#pragma once

unsigned getNumLen(int num);

unsigned getNumLen(double num);

bool isDigit(char ch);

double parseDouble(const char* input);

int parseNumber(const char* input);

void removeSurroundingChars(char *str, char toRemove, unsigned limit = 0);

void removeWhiteSpaces(char* str);

void parseEscapeSequences(char* str);
