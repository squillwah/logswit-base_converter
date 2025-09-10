#include "Converter.h"
#include <string>
#include <iostream>
#include <cmath>

//ostream overload for based struct
std::ostream& operator<<(std::ostream& output, const Based& num) {
    if (num.sign) output << '-';
    output << num.left;
    if (!num.right.empty()) output << '.' << num.right;
    return output;
}

//helper functions
namespace {
    //flag for logging
    bool LOGGING = false;

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
    
    //null conversion states
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

    //@todo check for related bases

    //calculate required decimal accuracy if decimals are present 
    int decAccuracy = 0; 
    if (computeRight) {
        decAccuracy = ceil(num.right.size()*std::log(num.base)/std::log(toBase));
        if (LOGGING) std::cout << "Minimum decimal accuracy = " << decAccuracy << std::endl;
    }
    
    //convert to ten if in different base, convert from that if desired base isn't ten 
    if (num.base != 10) {
        if (computeLeft) toTenLHS(num.left, num.base);
        if (computeRight) toTenRHS(num.right, num.base);
        num.base = 10;
    }
    if (toBase != 10) {
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
        if (LOGGING) std::cout << "Running left-handed b" << fromBase << "->b10 on " << num << std::endl;
        int value = 0;
        for (int i = 0; i < num.length(); i++) {
            value = value*fromBase + interpretCharDigit(num[i]);
            if (LOGGING) std::cout << "V: " << value << std::endl;
        }
        num = std::to_string(value);
    }

    void toTenRHS(std::string& num, int fromBase) {
        if (LOGGING) std::cout << "Running right-handed b" << fromBase << "->b10 on ." << num << std::endl;
        double value = 0.0;
        for (int i = num.length()-1; i > -1; i--) {
            value = (value+interpretCharDigit(num[i])) / fromBase;
            if (LOGGING) std::cout << "V: " << value << std::endl;
        }
        num = std::to_string(value).substr(2);
    }

    void fromTenLHS(std::string& num, int toBase) {
        if (LOGGING) std::cout << "Running left-handed b10->b" << toBase << " on " << num << std::endl;
        int value = std::stoi(num);
        num = "";
        while (value > 0) {
            num.insert(0, 1, interpretDigitChar(value%toBase));
            value /= toBase;
            if (LOGGING) std::cout << "V: " << value << "\t\tR: " << num << std::endl;
        }
    }
 
    void fromTenRHS(std::string& num, int toBase, int accuracy) {
        if (LOGGING) std::cout << "Running right-handed b10->b" <<  toBase << " on ." << num << std::endl;
        double value = stod("."+num);
        num = "";

        //multiply value by toBase accuracy+1 times
        //append integer portion of value to num string
        //break if hit zero
        
        for (int i = 0; i < accuracy+1; i++) {
            value *= toBase;
            int whole = static_cast<int>(value);
            value -= whole;
            num += interpretDigitChar(whole);
            if (LOGGING) std::cout << "V: " << whole << " + " << value << "\tN: ." << num << std::endl;
            if (value == 0) break;
        }

        //if (num.size() > accuracy) { 
        //    int half = toBase/2;
        //    
        //    
        //    static const int EPSILON = 5;
        //    for (int i = 0; i < EPSILON; i++) 
        //    //check if last char of num above, below, or equal to half of toBase
        //    //do a while loop n times to check if repeating
        //    
        //    //round at accuracy 
        //}
        

        
    }

}
