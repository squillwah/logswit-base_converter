#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <iostream>

struct Based {
    int base;
    bool sign;
    std::string left;
    std::string right;

    //const BasedNum& operator=(const BasedNum& rhs);
    //const BasedNum& operator=(const std::string& rhs);
    friend std::ostream& operator<<(std::ostream& output, const Based& num);
};

Based convert(Based num, int toBase, bool logging_enabled = false);

#endif
