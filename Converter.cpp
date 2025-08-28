#include "Converter.h"
#include <string>
#include <iostream>

int interpretCharDigit(char digit) {
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

std::string convert(const std::string& num, int fromBase, int toBase, bool verbose) {
    if (verbose) std::cout << "Converting " << num << " from b" << fromBase << " to b" << toBase << std::endl;

    //handle sign
    bool neg = (num[0] == '-');
    
    //return string
    std::string convertedString;

    int value;
    switch (fromBase) {
        case 10: //convert from base 10 to any base with known algorithm
            convertedString = "";
            value = std::stoi(num);
            if (neg) value = abs(value);
            while (value > 0) {
                convertedString.insert(0, 1, (interpretDigitChar(value % toBase)));
                value /= toBase;
                if (verbose) std::cout << "V: " << value << "\tR: " << convertedString << std::endl;
            }
            break;
        default:
            switch (toBase) {
                case 10: //convert to base 10 from any base with known algorithm
                    value = 0;
                    for (int i = neg; i < num.length(); i++) {//sloppy bool --> int conversion to handle possible sign index, @todo a better way of doing this
                        value = value*fromBase + interpretCharDigit(num[i]);
                        if (verbose) std::cout << "V: " << value << std::endl;
                    }
                    convertedString = std::to_string(value);
                    break;
                default: //convert any base to any base with base 10 conversion as mediary
                    if (verbose) std::cout << "Unknown conversion, translating through base 10" << std::endl;
                    convertedString = convert(convert(num, fromBase, 10, verbose), 10, toBase, verbose);
                    if (neg) neg = false; //flip neg back if set, was handled in above calls @todo rethink signs completely
                    break;
            }
            break;
        }

    //reinsert sign to converted string if applicable
    if (neg) convertedString.insert(0, 1, '-');
    
    return convertedString;
}
