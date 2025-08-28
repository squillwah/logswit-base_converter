#include "Converter.h"
#include <string>
#include <iostream>

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
    static int interpretCharDigit(char digit) {
        static const int ASCII_ALPHA_OFFSET = 55;
        static const int ASCII_NUMERIC_OFFSET = 48;
    
        int integerized = 0;
        
        if (digit > 47 && digit < 58)
            integerized = digit - ASCII_NUMERIC_OFFSET;
        else if (digit > 64 && digit < 91)
            integerized = digit - ASCII_ALPHA_OFFSET;
        else 
            std::cout << "Err: can't interpret char as digit, setting '" << digit << "' to zero." << std::endl;
    
        return integerized;
    }
    
    char interpretDigitChar(int digit) {
        static const int ASCII_ALPHA_OFFSET = 55;
        static const int ASCII_NUMERIC_OFFSET = 48;
    
        char characterized = '-';
    
        if (digit >= 0 && digit < 10)
            characterized = digit + ASCII_NUMERIC_OFFSET;
        else if (digit >= 10 && digit < 36)
            characterized = digit + ASCII_ALPHA_OFFSET;
        else
            std::cout << "Err: can't find suitable alphanumeric for " << digit << ", setting to '-'" << std::endl;
    
        return characterized;
    }
    
    std::string fromTen(const std::string& num, int base, bool verbose = false) {
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
    
    std::string toTen(const std::string& num, int base, bool verbose = false) {
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
    
std::string convert(const std::string& num, int fromBase, int toBase, bool verbose) {
    if (verbose) std::cout << "Converting " << num << " from b" << fromBase << " to b" << toBase << std::endl;

    //return string
    std::string convertedString;

    switch (fromBase) {
        case 10: //convert from base 10 to any base with known algorithm
            convertedString = fromTen(num, toBase, verbose);
            break;
        default:
            switch (toBase) {
                case 10: //convert to base 10 from any base with known algorithm
                    convertedString = toTen(num, fromBase, verbose);
                    break;
                default: //convert any base to any base with base 10 conversion as mediary
                    if (verbose) std::cout << "Unknown conversion, translating through base 10" << std::endl;
                    convertedString = fromTen(toTen(num, fromBase, verbose), toBase, verbose);
                    break;
            }
            break;
        }

    return convertedString;
}
