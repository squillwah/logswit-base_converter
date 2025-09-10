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

    std::cout << "-------------------------------" << std::endl;
    std::cout << "logs:" << logging_flag << " | num:" << bNum << " | from:" << bNum.base << " | to:" << toBase << std::endl;
    std::cout << "-------------------------------" << std::endl;
    
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

    int pointIndex = inputNumber.find('.');
    if (pointIndex != -1) {
        num.left = inputNumber.substr(0, pointIndex);
        num.right = inputNumber.substr(pointIndex+1);
    } else {
        num.left = inputNumber;
        num.right = "";
    }
    
    num.base = std::stoi(inputFromBase);
    toBase = std::stoi(inputToBase);

    return 0;
}

