#pragma once

unsigned getNumLen(int num);

bool isDigit(char ch);

int parseNumber(const char* input);

void removeSurroundingChars(char *str, char toRemove, unsigned limit = 0);

void removeWhiteSpaces(char* str);

void parseEscapeSequences(char* str);
