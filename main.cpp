#include "Converter.h"
#include <string>
#include <iostream>

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

    std::string converted = convert(number, inBase, toBase, verbose);

    std::cout << '\n' << converted << '\n' << std::endl;
    
    return 0;
}

