#include "ConsoleUI.hpp"
#include <iostream>
#include <limits>
#include <string>

void printBanner(){
    std::cout << "=============================\n         NEXADIAG PRO         \n  Diagnostic Reading Module  \n=============================\n\n";
}

void printOptions(){
    std::cout << "1. Add reading.\n2. Display readings.\n3. Search reading.\n4. Calculate parameter average.\n5. Exit.\n\n";
}

int getOption(){
    int option;
    std::cout << "Select option: ";
    std::cin >> option;
    while(option <= 0 || option >= 6){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid entry. Retype: ";
        std::cin >> option;
    }
    return option;
}

