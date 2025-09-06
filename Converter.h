#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <iostream>

struct BasedNum {
    int base;
    std::string left;
    std::string right;

    BasedNum(int b, const std::string& l, const std::string& r = "");
    const BasedNum& operator=(const BasedNum& rhs);
    friend std::ostream& operator<<(std::ostream& output, const BasedNum& num);
};

BasedNum convert(BasedNum num, int toBase, bool verbose = false);

#endif
