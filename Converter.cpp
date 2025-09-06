#include "Converter.h"
#include <string>
#include <iostream>


//struct BasedNum {
//    int base;
//    std::string left;
//    std::string right;
//
//    BasedNum(int b, const std::string& l, const std::string& r = "");
//    const BasedNum& operator=(const BasedNum& rhs);
//    friend std::ostream& operator<<(std::ostream& output, const BasedNum& num);
//};

// BASEDNUM TYPE METHODS:
// ------------------
// BasedNum()
//  Constructor, sets base integer and lhs/rhs strings
// ------------------
// operator=()
//  Assignment operator
// ------------------
// operator<<()
//  Output stream operator
// ------------------
BasedNum::BasedNum(int b, const std::string& l, const std::string& r) {
    base = b;
    left = l;
    right = r;
}
const BasedNum& BasedNum::operator=(const BasedNum& rhs) {
    if (this != &rhs) { 
        base = rhs.base;
        left = rhs.left;
        right = rhs.right;
    }
    return *this;
}
std::ostream& operator<<(std::ostream& output, const BasedNum& num) {
    output << num.left;
    if (num.right.empty())
        output << '.' << num.right;
    return output;
}

// HELPER FUNCTIONS:
// ------------------
// interpretCharDigit(char digit)
//  Takes character digit, returns integer representation
// ------------------
// interpretDigitChar(int digit)
//  Takes integer digit, returns char representation (0-Z)
// ------------------
// toTen(const string& num, int base)
//  Takes string of number in a given base, returns string of num in base 10
// ------------------
// fromTen(const string& num, int base)
//  Takes string of number in base 10, returns string of num in given base
// ------------------
namespace {
    int interpretCharDigit(char digit);
    char interpretDigitChar(int digit);
    std::string fromTenLHS(const std::string& num, int base, bool verbose);
    std::string toTenLHS(const std::string& num, int base, bool verbose);
}

// BASE CONVERTER FUNCTION: 
// -------------------------
BasedNum convert(BasedNum num, int toBase, bool verbose) {
    if (verbose) std::cout << "Converting " << num << " from b" << num.base << " to b" << toBase << std::endl;

    if (num.base < 2 || toBase < 2) {
        std::cerr << "Err: bases less than two are impossible, aborting" << std::endl;
        return num;
    }

    //convert to ten if in different base, convert from that if desired base isn't ten 
    if (num.base != toBase) {
        if (num.base != 10)
            num.left = toTenLHS(num.left, num.base, verbose);
        if (toBase != 10)
            num.left = fromTenLHS(num.left, toBase, verbose);
    }
    
    return num;
}

// HELPER FUNCTION DEFINITIONS:
// -----------------------------
namespace {
    int interpretCharDigit(char digit) {
        static const int ASCII_ALPHA_OFFSET = 'A' - 10;
        static const int ASCII_NUMERIC_OFFSET = '0';
    
        int integerized = 0;
        
        if (isdigit(digit))
            integerized = digit - ASCII_NUMERIC_OFFSET;
        else if (isupper(digit))
            integerized = digit - ASCII_ALPHA_OFFSET;
        else 
            std::cerr << "Err: can't interpret char as digit, setting '" << digit << "' to zero." << std::endl;
    
        return integerized;
    }
    
    char interpretDigitChar(int digit) {
        static const int ASCII_ALPHA_OFFSET = 'A' - 10;
        static const int ASCII_NUMERIC_OFFSET = '0';
    
        char characterized = '-';
    
        if (digit >= 0 && digit < 10)
            characterized = digit + ASCII_NUMERIC_OFFSET;
        else if (digit >= 10 && digit < 36)
            characterized = digit + ASCII_ALPHA_OFFSET;
        else
            std::cerr << "Err: can't find suitable alphanumeric for " << digit << ", setting to '-'" << std::endl;
    
        return characterized;
    }
    
    std::string fromTenLHS(const std::string& num, int base, bool verbose) {
        if (verbose) std::cout << "Executing b10 -> b" << base << " conversion on " << num << std::endl;
        
        bool neg = (num[0] == '-');
        int value = abs(stoi(num));
    
        std::string convertedString = "";
        while (value > 0) {
            convertedString.insert(0, 1, interpretDigitChar(value%base));
            value /= base;
            if (verbose) std::cout << "V: " << value << "\t\tR: " << convertedString << std::endl;
        }
    
        if (neg) convertedString.insert(0, 1, '-');
    
        return convertedString;
    }
    
    std::string toTenLHS(const std::string& num, int base, bool verbose) {
        if (verbose) std::cout << "Executing b" << base << " -> b10 conversion on " << num << std::endl;
    
        bool neg = (num[0] == '-');
        int value = 0;
        
        std::string convertedString = "";
       
        int i = 0;
        if (neg) i++;
        while (i < num.length()) {
            value = value*base + interpretCharDigit(num[i]);
            if (verbose) std::cout << "V: " << value << std::endl;
            i++;
        }
    
        convertedString = std::to_string(value);
        if (neg) convertedString.insert(0, 1, '-');
    
        return convertedString;
    }
}
