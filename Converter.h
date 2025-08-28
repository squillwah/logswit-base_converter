#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

int interpretCharDigit(char digit);
char interpretDigitChar(int digit);
std::string convert(const std::string& num, int fromBase, int toBase, bool verbose = false);

#endif
