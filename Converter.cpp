#include "Converter.h"
#include <string>
#include <iostream>
#include <cmath>

//global flag for logging
bool LOGGING = false;

//output stream overload for based number struct
std::ostream& operator<<(std::ostream& output, const Based& num) {
    if (num.sign) output << '-';
    output << num.left;
    if (!num.right.empty()) output << '.' << num.right;
    return output;
}

//isolated helper functions
namespace {
    int interpretCharDigit(char digit);
    char interpretDigitChar(int digit);
    
    void toTenLHS(std::string& num, int fromBase);
    void fromTenLHS(std::string& num, int toBase);
    void toTenRHS(std::string& num, int fromBase);
    void fromTenRHS(std::string& num, int toBase, int accuracy);

}

Based convert(Based num, int toBase, bool logging_enabled) {
    LOGGING = logging_enabled;
    const bool computeLeft = !num.left.empty();
    const bool computeRight = !num.right.empty();
    
    //null conversion cases
    if (!computeLeft && !computeRight) {
        std::cerr << "Err: empty number, aborting" << std::endl;
        return num;
    }
    if (num.base < 2 || toBase < 2) {
        std::cerr << "Err: bases less than two are impossible, aborting" << std::endl;
        return num;
    }
    if (num.base == toBase) {
        if (LOGGING) std::cout << "Bases equal, no conversion needed" << std::endl;
        return num;
    }

    if (LOGGING) std::cout << "Converting " << num << " from b" << num.base << " to b" << toBase << std::endl;
    
    //calculate required decimal accuracy if decimals are present 
    int decAccuracy = 0; 
    if (computeRight) {
        decAccuracy = num.right.size()*std::log(num.base)/std::log(toBase);
        if (LOGGING) std::cout << "Minimum decimal accuracy = " << decAccuracy << std::endl;
    }
    
    //convert to ten if in different base, convert from that if desired base isn't ten 
    if (num.base != 10) {
        if (LOGGING) std::cout << "Initiating b" << num.base << " -> b10 conversion on " << num << std::endl;
        if (computeLeft) toTenLHS(num.left, num.base);
        if (computeRight) toTenRHS(num.right, num.base);
        num.base = 10;
    }
    if (toBase != 10) {
        if (LOGGING) std::cout << "Initiating b10 -> b" << toBase << " conversion on " << num << std::endl;
        if (computeLeft) fromTenLHS(num.left, toBase);
        if (computeRight) fromTenRHS(num.right, toBase, decAccuracy);
        num.base = toBase;
    }

    if (computeRight && num.right.size() > decAccuracy) {
        num = num; //round right hand side!
    }
    
    
    return num;
}

//helper function definitions
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
    
    void toTenLHS(std::string& num, int fromBase) {
        if (LOGGING) std::cout << "Executing left-handed bX->b10 conversion algorithm" << std::endl;
        int value = 0;
        for (int i = 0; i < num.length(); i++) {
            value = value*fromBase + interpretCharDigit(num[i]);
            if (LOGGING) std::cout << "V: " << value << std::endl;
        }
        num = std::to_string(value);
    }

    void toTenRHS(std::string& num, int fromBase) {
        if (LOGGING) std::cout << "Executing right-handed bX->b10 conversion algorithm" << std::endl;
        double value = 0.0;
        for (int i = num.length()-1; i > -1; i--) {
            value = (value+num[i]) / fromBase;
            if (LOGGING) std::cout << "V: " << value << std::endl;
        }
        num = std::to_string(value);
    }

    void fromTenLHS(std::string& num, int toBase) {
        if (LOGGING) std::cout << "Executing left-handed b10->bX conversion algorithm" << std::endl;
        int value = std::stoi(num);
        num = "";
        while (value > 0) {
            num.insert(0, 1, interpretDigitChar(value%toBase));
            value /= toBase;
            if (LOGGING) std::cout << "V: " << value << "\t\tR: " << num << std::endl;
        }
    }
 
    void fromTenRHS(std::string& num, int toBase, int accuracy) {
        if (LOGGING) std::cout << "Executing right-handed b10->bX conversion algorithm" << std::endl;
        int i = 2;
    }

}
