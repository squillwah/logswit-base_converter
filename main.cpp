#include "Converter.h"
#include <string>
#include <iostream>

int parseInput(int argc, char*argv[], Based& num, int& toBase, bool& logging_flag);

int main(int argc, char* argv[]) {
    Based bNum;
    int toBase;
    bool logging_flag;

    int inputErr = parseInput(argc, argv, bNum, toBase, logging_flag);
    switch (inputErr) {
        case 0:
            break;
        case 1:
            std::cerr << "\nCommand arguments invalid\nfollow 'convert -FLAGS [number] [base] [base2]'\n" << std::endl;
            return inputErr;
        default:
            std::cerr << "\nInput error " << inputErr << ", aborting.\n" << std::endl;
            return inputErr;
    }
    
    Based converted = convert(bNum, toBase, logging_flag);

    std::cout << '\n' << converted << '\n' << std::endl;
    
    return 0;
}

//@todo more robust checking (any at all)
int parseInput(int argc, char*argv[], Based& num, int& toBase, bool& logging_flag) {
    if (argc < 4 || argc > 5) 
        return 1;

    int argument = 1;
    if (std::string(argv[argument]) == "-v") {
        logging_flag = true;
        argument++;
    }

    std::string inputNumber = argv[argument];
    std::string inputFromBase = argv[argument+1];
    std::string inputToBase = argv[argument+2];

    if (inputNumber[0] == '-') {
        num.sign = true;
        inputNumber.erase(0, 1);
    }

    num.left = inputNumber;
    num.right = "";
    num.base = std::stoi(inputFromBase);
    toBase = std::stoi(inputToBase);

    std::cout << "num: " << num << std::endl;
    std::cout << "base: " << num.base << std::endl;
    std::cout << "tobase: " << toBase << std::endl;

    return 0;
}

