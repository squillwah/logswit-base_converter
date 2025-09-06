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

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "\nCommand arguments invalid\nfollow 'convert -FLAGS [number] [base] [base2]'\n" << std::endl;
        return 1;
    }

    //command flags
    bool verbose = false;

    int argument = 1;
    if (std::string(argv[1]) == "-v") {
        verbose = true;
        argument++;
    }

    std::string number = argv[argument];
    int inBase = atoi(argv[argument+1]);
    int toBase = atoi(argv[argument+2]);

    BasedNum bnum(inBase, number);

    BasedNum converted = convert(bnum, toBase, verbose);

    std::cout << '\n' << converted << '\n' << std::endl;
    
    return 0;
}

